#include "dllmain.hpp"
#include <ProtocolVersion.hpp>
#include <amethyst/runtime/ModContext.hpp>

// Ran when the mod is loaded into the game by AmethystRuntime
ModFunction void Initialize(AmethystContext& ctx) {
    Amethyst::InitializeAmethystMod(ctx);

    Log::Info("[Join-Latest] Started!");

    SpoofProtocolVersions();
} 