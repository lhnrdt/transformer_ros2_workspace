// msp_probe: Minimal utility to verify FC responses to MSP messages as a baseline.
#include <chrono>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <map>
#include <set>
#include <string>
#include <thread>
#include <vector>

#include "transformer_msp_bridge/msp_parser.hpp"
#include "transformer_msp_bridge/msp_registry.hpp"
#include "transformer_msp_bridge/serial_port.hpp"

using namespace transformer_msp_bridge;

struct Args {
  std::string device = "/dev/ttyAMA0";
  int baud = 115200;
  int timeout_ms = 50;
  double duration_sec = 5.0;  // max wait per command
  bool log = false;
  bool only_default_polled = false;  // if true, skip entries with poll_rate_hz==0
};

static void usage(const char* exe) {
  std::cout << "Usage: " << exe
            << " [--port DEV] [--baud N] [--timeout-ms N] [--duration-sec S] [--log] [--only-default-polled]\n";
}

static bool parseArgs(int argc, char** argv, Args& a) {
  for (int i = 1; i < argc; ++i) {
    std::string k = argv[i];
    auto need = [&]() {
      if (i + 1 >= argc) {
        std::cerr << "Missing value for " << k << "\n";
        return false;
      }
      i++;
      return true;
    };
    if (k == "--port") {
      if (!need())
        return false;
      a.device = argv[i];
    } else if (k == "--baud") {
      if (!need())
        return false;
      a.baud = std::atoi(argv[i]);
    } else if (k == "--timeout-ms") {
      if (!need())
        return false;
      a.timeout_ms = std::atoi(argv[i]);
    } else if (k == "--duration-sec") {
      if (!need())
        return false;
      a.duration_sec = std::atof(argv[i]);
    } else if (k == "--log") {
      a.log = true;
    } else if (k == "--only-default-polled") {
      a.only_default_polled = true;
    } else if (k == "-h" || k == "--help") {
      usage(argv[0]);
      std::exit(0);
    } else {
      std::cerr << "Unknown arg: " << k << "\n";
      usage(argv[0]);
      return false;
    }
  }
  return true;
}

int main(int argc, char** argv) {
  Args args;
  if (!parseArgs(argc, argv, args))
    return 2;

  SerialPort sp;
  if (!sp.open(args.device, args.baud, args.timeout_ms)) {
    std::cerr << "Failed to open " << args.device << " at " << args.baud << "\n";
    return 1;
  }

  bool any_rx = false;
  MSPParser parser([&](const MSPPacket& pkt) {
    any_rx = true;
    if (args.log) {
      std::cout << "RX " << (pkt.version == MSPVersion::V2 ? "V2" : "V1") << " cmd=0x" << std::hex << pkt.cmd
                << std::dec << " len=" << pkt.payload.size() << (pkt.tunneled ? " (tunneled)" : "") << "\n";
    }
  });

  auto view = get_default_registry();
  size_t total = 0, ok = 0, noresp = 0;
  struct Miss {
    uint16_t id;
    const char* name;
    bool v2;
  };
  std::vector<Miss> misses;

  auto now = std::chrono::steady_clock::now;
  auto deadline_offset = std::chrono::duration<double>(args.duration_sec);

  for (size_t i = 0; i < view.size; ++i) {
    const auto& d = view.data[i];
    if (args.only_default_polled && d.poll_rate_hz <= 0.0)
      continue;
    total++;
    any_rx = false;
    auto frame = d.build_request_fn();
    if (args.log) {
      std::cout << "TX " << (d.is_v2() ? "V2" : "V1") << " 0x" << std::hex << d.id << std::dec << " ("
                << (d.name ? d.name : "<unnamed>") << ") size=" << frame.size() << "\n";
    }
    sp.writeAll(frame.data(), frame.size());
    auto deadline = now() + deadline_offset;
    uint8_t buf[512];
    while (now() < deadline) {
      int n = sp.readSome(buf, sizeof(buf));
      if (n < 0) {
        break;
      }
      if (n > 0) {
        parser.feed(buf, static_cast<size_t>(n));
        if (any_rx)
          break;
      }
      // small sleep to avoid busy loop
      std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    if (any_rx) {
      ok++;
    } else {
      noresp++;
      std::cout << "No response: id=0x" << std::hex << d.id << std::dec << " (" << (d.name ? d.name : "<unnamed>")
                << ")\n";
      misses.push_back(Miss{d.id, d.name ? d.name : "<unnamed>", d.is_v2()});
    }
  }

  std::cout << "Probe summary: total=" << total << " ok=" << ok << " no-response=" << noresp << "\n";
  if (!misses.empty()) {
    std::cout << "No-response commands (" << misses.size() << "):\n";
    for (const auto& m : misses) {
      std::cout << "  - 0x" << std::hex << m.id << std::dec << " (" << m.name << ") proto=" << (m.v2 ? "V2" : "V1")
                << "\n";
    }
  }
  return (noresp == 0) ? 0 : 3;
}
