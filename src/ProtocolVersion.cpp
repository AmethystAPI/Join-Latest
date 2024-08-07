#include "ProtocolVersion.hpp"
#include <amethyst/runtime/ModContext.hpp>
#include <minecraft/src/common/network/packet/RequestNetworkSettingsPacket.hpp>
#include <minecraft/src/common/network/packet/LoginPacket.hpp>

SafetyHookInline _writeNetSettingsReq;
SafetyHookInline _writeLogin;

SafetyHookInline _serverReqNetSettingsHandler;
SafetyHookInline _serverLoginHandler;

SafetyHookInline _multiplayerGameinfoFromSessionProperties;
SafetyHookInline _multiplayerGameinfoToSessionProperties;

// Update the protocol version in packets' write() functions
void writeNetSettingsReq(size_t a1, size_t a2) {
    auto packet = (Packet*)a1;

    if (packet->getId() == MinecraftPacketIds::RequestNetworkSettings) {
        uint32_t& protoVer = *(uint32_t*)(a1 + 48);

        protoVer = TARGET_PROTOCOL_VERSION; // try and update the protocol LOL
        Log::Info("(NetworkSettingsPacket) Protocol version: {}", std::to_string(protoVer));
    }

    return _writeNetSettingsReq.call(a1, a2);
}

void writeLogin(size_t a1, size_t a2) {
    auto packet = (Packet*)a1;

    if (packet->getId() == MinecraftPacketIds::Login) {
        uint32_t& protoVer = *(uint32_t*)(a1 + 48);

        protoVer = TARGET_PROTOCOL_VERSION; // try and update the protocol LOL
        Log::Info("(LoginPacket) Protocol version: {}", std::to_string(protoVer));
    }

    return _writeLogin.call(a1, a2);
}

// Downgrade the protocol version in the server's packet handlers
void serverReqNetSettingsHandler(size_t a1, size_t a2, size_t a3) {
    auto packet = (Packet*)a3;

    if (packet->getId() == MinecraftPacketIds::RequestNetworkSettings) {
        uint32_t& protoVer = *(uint32_t*)(a3 + 48);

        protoVer = REAL_PROTOCOL_VERSION; // downgrade it back so it can join local server
        Log::Info("(ServerNetworkHandler::handle RequestNetworkSettings) Protocol version: {}", std::to_string(protoVer));
    }

    return _serverReqNetSettingsHandler.call(a1, a2, a3);
}

void serverLoginHandler(size_t a1, size_t a2, size_t a3) {
    auto packet = (Packet*)a3;

    if (packet->getId() == MinecraftPacketIds::Login) {
        uint32_t& protoVer = *(uint32_t*)(a3 + 48);

        protoVer = REAL_PROTOCOL_VERSION;
        Log::Info("(ServerNetworkHandler::handle Login) Protocol version: {}", std::to_string(protoVer));
    }

    return _serverLoginHandler.call(a1, a2, a3);
}

void* multiplayerGameinfoFromSessionProperties(int64_t a1, int64_t a2) {
    void* result = _multiplayerGameinfoFromSessionProperties.call<void*>(a1, a2);

    uint32_t protoVer = *(uint32_t*)(a1 + 552);

    if (protoVer == TARGET_PROTOCOL_VERSION) {
        protoVer = REAL_PROTOCOL_VERSION;
        Log::Info("(MultiplayerGameinfo::createFromSessionProperties) Protocol version: {}", std::to_string(protoVer));
    };

    return result;
}

void* multiplayerGameinfoToSessionProperties(int64_t a1) {
    uint32_t protoVer = *(uint32_t*)(a1 + 568);

    if (protoVer == REAL_PROTOCOL_VERSION) {
        protoVer = TARGET_PROTOCOL_VERSION;
        Log::Info("(MultiplayerGameinfo::toSessionProperties) Protocol version: {}", std::to_string(protoVer));
    };

    return _multiplayerGameinfoToSessionProperties.call<void*>(a1);
}

void SpoofProtocolVersions()
{
    auto& hooks = Amethyst::GetHookManager();
    auto& patches = Amethyst::GetPatchManager();

    // RequestNetworkSettingsPacket::write()
    hooks.RegisterFunction<&RequestNetworkSettingsPacket::write>("48 8B C2 8B 51 ? 48 8B C8 E9 ? ? ? ? CC CC 48 89 5C 24 ? 55 56 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B DA 48 8B F9 48 89 54 24 ? 33 F6 48 8D 54 24 ? 49 8B C8 E8 ? ? ? ? 90 48 8B D0 48 8D 4D ? E8 ? ? ? ? 48 8B D0 48 8D 4D ? E8 ? ? ? ? 40 38 75 ? 75 ? 48 8D 4D ? E8 ? ? ? ? 48 8D 4D ? E8 ? ? ? ? 90 80 7C 24 ? ? 75 ? 48 8D 4C 24 ? E8 ? ? ? ? 48 8D 4C 24 ? E8 ? ? ? ? 80 7D ? ? 0F 85 ? ? ? ? 0F 10 05 ? ? ? ? 0F 11 44 24 ? 0F 10 0D ? ? ? ? 0F 11 4C 24 ? C6 45 ? ? 48 8B 55 ? 48 3B 55 ? 74 ? 0F 11 02 0F 11 4A ? C6 42 ? ? 80 7D ? ? 74 ? 0F 57 C0 0F 11 42 ? 48 89 72 ? 48 89 72 ? 0F 10 44 24 ? 0F 11 42 ? 0F 10 4C 24 ? 0F 11 4A ? 66 0F 6F 05 ? ? ? ? F3 0F 7F 44 24 ? C6 44 24 ? ? 48 8B 44 24 ? 48 89 42 ? 48 8B 44 24 ? 48 89 42 ? C6 42 ? ? 48 83 45 ? ? EB ? 4C 8D 44 24 ? 48 8D 4D ? E8 ? ? ? ? 80 7D ? ? 74 ? 48 8D 4C 24 ? E8 ? ? ? ? 90 0F 28 45 ? 0F 11 45 ? 48 8B 55 ? 48 89 75 ? 48 8B 4D ? 48 89 75 ? 48 8B 45 ? 48 89 75 ? 48 89 45 ? 48 89 4D ? 48 89 55 ? 48 8B 55 ? 48 89 75 ? 48 8B 4D ? 48 89 75 ? 48 8B 45 ? 48 89 75 ? 48 89 45 ? 48 89 4D ? 48 89 55 ? 48 8D 55 ? 48 8B CB E8 ? ? ? ? 80 7D ? ? 75 ? 48 8D 4D ? E8 ? ? ? ? 48 8D 4D ? E8 ? ? ? ? EB ? 8B 45 ? 89 47 ? C6 43 ? ? 48 8B C3 48 8B 4D ? 48 33 CC E8 ? ? ? ? 48 8B 9C 24 ? ? ? ? 48 81 C4 ? ? ? ? 5F 5E 5D C3 CC CC CC CC 45 33 DB");
    hooks.CreateHook<&RequestNetworkSettingsPacket::write>(_writeNetSettingsReq, &writeNetSettingsReq);

    // LoginPacket::write()
    hooks.RegisterFunction<&LoginPacket::write>("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B F2 48 8B D9 8B 51");
    hooks.CreateHook<&LoginPacket::write>(_writeLogin, &writeLogin);

    // ServerHandler::handle() for RequestNetworkSettingsPacket
    hooks.RegisterFunction<&serverReqNetSettingsHandler>("48 8B C4 48 89 58 ? 48 89 70 ? 55 57 41 56 48 8D 68 ? 48 81 EC ? ? ? ? 0F 29 70 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 4C 8B F2 48 8B F9 41 8B 70");
    hooks.CreateHook<&serverReqNetSettingsHandler>(_serverReqNetSettingsHandler, &serverReqNetSettingsHandler);

    // ServerHandler::handle() for LoginPacket
    hooks.RegisterFunction<&serverLoginHandler>("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B F8 4C 8B E2 48 8B F1");
    hooks.CreateHook<&serverLoginHandler>(_serverLoginHandler, &serverLoginHandler);

    // Social::MultiplayerGameInfo::createFromSessionProperties
    hooks.RegisterFunction<&multiplayerGameinfoFromSessionProperties>("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B F2 48 8B F9 48 89 4C 24 ? C7 44 24");
    hooks.CreateHook<&multiplayerGameinfoFromSessionProperties>(_multiplayerGameinfoFromSessionProperties, &multiplayerGameinfoFromSessionProperties);

    // sub_141025F30 (some member of Social::MultiplayerGameInfo)
    hooks.RegisterFunction<&multiplayerGameinfoToSessionProperties>("48 89 5C 24 ? 48 89 74 24 ? 48 89 7C 24 ? 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 48 8B F1 33 DB");
    hooks.CreateHook<&multiplayerGameinfoToSessionProperties>(_multiplayerGameinfoToSessionProperties, &multiplayerGameinfoToSessionProperties);

    patches.ApplyPatch(SlideAddress(0x15BAFC2), TARGET_PROTOCOL_VERSION); // RequestNetworkSettingsPacket::_read() patch
    patches.ApplyPatch(SlideAddress(0x15A419F), TARGET_PROTOCOL_VERSION); // LoginPacket::_read() patch

    patches.ApplyPatch(SlideAddress(0x9213AE), TARGET_PROTOCOL_VERSION); // Realms::GenericRequestHandler::send() patch

    //patches.ApplyPatch(SlideAddress(0x122DC00), (uint32_t)NEW_PROTOCOL_VERSION); // X-NetworkProtocolVersion HTTP header
    //patches.ApplyPatch(SlideAddress(0x122EB03), (uint32_t)NEW_PROTOCOL_VERSION); // X-NetworkProtocolVersion HTTP header

    patches.ApplyPatch(SlideAddress(0xC992CB), TARGET_PROTOCOL_VERSION); // Settings page
}
