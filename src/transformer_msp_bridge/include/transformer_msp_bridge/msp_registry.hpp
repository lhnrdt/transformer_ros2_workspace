// Declares lookups and schema helpers for the MSP command registry.
#pragma once

#include <cstddef>
#include <cstdint>
#include <functional>
#include <string>
#include <string_view>
#include <vector>

#include "transformer_msp_bridge/msp_messages_inav.hpp"

namespace transformer_msp_bridge::msp
{

using ::msp::MspField;
using ::msp::MspMsg;

inline constexpr uint16_t kMspV2FrameId = 0xFF;

struct MessageSchema
{
  const MspField *fields{nullptr};
  std::size_t count{0};
  const MspMsg *message{nullptr};

  [[nodiscard]] bool has_fields() const { return fields != nullptr && count > 0; }
};

struct RegistryEntry
{
  std::string_view name{};
  uint16_t id{0};
  double poll_rate_hz{0.0};
  bool default_polled{false};
  std::function<std::vector<uint8_t>()> build_request_fn;
  MessageSchema response_schema{};
};

struct RegistryView
{
  const RegistryEntry *data{nullptr};
  std::size_t size{0};
};

[[nodiscard]] uint16_t command_id(std::string_view name);
[[nodiscard]] const MspMsg *find_message_by_id(uint16_t id);
[[nodiscard]] const MspMsg *find_message_by_name(std::string_view name);
[[nodiscard]] bool is_v2(uint16_t id);
[[nodiscard]] std::string_view message_name(uint16_t id);
[[nodiscard]] RegistryView get_default_registry();

bool schema_fixed_size_bytes(const MessageSchema &schema, std::size_t &out_bytes);
bool parse_to_flat_list(const MessageSchema &schema, const std::vector<uint8_t> &payload,
                        std::vector<double> &out_values,
                        std::vector<std::string> *field_names = nullptr,
                        std::string *error = nullptr);

} // namespace transformer_msp_bridge::msp
