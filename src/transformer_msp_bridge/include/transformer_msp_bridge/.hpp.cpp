inline constexpr auto MSP_API_VERSION_FIELDS = ::msp::make_fields(
    ::msp::MspField{("mspProtocolVersion"), ("uint8_t"), ("1"), (""),
                    ("MSP Protocol version (MSP_PROTOCOL_VERSION, typically 0).")},
    ::msp::MspField{("apiVersionMajor"), ("uint8_t"), ("1"), (""), ("INAV API Major version (API_VERSION_MAJOR).")},
    ::msp::MspField{("apiVersionMinor"), ("uint8_t"), ("1"), (""), ("INAV API Minor version (API_VERSION_MINOR).")});
inline constexpr ::msp::MspMsg MSP_API_VERSION {
  "MSP_API_VERSION", (0x01), (::msp::MspDir::Out),
      ::std::span<const ::msp::MspField>(MSP_API_VERSION_FIELDS.data(), MSP_API_VERSION_FIELDS.size())
}