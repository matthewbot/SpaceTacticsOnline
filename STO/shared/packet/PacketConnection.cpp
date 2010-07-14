#include "PacketConnection.h"

using namespace sto;
using namespace mge;

PacketConnection::PacketConnection(const boost::shared_ptr<Connection> &conn) : conn(conn) { }

Packet *PacketConnection::receive() {
	if (!conn->messageAvailable())
		return NULL;
		
	Message msg = conn->getMessage();
	Blob blob = msg.getData();
	return pman.decode(blob);
}

void PacketConnection::send(const Packet &packet, int chan, Message::Type type) {
	Blob blob(100);
	pman.encode(packet, blob);
	
	conn->sendMessage(Message(blob, chan, type));
}


#include "BasePacketFactory.h"
#include "ConnectPacket.h"
#include "ConnectRefusedPacket.h"
#include "EntityCreatePacket.h"
#include "EntityUpdatePacket.h"
#include "FlightInputPacket.h"
#include "PlayerIDPacket.h"

PacketConnection::AssembledPacketManager::AssembledPacketManager() {
	addFactory(new BasePacketFactory<ConnectPacket, 1>());
	addFactory(new BasePacketFactory<ConnectRefusedPacket, 2>());
	addFactory(new BasePacketFactory<EntityCreatePacket, 3>());
	addFactory(new BasePacketFactory<EntityUpdatePacket, 4>());
	addFactory(new BasePacketFactory<FlightInputPacket, 5>());
	addFactory(new BasePacketFactory<PlayerIDPacket, 6>());
}

const PacketConnection::AssembledPacketManager PacketConnection::pman;
