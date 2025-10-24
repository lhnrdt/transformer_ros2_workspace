#pragma once

#include <optional>
#include <string>
#include <vector>

#include <gtest/gtest.h>

#include "transformer_msp_bridge/msp_registry.hpp"

namespace transformer_msp_bridge::test_utils
{

inline std::optional<std::size_t> schema_expected_size(uint16_t command_id)
{
  const CommandDescriptor *desc = find_descriptor(command_id);
  if (!desc)
  {
    ADD_FAILURE() << "Command ID 0x" << std::hex << command_id << std::dec << " not present in registry";
    return std::nullopt;
  }
  if (!desc->response_schema || desc->response_schema_count == 0)
  {
    ADD_FAILURE() << "Command '" << desc->name << "' (0x" << std::hex << desc->id << std::dec
                  << ") has no response schema; JSON definition may be missing fields.";
    return std::nullopt;
  }
  ResponseSchema schema{desc->response_schema, desc->response_schema_count};
  std::size_t expected = 0;
  if (!schema_fixed_size_bytes(schema, expected))
  {
    ADD_FAILURE() << "Command '" << desc->name << "' (0x" << std::hex << desc->id << std::dec
                  << ") schema is not fixed-size; cannot validate payload length in test.";
    return std::nullopt;
  }
  return expected;
}

inline void expect_payload_matches_schema(uint16_t command_id, const std::vector<uint8_t> &payload)
{
  auto expected = schema_expected_size(command_id);
  ASSERT_TRUE(expected.has_value()) << "Schema lookup failed for command 0x" << std::hex << command_id;
  ASSERT_EQ(payload.size(), expected.value())
      << "Payload size mismatch for command 0x" << std::hex << command_id << std::dec;
}

} // namespace transformer_msp_bridge::test_utils
