#include "JigsawStructureDataPacket.hpp"
#include <latest/MinecraftPacketIds.hpp>

::MinecraftPacketIds Latest::JigsawStructureDataPacket::getId() const
{
    return (::MinecraftPacketIds)Latest::MinecraftPacketIds::JigsawStructureDataPacket;
}

std::string Latest::JigsawStructureDataPacket::getName() const
{
    return "JigsawStructureDataPacket";
}

void Latest::JigsawStructureDataPacket::write(BinaryStream& stream) {
    // add ser/de to the CompoundTag type to write mJigsawStructureDataTag
}

Bedrock::Result<void, std::error_code> Latest::JigsawStructureDataPacket::_read(ReadOnlyBinaryStream&) {
    // add ser/de to the CompoundTag type to read mJigsawStructureDataTag
    return Bedrock::Result<void>(); // success
}
