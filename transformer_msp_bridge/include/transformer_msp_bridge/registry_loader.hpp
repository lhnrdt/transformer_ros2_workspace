#pragma once

#include <memory>
#include <string>
#include <unordered_map>
#include <vector>

#include "transformer_msp_bridge/msp_registry.hpp"

namespace transformer_msp_bridge {

// Runtime-loaded registry built from YAML. Owns dynamically allocated schemas.
class RuntimeRegistry {
 public:
  RuntimeRegistry() = default;
  RuntimeRegistry(const RuntimeRegistry&) = delete;
  RuntimeRegistry& operator=(const RuntimeRegistry&) = delete;
  RuntimeRegistry(RuntimeRegistry&&) noexcept = default;
  RuntimeRegistry& operator=(RuntimeRegistry&&) noexcept = default;

  // Build from a YAML file path. Throws std::runtime_error on failure.
  static RuntimeRegistry from_yaml_file(const std::string& yaml_path);

  // View over the immutable descriptors.
  RegistryView view() const { return RegistryView{descriptors_.data(), descriptors_.size()}; }

  // Find by command id and version flag.
  const CommandDescriptor* find(uint16_t id, bool v2) const;

 private:
  // Storage for owned schemas to keep pointers in descriptors valid.
 public:
  struct OwnedSchema {
    std::unique_ptr<FieldSpec[]> fields;
    std::unique_ptr<std::string[]> names;
    std::unique_ptr<std::string[]> units;
    std::size_t count{};
  };

 private:
  std::vector<OwnedSchema> owned_schemas_{};
  std::vector<std::string> owned_names_{};
  std::vector<CommandDescriptor> descriptors_{};
};

// Utility to resolve a registry YAML installed in the package share directory.
// If env var TRANSFORMER_MSP_REGISTRY_YAML is set, that path is used.
// Otherwise attempts to read share/<pkg>/config/registry.yaml via ament index.
// Returns empty string if not found.
std::string resolve_default_registry_yaml_path();

}  // namespace transformer_msp_bridge
