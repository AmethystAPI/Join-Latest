#pragma once
#include <cstdint>

constexpr const uint32_t REAL_PROTOCOL_VERSION = 685;
constexpr const uint32_t TARGET_PROTOCOL_VERSION = 686;

class AmethystContext;

void SpoofProtocolVersions(AmethystContext& context);