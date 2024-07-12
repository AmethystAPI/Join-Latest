#pragma once
#include <Windows.h>
#include <amethyst/runtime/AmethystContext.hpp>
#include <minecraft/src/common/network/packet/Packet.hpp>

#define ModFunction extern "C" __declspec(dllexport)

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved) {
    return TRUE;
}

void writeNetSettingsReq(size_t a1, size_t a2);
void writeLogin(size_t a1, size_t a2);
void serverReqNetSettingsHandler(size_t a1, size_t a2, size_t a3);
void serverLoginHandler(size_t a1, size_t a2, size_t a3);
