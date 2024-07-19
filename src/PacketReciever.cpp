#include "PacketReciever.hpp"
#include <amethyst/Memory.hpp>
#include <amethyst/runtime/ModContext.hpp>
#include <minecraft/src/common/network/packet/Packet.hpp>

SafetyHookInline _MinecraftPackets_createPacket;

std::shared_ptr<Packet> MinecraftPackets_createPacket(MinecraftPacketIds packetID) {
	return _MinecraftPackets_createPacket.call<std::shared_ptr<Packet>>(packetID);
}

void CreatePacketHooks()
{
	auto& hooks = Amethyst::GetHookManager();
	hooks.RegisterFunction<&MinecraftPackets::createPacket>("40 53 48 83 EC ? 45 33 C0 48 8B D9 FF CA 81 FA");
	hooks.CreateHook<&MinecraftPackets::createPacket>(_MinecraftPackets_createPacket, &MinecraftPackets_createPacket);
}
