#pragma once

#include "transformer_msp_bridge/msp_parser.hpp"
#include "transformer_msp_bridge/decoder_base.hpp"
#include "transformer_msp_bridge/decoder_outputs.hpp"
#include <functional>
#include <string>

namespace transformer_msp_bridge
{

  class InavStatusDecoder : public IMspDecoder
  {
  public:
    using StatusCallback = std::function<void(const InavStatusData &)>;

    struct Callbacks
    {
      StatusCallback status{};
      std::function<void(const std::string &)> log_info{};
      bool log_first_frame{false};
    };

  InavStatusDecoder();
  explicit InavStatusDecoder(Callbacks callbacks);
    void set_callbacks(Callbacks callbacks);
    void decode(const MSPPacket &pkt) override;
    bool matches(uint16_t command_id) const override;
    std::string name() const override;

  private:
    Callbacks callbacks_{};
    bool logged_{false};
  };

} // namespace transformer_msp_bridge
