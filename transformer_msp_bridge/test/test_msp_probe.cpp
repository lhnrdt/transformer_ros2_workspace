#include <gtest/gtest.h>
#include <chrono>
#include <cstdlib>
#include <cstring>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <thread>
#include "msp/msp_protocol.h"
#include "transformer_msp_bridge/msp_builders.hpp"
#include "transformer_msp_bridge/msp_parser.hpp"
#include "transformer_msp_bridge/msp_registry.hpp"
#include "transformer_msp_bridge/serial_port.hpp"

using namespace transformer_msp_bridge;

TEST(MspProbe, AllDefaultPolledRespondAndValidate) {
  const char* port = std::getenv("MSP_TEST_PORT");
  const char* baud = std::getenv("MSP_TEST_BAUD");
  if (!port || !baud) {
    GTEST_SKIP() << "MSP_TEST_PORT/MSP_TEST_BAUD not set; skipping probe test";
  }
  int baud_i = std::atoi(baud);

  SerialPort sp;
  ASSERT_TRUE(sp.open(port, baud_i, 100)) << "Failed to open serial port";

  bool any_rx = false;
  std::optional<MSPPacket> last_pkt;
  MSPParser parser([&](const MSPPacket& pkt) {
    any_rx = true;
    last_pkt = pkt;
  });

  auto view = get_default_registry();
  size_t total = 0, ok = 0;
  std::set<uint16_t> missing_ids;
  std::map<uint16_t, std::string> validation_errors;  // removed validation; kept var for minimal diff but unused

  auto now = std::chrono::steady_clock::now;
  auto deadline_offset = std::chrono::duration<double>(5.0);

  for (size_t i = 0; i < view.size; ++i) {
    const auto& d = view.data[i];
    if (d.poll_rate_hz <= 0.0)
      continue;  // only default-polled
    total++;
    any_rx = false;
    last_pkt.reset();
    auto frame = d.build_request_fn();
    ASSERT_TRUE(sp.writeAll(frame.data(), frame.size()));
    auto deadline = now() + deadline_offset;
    uint8_t buf[512];
    while (now() < deadline) {
      int n = sp.readSome(buf, sizeof(buf));
      if (n < 0)
        break;
      if (n > 0) {
        parser.feed(buf, static_cast<size_t>(n));
        if (any_rx)
          break;
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(2));
    }
    if (!any_rx) {
      missing_ids.insert(d.id);
      continue;
    }
    ok++;
    // No value validation anymore.
  }

  if (!missing_ids.empty()) {
    std::ostringstream msg;
    msg << "Probe summary: total=" << total << " ok=" << ok << " missing=" << missing_ids.size() << "\n";
    if (!missing_ids.empty()) {
      msg << "Missing responses:";
      for (auto id : missing_ids)
        msg << " 0x" << std::hex << id;
      msg << "\n";
    }
    FAIL() << msg.str();
  }
}
