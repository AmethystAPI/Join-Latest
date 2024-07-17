#pragma once
#include <protocol_686/Protocol_686.hpp>
#include <minecraft/src/common/network/packet/Packet.hpp>
#include <minecraft/src/common/network/PacketHandlerDispatcherInstance.hpp>

namespace Protocol_686 {
	class ClientboundCloseFormPacket : public Packet {
	public:
		virtual MinecraftPacketIds getId() const override;
		virtual std::string getName() const override;
		virtual void write(BinaryStream&) override;
		virtual Bedrock::Result<void, std::error_code> _read(ReadOnlyBinaryStream&) override;
	};

	template <>
	class PacketHandlerDispatcherInstance<ClientboundCloseFormPacket, false> : public IPacketHandlerDispatcher {
	public:
		virtual void handle(const NetworkIdentifier&, NetEventCallback&, std::shared_ptr<Packet>) const override {
			// Todo: implement form closing?
			Log::Info("[ClientboundCloseFormPacket recieved] Dropping!");
		}
	};
}