#include "transformer_msp_bridge/decoders/inav_generic_decoder.hpp"
#include <iomanip>
#include <sstream>
#include "msp/msp_protocol_v2_inav.h"

namespace transformer_msp_bridge
{

  using diagnostic_msgs::msg::DiagnosticArray;
  using diagnostic_msgs::msg::DiagnosticStatus;
  using diagnostic_msgs::msg::KeyValue;

  static inline std::string to_hex(const std::vector<uint8_t> &data)
  {
    std::ostringstream oss;
    for (uint8_t b : data)
    {
      oss << std::hex << std::uppercase << std::setw(2) << std::setfill('0') << (int)b;
    }
    return oss.str();
  }

  bool InavGenericDecoder::matches(uint16_t command_id) const
  {
    switch (command_id)
    {
    case MSP2_INAV_ANALOG:
    case MSP2_INAV_BATTERY_CONFIG:
    case MSP2_INAV_AIR_SPEED:
    case MSP2_INAV_TEMPERATURES:
    case MSP2_INAV_ESC_RPM:
      return true;
    default:
      return false;
    }
  }

  void InavGenericDecoder::publishRaw(const MSPPacket &pkt, const std::string &title)
  {
    DiagnosticStatus st;
    st.name = title;
    st.hardware_id = "fc";
    st.level = DiagnosticStatus::OK;
    st.message = "raw";
    KeyValue kv;
    kv.key = "payload";
    kv.value = to_hex(pkt.payload);
    st.values.push_back(kv);
    DiagnosticArray arr;
    arr.header.stamp = node_.now();
    arr.status.push_back(st);
    diag_pub_->publish(arr);
  }

  void InavGenericDecoder::decode(const MSPPacket &pkt)
  {
    switch (pkt.cmd)
    {
    case MSP2_INAV_ANALOG:
      publishRaw(pkt, "inav_analog");
      break;
    case MSP2_INAV_BATTERY_CONFIG:
      publishRaw(pkt, "inav_battery_config");
      break;
    case MSP2_INAV_AIR_SPEED:
      publishRaw(pkt, "inav_air_speed");
      break;
    case MSP2_INAV_TEMPERATURES:
      publishRaw(pkt, "inav_temperatures");
      break;
    case MSP2_INAV_ESC_RPM:
      publishRaw(pkt, "inav_esc_rpm");
      break;
    default:
      break;
    }
  }

} // namespace transformer_msp_bridge
