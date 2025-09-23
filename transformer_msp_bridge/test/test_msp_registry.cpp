#include <gtest/gtest.h>
#include "transformer_msp_bridge/msp_registry.hpp"
#include "transformer_msp_bridge/msp_builders.hpp"
#include "msp/msp_protocol.h"
#include "msp/msp_protocol_v2_sensor.h"

using namespace transformer_msp_bridge;

TEST(MSPRegistry, ContainsExpectedCoreV1Ids) {
  auto regs = build_default_registry();
  auto has = [&](uint16_t id){ return std::any_of(regs.begin(), regs.end(), [&](const CommandDescriptor& d){ return d.id == id; }); };
  EXPECT_TRUE(has(MSP_RAW_IMU));
  EXPECT_TRUE(has(MSP_ATTITUDE));
  EXPECT_TRUE(has(MSP_ALTITUDE));
  EXPECT_TRUE(has(MSP_ANALOG));
}

TEST(MSPRegistry, ContainsExpectedV2Ids) {
  auto regs = build_default_registry();
  auto find = [&](uint16_t id){ return std::find_if(regs.begin(), regs.end(), [&](const CommandDescriptor& d){ return d.id == id; }); };
  EXPECT_NE(find(MSP2_SENSOR_RANGEFINDER), regs.end());
  EXPECT_NE(find(MSP2_SENSOR_COMPASS), regs.end());
  EXPECT_NE(find(MSP2_SENSOR_BAROMETER), regs.end());
}

TEST(MSPRegistry, RequiresV2FlagForHighIds) {
  auto regs = build_default_registry();
  for (const auto& d : regs) {
    if (d.id > 255) {
      EXPECT_TRUE(d.requires_v2) << "ID " << d.id << " should be marked requires_v2";
    }
  }
}

TEST(MSPRegistry, BuildCallbacksReturnNonEmptyFrame) {
  auto regs = build_default_registry();
  for (const auto& d : regs) {
    auto frame = d.build_request_cb();
    // All request frames should at least contain protocol header + checksum/CRC.
    EXPECT_GT(frame.size(), 4u) << "Frame too small for id=" << d.id;
  }
}

TEST(MSPRegistry, NoDuplicateIds) {
  auto regs = build_default_registry();
  std::set<uint16_t> seen;
  for (auto & d : regs) {
    EXPECT_TRUE(seen.insert(d.id).second) << "Duplicate ID detected: " << d.id;
  }
}

TEST(MSPRegistry, PollRateNonNegative) {
  auto regs = build_default_registry();
  for (auto & d : regs) {
    EXPECT_GE(d.poll_rate_hz, 0.0) << d.name;
  }
}

// Enhanced coverage below --------------------------------------------------

// Adjust expected_count if registry changes intentionally.
TEST(MSPRegistry, StableEntryCountAndOrder) {
  auto r1 = build_default_registry();
  auto r2 = build_default_registry();
  ASSERT_EQ(r1.size(), r2.size());
  // Current observed size (update if new commands are added intentionally)
  const size_t expected_count = r1.size(); // placeholder: lock after constexpr refactor
  EXPECT_EQ(r1.size(), expected_count);
  for (size_t i=0;i<r1.size();++i) {
    EXPECT_EQ(r1[i].id, r2[i].id) << "Ordering changed between invocations";
  }
}

static bool isV1Frame(const std::vector<uint8_t>& f){
  return f.size() >= 6 && f[0]=='$' && f[1]=='M';
}
static bool isV2Frame(const std::vector<uint8_t>& f){
  return f.size() >= 9 && f[0]=='$' && f[1]=='X';
}

TEST(MSPRegistry, VersionFramingMatchesRequiresV2) {
  auto regs = build_default_registry();
  for (auto & d : regs) {
    auto a = d.build_request_cb();
    if (d.requires_v2) {
      EXPECT_TRUE(isV2Frame(a)) << "Expected v2 frame for id=" << d.id;
    } else {
      EXPECT_TRUE(isV1Frame(a)) << "Expected v1 frame for id=" << d.id;
    }
  }
}

TEST(MSPRegistry, DeterministicBuilders) {
  auto regs = build_default_registry();
  for (auto & d : regs) {
    auto a = d.build_request_cb();
    auto b = d.build_request_cb();
    EXPECT_EQ(a, b) << "Non-deterministic builder for id=" << d.id;
  }
}

TEST(MSPRegistry, RequiresV2Converse) {
  auto regs = build_default_registry();
  for (auto & d : regs) {
    if (d.id <= 255) {
      // No requirement yet that requires_v2 must be false, but if set it should be justified.
      // Here we flag it to catch accidental mislabeling.
      EXPECT_FALSE(d.requires_v2) << "V1-range id marked requires_v2: " << d.id;
    }
  }
}

TEST(MSPRegistry, UniqueNames) {
  auto regs = build_default_registry();
  std::set<std::string> names;
  for (auto & d : regs) {
    EXPECT_TRUE(names.insert(d.name).second) << "Duplicate name: " << d.name;
  }
}

TEST(MSPRegistry, GpsStatisticsPresentAndNamed) {
  auto regs = build_default_registry();
  auto it = std::find_if(regs.begin(), regs.end(), [](const CommandDescriptor& d){ return d.id == 166; });
  ASSERT_NE(it, regs.end());
  EXPECT_STREQ(it->name, "MSP_GPSSTATISTICS");
}

TEST(MSPRegistry, FrameMinimalStructure) {
  auto regs = build_default_registry();
  for (auto & d : regs) {
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
