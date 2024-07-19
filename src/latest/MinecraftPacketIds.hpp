#pragma once

namespace Latest {
    enum class MinecraftPacketIds : uint32_t {
        BlockPalette_deprecated = 116,
        TitleSpecificPacketsStart = 200,
        TitleSpecificPacketsEnd = 299,
        ClientboundCloseFormPacket = 310,
        ClientboundLoadScreenPacket_Deprecated = 311,
        ServerboundLoadingScreenPacket = 312,
        JigsawStructureDataPacket = 313
    };
}