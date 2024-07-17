#include "ClientboundCloseFormPacket.hpp"

MinecraftPacketIds Protocol_686::ClientboundCloseFormPacket::getId() const
{
    return (MinecraftPacketIds)MinecraftPacketIds_686::ClientboundCloseFormPacket;
}

std::string Protocol_686::ClientboundCloseFormPacket::getName() const
{
    return "ClientboundClosePacketFormPacket";
}

void Protocol_686::ClientboundCloseFormPacket::write(BinaryStream& stream) {}

Bedrock::Result<void, std::error_code> Protocol_686::ClientboundCloseFormPacket::_read(ReadOnlyBinaryStream&) {
    return Bedrock::Result<void>(); // success
}
