#pragma once

#include <cstdint>
#include <memory>
#include <vector>
#include "transformer_msp_bridge/decoder_base.hpp"

namespace transformer_msp_bridge
{

  class DecoderRegistry
  {
  public:
    void add(std::unique_ptr<IMspDecoder> dec) { decoders_.push_back(std::move(dec)); }
    bool dispatch(const MSPPacket &pkt)
    {
      bool handled = false;
      for (auto &d : decoders_)
      {
        if (d->matches(pkt.cmd))
        {
          d->decode(pkt);
          handled = true;
        }
      }
      return handled;
    }
    bool hasDecoder(uint16_t command_id) const
    {
      for (auto &d : decoders_)
        if (d->matches(command_id))
          return true;
      return false;
    }
    std::vector<uint16_t> coveredIds() const
    {
      // Potentially duplicates if multiple decoders match same id; caller can unique() if needed.
      std::vector<uint16_t> ids;
      // We can't enumerate all IDs a decoder might match without probing; we take registry-driven probing elsewhere.
      return ids; // Placeholder; coverage check will brute-force over registry instead.
    }

  private:
    std::vector<std::unique_ptr<IMspDecoder>> decoders_;
  };

} // namespace transformer_msp_bridge
