#include "ClientboundCloseFormPacket.hpp"
#include <latest/MinecraftPacketIds.hpp>

::MinecraftPacketIds Latest::ClientboundCloseFormPacket::getId() const
{
    return (::MinecraftPacketIds)(Latest::MinecraftPacketIds::ClientboundCloseFormPacket);
}

std::string Latest::ClientboundCloseFormPacket::getName() const
{
    return "ClientboundClosePacketFormPacket";
}

void Latest::ClientboundCloseFormPacket::write(BinaryStream& stream) {}

Bedrock::Result<void, std::error_code> Latest::ClientboundCloseFormPacket::_read(ReadOnlyBinaryStream&) {
    return Bedrock::Result<void>(); // success
}
