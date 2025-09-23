#pragma once

#include <vector>
#include <memory>
#include <cstdint>
#include "transformer_msp_bridge/decoder_base.hpp"

namespace transformer_msp_bridge {

class DecoderRegistry {
public:
  void add(std::unique_ptr<IMspDecoder> dec) { decoders_.push_back(std::move(dec)); }
  bool dispatch(const MSPPacket &pkt) {
    bool handled = false;
    for (auto &d : decoders_) {
      if (d->matches(pkt.cmd)) { d->decode(pkt); handled = true; }
    }
    return handled;
  }
private:
  std::vector<std::unique_ptr<IMspDecoder>> decoders_;
};

} // namespace transformer_msp_bridge
