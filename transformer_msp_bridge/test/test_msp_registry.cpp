#include <gtest/gtest.h>
#include "msp/msp_protocol.h"
#include "msp/msp_protocol_v2_sensor.h"
#include "transformer_msp_bridge/msp_builders.hpp"
#include "transformer_msp_bridge/msp_registry.hpp"

using namespace transformer_msp_bridge;

TEST(MSPRegistry, ContainsExpectedCoreV1Ids) {
  auto view = get_default_registry();
  std::vector<CommandDescriptor> regs(view.begin(), view.end());
  auto has = [&](uint16_t id) {
    return std::any_of(regs.begin(), regs.end(), [&](const CommandDescriptor& d) { return d.id == id; });
  };
  EXPECT_TRUE(has(MSP_RAW_IMU));
  EXPECT_TRUE(has(MSP_ATTITUDE));
  EXPECT_TRUE(has(MSP_ALTITUDE));
  EXPECT_TRUE(has(MSP_ANALOG));
}

TEST(MSPRegistry, ContainsExpectedV2Ids) {
  auto view = get_default_registry();
  std::vector<CommandDescriptor> regs(view.begin(), view.end());
  auto find = [&](uint16_t id) {
    return std::find_if(regs.begin(), regs.end(), [&](const CommandDescriptor& d) { return d.id == id; });
  };
  EXPECT_NE(find(MSP2_SENSOR_RANGEFINDER), regs.end());
  EXPECT_NE(find(MSP2_SENSOR_COMPASS), regs.end());
  EXPECT_NE(find(MSP2_SENSOR_BAROMETER), regs.end());
}

TEST(MSPRegistry, RequiresV2FlagForHighIds) {
  auto view = get_default_registry();
  std::vector<CommandDescriptor> regs(view.begin(), view.end());
  for (const auto& d : regs) {
    if (d.id > 255) {
      EXPECT_TRUE(d.requires_v2) << "ID " << d.id << " should be marked requires_v2";
    }
  }
}

TEST(MSPRegistry, BuildCallbacksReturnNonEmptyFrame) {
  auto view = get_default_registry();
  std::vector<CommandDescriptor> regs(view.begin(), view.end());
  for (const auto& d : regs) {
    auto frame = d.build_request_cb();
    // All request frames should at least contain protocol header + checksum/CRC.
    EXPECT_GT(frame.size(), 4u) << "Frame too small for id=" << d.id;
  }
}

TEST(MSPRegistry, NoDuplicateIds) {
  auto view = get_default_registry();
  std::vector<CommandDescriptor> regs(view.begin(), view.end());
  std::set<uint16_t> seen;
  for (auto& d : regs) {
    EXPECT_TRUE(seen.insert(d.id).second) << "Duplicate ID detected: " << d.id;
  }
}

TEST(MSPRegistry, PollRateNonNegative) {
  auto view = get_default_registry();
  std::vector<CommandDescriptor> regs(view.begin(), view.end());
  for (auto& d : regs) {
    EXPECT_GE(d.poll_rate_hz, 0.0) << d.name;
  }
}

// Enhanced coverage below --------------------------------------------------

// Adjust expected_count if registry changes intentionally.
TEST(MSPRegistry, StableEntryCountAndOrder) {
  auto r1 = get_default_registry();
  auto r2 = get_default_registry();
  ASSERT_EQ(r1.size, r2.size);
  constexpr size_t expected_count = 26;  // Update if you add/remove commands.
  EXPECT_EQ(r1.size, expected_count);
  EXPECT_EQ(kDefaultRegistrySize(), expected_count);
  for (size_t i = 0; i < r1.size; ++i) {
    EXPECT_EQ(r1.data[i].id, r2.data[i].id) << "Ordering changed between invocations";
  }
}

static bool isV1Frame(const std::vector<uint8_t>& f) {
  return f.size() >= 6 && f[0] == '$' && f[1] == 'M';
}
static bool isV2Frame(const std::vector<uint8_t>& f) {
  return f.size() >= 9 && f[0] == '$' && f[1] == 'X';
}

TEST(MSPRegistry, VersionFramingMatchesRequiresV2) {
  auto view = get_default_registry();
  for (size_t i = 0; i < view.size; ++i) {
    const auto& d = view.data[i];
    auto frame = d.build_request_cb();
    if (d.requires_v2) {
      EXPECT_TRUE(isV2Frame(frame)) << d.name;
    } else {
      EXPECT_TRUE(isV1Frame(frame)) << d.name;
    }
  }
}

TEST(MSPRegistry, DeterministicBuilders) {
  auto view = get_default_registry();
  std::vector<CommandDescriptor> regs(view.begin(), view.end());
  for (auto& d : regs) {
    auto a = d.build_request_cb();
    auto b = d.build_request_cb();
    EXPECT_EQ(a, b) << "Non-deterministic builder for id=" << d.id;
  }
}

TEST(MSPRegistry, RequiresV2Converse) {
  auto view = get_default_registry();
  std::vector<CommandDescriptor> regs(view.begin(), view.end());
  for (auto& d : regs) {
    if (d.id <= 255) {
      // No requirement yet that requires_v2 must be false, but if set it should be justified.
      // Here we flag it to catch accidental mislabeling.
      EXPECT_FALSE(d.requires_v2) << "V1-range id marked requires_v2: " << d.id;
    }
  }
}

TEST(MSPRegistry, UniqueNames) {
  auto view = get_default_registry();
  std::vector<CommandDescriptor> regs(view.begin(), view.end());
  std::set<std::string> names;
  for (auto& d : regs) {
    EXPECT_TRUE(names.insert(d.name).second) << "Duplicate name: " << d.name;
  }
}

TEST(MSPRegistry, GpsStatisticsPresentAndNamed) {
  auto view = get_default_registry();
  std::vector<CommandDescriptor> regs(view.begin(), view.end());
  auto it = std::find_if(regs.begin(), regs.end(), [](const CommandDescriptor& d) { return d.id == 166; });
  ASSERT_NE(it, regs.end());
  EXPECT_STREQ(it->name, "MSP_GPSSTATISTICS");
}

TEST(MSPRegistry, FrameMinimalStructure) {
  auto view = get_default_registry();
  std::vector<CommandDescriptor> regs(view.begin(), view.end());
  for (auto& d : regs) {
    auto f = d.build_request_cb();
    ASSERT_GE(f.size(), d.requires_v2 ? 9u : 6u);
    EXPECT_EQ(f[0], '$');
    if (d.requires_v2) {
      EXPECT_EQ(f[1], 'X');
    } else {
      EXPECT_EQ(f[1], 'M');
    }
  }
}
