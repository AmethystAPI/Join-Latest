#include "dllmain.hpp"

SafetyHookInline _writeNetSettingsReq;
SafetyHookInline _writeLogin;

SafetyHookInline _serverReqNetSettingsHandler;
SafetyHookInline _serverLoginHandler;

// Ran when the mod is loaded into the game by AmethystRuntime
ModFunction void Initialize(AmethystContext* ctx) {
    ctx->mHookManager.RegisterFunction<&writeNetSettingsReq>("48 8B C2 8B 51 ? 48 8B C8 E9 ? ? ? ? CC CC 48 89 5C 24 ? 55 56 57 48 8D 6C 24 ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 48 8B DA 48 8B F9 48 89 54 24 ? 33 F6 48 8D 54 24 ? 49 8B C8 E8 ? ? ? ? 90 48 8B D0 48 8D 4D ? E8 ? ? ? ? 48 8B D0 48 8D 4D ? E8 ? ? ? ? 40 38 75 ? 75 ? 48 8D 4D ? E8 ? ? ? ? 48 8D 4D ? E8 ? ? ? ? 90 80 7C 24 ? ? 75 ? 48 8D 4C 24 ? E8 ? ? ? ? 48 8D 4C 24 ? E8 ? ? ? ? 80 7D ? ? 0F 85 ? ? ? ? 0F 10 05 ? ? ? ? 0F 11 44 24 ? 0F 10 0D ? ? ? ? 0F 11 4C 24 ? C6 45 ? ? 48 8B 55 ? 48 3B 55 ? 74 ? 0F 11 02 0F 11 4A ? C6 42 ? ? 80 7D ? ? 74 ? 0F 57 C0 0F 11 42 ? 48 89 72 ? 48 89 72 ? 0F 10 44 24 ? 0F 11 42 ? 0F 10 4C 24 ? 0F 11 4A ? 66 0F 6F 05 ? ? ? ? F3 0F 7F 44 24 ? C6 44 24 ? ? 48 8B 44 24 ? 48 89 42 ? 48 8B 44 24 ? 48 89 42 ? C6 42 ? ? 48 83 45 ? ? EB ? 4C 8D 44 24 ? 48 8D 4D ? E8 ? ? ? ? 80 7D ? ? 74 ? 48 8D 4C 24 ? E8 ? ? ? ? 90 0F 28 45 ? 0F 11 45 ? 48 8B 55 ? 48 89 75 ? 48 8B 4D ? 48 89 75 ? 48 8B 45 ? 48 89 75 ? 48 89 45 ? 48 89 4D ? 48 89 55 ? 48 8B 55 ? 48 89 75 ? 48 8B 4D ? 48 89 75 ? 48 8B 45 ? 48 89 75 ? 48 89 45 ? 48 89 4D ? 48 89 55 ? 48 8D 55 ? 48 8B CB E8 ? ? ? ? 80 7D ? ? 75 ? 48 8D 4D ? E8 ? ? ? ? 48 8D 4D ? E8 ? ? ? ? EB ? 8B 45 ? 89 47 ? C6 43 ? ? 48 8B C3 48 8B 4D ? 48 33 CC E8 ? ? ? ? 48 8B 9C 24 ? ? ? ? 48 81 C4 ? ? ? ? 5F 5E 5D C3 CC CC CC CC 45 33 DB");
    ctx->mHookManager.CreateHook<&writeNetSettingsReq>(_writeNetSettingsReq, &writeNetSettingsReq);

    ctx->mHookManager.RegisterFunction<&writeLogin>("48 89 5C 24 ? 48 89 74 24 ? 57 48 83 EC ? 48 8B F2 48 8B D9 8B 51");
	ctx->mHookManager.CreateHook<&writeLogin>(_writeLogin, &writeLogin);

    ctx->mHookManager.RegisterFunction<&serverReqNetSettingsHandler>("48 8B C4 48 89 58 ? 48 89 70 ? 55 57 41 56 48 8D 68 ? 48 81 EC ? ? ? ? 0F 29 70 ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 45 ? 4C 8B F2 48 8B F9 41 8B 70");
    ctx->mHookManager.CreateHook<&serverReqNetSettingsHandler>(_serverReqNetSettingsHandler, &serverReqNetSettingsHandler);

    ctx->mHookManager.RegisterFunction<&serverLoginHandler>("48 89 5C 24 ? 55 56 57 41 54 41 55 41 56 41 57 48 8D AC 24 ? ? ? ? 48 81 EC ? ? ? ? 48 8B 05 ? ? ? ? 48 33 C4 48 89 85 ? ? ? ? 4D 8B F8 4C 8B E2 48 8B F1");
	ctx->mHookManager.CreateHook<&serverLoginHandler>(_serverLoginHandler, &serverLoginHandler);

	ctx->mPatchManager.ApplyPatch(SlideAddress(0x15BAFC2), (uint32_t) NEW_PROTOCOL_VERSION); // RequestNetworkSettingsPacket::_read() patch
    ctx->mPatchManager.ApplyPatch(SlideAddress(0x15A419F), (uint32_t) NEW_PROTOCOL_VERSION); // LoginPacket::_read() patch
}

void writeNetSettingsReq(size_t a1, size_t a2) {
    auto packet = (Packet*)a1;

    if (packet->getId() == MinecraftPacketIds::RequestNetworkSettings) {
		uint32_t &protoVer = *(unsigned int*)(a1 + 48);

        protoVer = NEW_PROTOCOL_VERSION; // try and update the protocol LOL
        Log::Info("(NetworkSettingsPacket) Protocol version: {}", std::to_string(protoVer));
    }

    return _writeNetSettingsReq.call(a1, a2);
}

void writeLogin(size_t a1, size_t a2) {
    auto packet = (Packet*)a1;

    if (packet->getId() == MinecraftPacketIds::Login) {
		unsigned int& protoVer = *(unsigned int*)(a1 + 48);

		protoVer = NEW_PROTOCOL_VERSION; // try and update the protocol LOL
		Log::Info("(LoginPacket) Protocol version: {}", std::to_string(protoVer));
    }

	return _writeLogin.call(a1, a2);
}

void serverReqNetSettingsHandler(size_t a1, size_t a2, size_t a3) {
    auto packet = (Packet*)a3;

    if (packet->getId() == MinecraftPacketIds::RequestNetworkSettings) {
		unsigned int& protoVer = *(unsigned int*)(a3 + 48);

		protoVer = OLD_PROTOCOL_VERSION; // downgrade it back so it can join local server
		Log::Info("(ServerNetworkHandler::handle RequestNetworkSettings) Protocol version: {}", std::to_string(protoVer));
    }

    return _serverReqNetSettingsHandler.call(a1, a2, a3);
}

void serverLoginHandler(size_t a1, size_t a2, size_t a3) {
    auto packet = (Packet*)a3;

    if (packet->getId() == MinecraftPacketIds::Login) {
		unsigned int& protoVer = *(unsigned int*)(a3 + 48);

		protoVer = OLD_PROTOCOL_VERSION;
		Log::Info("(ServerNetworkHandler::handle Login) Protocol version: {}", std::to_string(protoVer));
    }

    return _serverLoginHandler.call(a1, a2, a3);
}

