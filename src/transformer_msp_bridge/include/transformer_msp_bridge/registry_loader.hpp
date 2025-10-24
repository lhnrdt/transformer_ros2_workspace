#pragma once

#include <memory>
#include <string>
#include <vector>

#include "transformer_msp_bridge/msp_registry.hpp"

namespace transformer_msp_bridge
{

  enum class MessageDirection
  {
    Unknown = 0,
    Outbound,
    Inbound,
    Bidirectional,
    Indicator
  };

  struct MessageField
  {
    std::string name;
    std::string ctype;
    std::string size;
    std::string units;
    std::string description;
  };

  struct MessageDefinition
  {
    uint16_t id{0};
    std::string name;
    std::string id_hex;
    MessageDirection direction{MessageDirection::Unknown};
    std::string direction_label;
    std::string description;
    bool has_variable_length{false};
    std::vector<MessageField> fields;
  };

  // Runtime-loaded registry built from JSON. Owns dynamically allocated schemas and message metadata.
  class RuntimeRegistry
  {
  public:
    RuntimeRegistry() = default;
    RuntimeRegistry(const RuntimeRegistry &) = delete;
    RuntimeRegistry &operator=(const RuntimeRegistry &) = delete;
    RuntimeRegistry(RuntimeRegistry &&) noexcept = default;
    RuntimeRegistry &operator=(RuntimeRegistry &&) noexcept = default;

    // Build from a JSON file path. Throws std::runtime_error on failure.
    static RuntimeRegistry from_json_file(const std::string &json_path);

    // View over the immutable descriptors.
    RegistryView view() const { return RegistryView{descriptors_.data(), descriptors_.size()}; }

    const std::vector<MessageDefinition> &message_definitions() const { return definitions_; }
    const MessageDefinition *find_definition(uint16_t id) const;

  private:
    // Storage for owned schemas to keep pointers in descriptors valid.
  public:
    struct OwnedSchema
    {
      std::unique_ptr<FieldSpec[]> fields;
      std::unique_ptr<std::string[]> names;
      std::unique_ptr<std::string[]> units;
      std::size_t count{};
    };

  private:
    std::vector<OwnedSchema> owned_schemas_{};
    std::vector<std::string> owned_names_{};
    std::vector<CommandDescriptor> descriptors_{};
    std::vector<MessageDefinition> definitions_{};
  };

  // Utility to resolve a registry JSON installed in the package share directory.
  // If env var TRANSFORMER_MSP_REGISTRY_JSON is set, that path is used.
  // Otherwise attempts to read share/<pkg>/config/msp_messages_inav.json via ament index.
  // Returns empty string if not found.
  std::string resolve_default_registry_json_path();

} // namespace transformer_msp_bridge
