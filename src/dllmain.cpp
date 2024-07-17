#include "dllmain.hpp"
#include <ProtocolVersion.hpp>

// Ran when the mod is loaded into the game by AmethystRuntime
ModFunction void Initialize(AmethystContext* ctx) {
    Log::Info("[Join-Latest] Started!");

    SpoofProtocolVersions(*ctx);
}