#include <gtest/gtest.h>
#include <algorithm>
#include <cstdint>
#include <set>
#include <string_view>

#include "transformer_msp_bridge/msp_registry.hpp"

namespace registry = transformer_msp_bridge::msp;

namespace
{

uint16_t require_command(std::string_view name)
{
  const uint16_t id = registry::command_id(name);
  EXPECT_NE(id, 0u) << "command not found in registry: " << name;
  return id;
}
} // namespace

TEST(MSPRegistry, MessageLookupProvidesMetadata)
{
  const uint16_t rtc_id = require_command("MSP_RTC");
  ASSERT_NE(rtc_id, 0u);
  const registry::MspMsg *rtc_msg = registry::find_message_by_id(rtc_id);
  ASSERT_NE(rtc_msg, nullptr);
  EXPECT_EQ(rtc_msg->field_count, 2u);
  EXPECT_TRUE(registry::is_v2(require_command("MSP2_INAV_ESC_RPM")));
  const std::string_view name = registry::message_name(rtc_id);
  EXPECT_FALSE(name.empty());
  EXPECT_EQ(name, std::string_view("MSP_RTC"));
}
