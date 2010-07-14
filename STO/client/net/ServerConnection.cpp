#include "ServerConnection.h"
#include <STO/shared/packet/ConnectPacket.h>
#include <STO/shared/packet/PlayerIDPacket.h>
#include <STO/shared/packet/ConnectRefusedPacket.h>
#include <STO/shared/packet/FlightInputPacket.h>
#include <STO/shared/packet/EntityCreatePacket.h>
#include <STO/shared/packet/EntityUpdatePacket.h>
#include <STO/version.h>
#include <boost/scoped_ptr.hpp>
#include <sstream>

using namespace sto;
using namespace mge;
using namespace boost;
using namespace std;

ServerConnection::ServerConnection(ServerConnectionCallbacks &callbacks) 
: BaseConnection(callbacks), playerid(0), callbacks(callbacks) {

}

void ServerConnection::connect(const shared_ptr<Connection> &conn, const string &newusername) {
    setConn(new PacketConnection(conn));
	username = newusername;
	state = ESTABLISHING;
}

void ServerConnection::update() {
	if (!hasConn())
		return;
		
	Connection::State connstate = getConn().getState();
		
	if (connstate == Connection::TIMEOUT) {
		setError("Connection timeout");
		return;
	}
	
	if (connstate == Connection::ESTABLISHING)
		return;

	if (state == ESTABLISHING) {
		getConn().send(ConnectPacket(STO_VERSION_STRING, username, STO_AUTHORIZE_MESSAGE), 1, Message::RELIABLE);
		state = CONNECTING;
	}

	while (true) {
		scoped_ptr<Packet> pack(getConn().receive());
		
		if (!pack)
			break;
		
		switch (state) {
			case CONNECTING:
				if (PlayerIDPacket *pidpack = dynamic_cast<PlayerIDPacket *>(pack.get())) {
					state = CONNECTED;
					playerid = pidpack->getPlayerID();
					callbacks.onConnect();
				} else if (ConnectRefusedPacket *refpack = dynamic_cast<ConnectRefusedPacket *>(pack.get())) {
					stringstream buf;
					buf << "Connection to server refused: " << refpack->getMessage();
					setError(buf.str());
				}
				break;	
				
			case CONNECTED:
				if (EntityCreatePacket *ecpack = dynamic_cast<EntityCreatePacket *>(pack.get())) {
					callbacks.onCreateEntity(ecpack->getEntityID(), ecpack->getEntityName(), ecpack->getUpdateBlob());
				} else if (EntityUpdatePacket *eupack = dynamic_cast<EntityUpdatePacket *>(pack.get())) {
					callbacks.onUpdateEntity(eupack->getEntityID(), eupack->getUpdateBlob(), eupack->isFullUpdate());
				}
				
			default:
				break;
		}
	}
}

void ServerConnection::sendFlightInput(const FlightInput &input) {
    getConn().send(FlightInputPacket(input), 0, Message::NORMAL);
}

