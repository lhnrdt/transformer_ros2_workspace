#include <gtest/gtest.h>
#include "msp/msp_protocol.h"
#include "msp/msp_protocol_v2_sensor.h"
#include "transformer_msp_bridge/msp_builders.hpp"
#include "transformer_msp_bridge/msp_registry.hpp"

using namespace transformer_msp_bridge;

TEST(MSPRegistry, ContainsExpectedCoreV1Ids)
{
  auto view = get_default_registry();
  std::vector<CommandDescriptor> regs(view.begin(), view.end());
  auto has = [&](uint16_t id)
  {
    return std::any_of(regs.begin(), regs.end(), [&](const CommandDescriptor &d)
                       { return d.id == id; });
  };
  EXPECT_TRUE(has(MSP_RAW_IMU));
  EXPECT_TRUE(has(MSP_ATTITUDE));
  EXPECT_TRUE(has(MSP_ALTITUDE));
  EXPECT_TRUE(has(MSP_ANALOG));
}

TEST(MSPRegistry, ContainsExpectedV2Ids)
{
  auto view = get_default_registry();
  std::vector<CommandDescriptor> regs(view.begin(), view.end());
  auto find = [&](uint16_t id)
  {
    return std::find_if(regs.begin(), regs.end(), [&](const CommandDescriptor &d)
                        { return d.id == id; });
  };
  EXPECT_NE(find(MSP2_SENSOR_RANGEFINDER), regs.end());
  EXPECT_NE(find(MSP2_SENSOR_COMPASS), regs.end());
  EXPECT_NE(find(MSP2_SENSOR_BAROMETER), regs.end());
}

// Explicit requires_v2 flag removed; inference via CommandDescriptor::is_v2() (id > 255).
TEST(MSPRegistry, V2InferenceMatchesIdRange)
{
  auto view = get_default_registry();
  for (size_t i = 0; i < view.size; ++i)
  {
    const auto &d = view.data[i];
    EXPECT_EQ(d.is_v2(), d.id > 255) << "Inference mismatch for id=" << d.id;
  }
}

TEST(MSPRegistry, BuildCallbacksReturnNonEmptyFrame)
{
  auto view = get_default_registry();
  std::vector<CommandDescriptor> regs(view.begin(), view.end());
  for (const auto &d : regs)
  {
    auto frame = d.build_request_fn();
    // All request frames should at least contain protocol header + checksum/CRC.
    EXPECT_GT(frame.size(), 4u) << "Frame too small for id=" << d.id;
  }
}

TEST(MSPRegistry, NoDuplicateIds)
{
  auto view = get_default_registry();
  std::vector<CommandDescriptor> regs(view.begin(), view.end());
  std::set<uint16_t> seen;
  for (auto &d : regs)
  {
    EXPECT_TRUE(seen.insert(d.id).second) << "Duplicate ID detected: " << d.id;
  }
}

TEST(MSPRegistry, PollRateNonNegative)
{
  auto view = get_default_registry();
  std::vector<CommandDescriptor> regs(view.begin(), view.end());
  for (auto &d : regs)
  {
    EXPECT_GE(d.poll_rate_hz, 0.0) << d.name;
  }
}

// Enhanced coverage below --------------------------------------------------

// Removed fixed-count test: the registry size can evolve without requiring an edit to a magic number.
// Ordering determinism is sufficiently covered by deterministic construction (constexpr static array).

static bool isV1Frame(const std::vector<uint8_t> &f)
{
  return f.size() >= 6 && f[0] == '$' && f[1] == 'M';
}
static bool isV2Frame(const std::vector<uint8_t> &f)
{
  return f.size() >= 9 && f[0] == '$' && f[1] == 'X';
}

TEST(MSPRegistry, VersionFramingMatchesInference)
{
  auto view = get_default_registry();
  for (size_t i = 0; i < view.size; ++i)
  {
    const auto &d = view.data[i];
    auto frame = d.build_request_fn();
    if (d.is_v2())
    {
      EXPECT_TRUE(isV2Frame(frame)) << d.name;
    }
    else
    {
      EXPECT_TRUE(isV1Frame(frame)) << d.name;
    }
  }
}

TEST(MSPRegistry, DeterministicBuilders)
{
  auto view = get_default_registry();
  std::vector<CommandDescriptor> regs(view.begin(), view.end());
  for (auto &d : regs)
  {
    auto a = d.build_request_fn();
    auto b = d.build_request_fn();
    EXPECT_EQ(a, b) << "Non-deterministic builder for id=" << d.id;
  }
}

// RequiresV2Converse test obsolete (manual flag removed).

TEST(MSPRegistry, UniqueNames)
{
  auto view = get_default_registry();
  std::vector<CommandDescriptor> regs(view.begin(), view.end());
  std::set<std::string> names;
  for (auto &d : regs)
  {
    EXPECT_TRUE(names.insert(d.name).second) << "Duplicate name: " << d.name;
  }
}

TEST(MSPRegistry, GpsStatisticsPresentAndNamed)
{
  auto view = get_default_registry();
  std::vector<CommandDescriptor> regs(view.begin(), view.end());
  auto it = std::find_if(regs.begin(), regs.end(), [](const CommandDescriptor &d)
                         { return d.id == 166; });
  ASSERT_NE(it, regs.end());
  EXPECT_STREQ(it->name, "MSP_GPSSTATISTICS");
}

TEST(MSPRegistry, FrameMinimalStructure)
{
  auto view = get_default_registry();
  std::vector<CommandDescriptor> regs(view.begin(), view.end());
  for (auto &d : regs)
  {
    auto f = d.build_request_fn();
    ASSERT_GE(f.size(), d.is_v2() ? 9u : 6u);
    EXPECT_EQ(f[0], '$');
    if (d.is_v2())
    {
      EXPECT_EQ(f[1], 'X');
    }
    else
    {
      EXPECT_EQ(f[1], 'M');
    }
  }
}
