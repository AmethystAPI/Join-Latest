#pragma once
#include <Windows.h>
#include <cstdint>
#include <string>
#include <amethyst/runtime/AmethystContext.hpp>
#include <minecraft/src/common/network/packet/Packet.hpp>

#define ModFunction extern "C" __declspec(dllexport)

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    return TRUE;
}

const uint32_t OLD_PROTOCOL_VERSION = 685;
const std::string OLD_BASEGAME_VERSION = "1.21.0";

const uint32_t NEW_PROTOCOL_VERSION = 686;
const std::string NEW_BASEGAME_VERSION = "1.21.2";

void writeNetSettingsReq(size_t a1, size_t a2);
void writeLogin(size_t a1, size_t a2);
void serverReqNetSettingsHandler(size_t a1, size_t a2, size_t a3);
void serverLoginHandler(size_t a1, size_t a2, size_t a3);
