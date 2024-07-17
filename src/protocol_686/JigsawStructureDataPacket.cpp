#include "JigsawStructureDataPacket.hpp"

MinecraftPacketIds Protocol_686::JigsawStructureDataPacket::getId() const
{
    return (MinecraftPacketIds)MinecraftPacketIds_686::JigsawStructureDataPacket;
}

std::string Protocol_686::JigsawStructureDataPacket::getName() const
{
    return "JigsawStructureDataPacket";
}

void Protocol_686::JigsawStructureDataPacket::write(BinaryStream& stream) {
    // add ser/de to the CompoundTag type to write mJigsawStructureDataTag
}

Bedrock::Result<void, std::error_code> Protocol_686::JigsawStructureDataPacket::_read(ReadOnlyBinaryStream&) {
    // add ser/de to the CompoundTag type to read mJigsawStructureDataTag
    return Bedrock::Result<void>(); // success
}
