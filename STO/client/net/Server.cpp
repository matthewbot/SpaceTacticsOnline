#include "Server.h"
#include <STO/shared/packet/ConnectPacket.h>
#include <STO/shared/packet/PlayerIDPacket.h>
#include <STO/shared/packet/ConnectRefusedPacket.h>
#include <STO/shared/packet/FlightInputPacket.h>
#include <STO/shared/packet/EntityCreatePacket.h>
#include <STO/shared/packet/EntityUpdatePacket.h>
#include <STO/shared/packet/PlayerJoinedPacket.h>
#include <STO/shared/packet/PlayerLeftPacket.h>
#include <STO/version.h>
#include <boost/scoped_ptr.hpp>
#include <sstream>

using namespace sto;
using namespace mge;
using namespace boost;
using namespace std;

Server::Server(ServerCallbacks &callbacks) 
: BaseClientServer(callbacks), playerid(0), callbacks(callbacks) {

}

void Server::connect(const shared_ptr<Connection> &conn, const string &newusername) {
    setConn(new PacketConnection(conn));
	username = newusername;
	state = ESTABLISHING;
}

void Server::connectionEstablished() {
	state = CONNECTING;
	getConn().send(ConnectPacket(STO_VERSION_STRING, username, STO_AUTHORIZE_MESSAGE), 1, Message::RELIABLE);
}

void Server::processPacket(Packet *pack) {
	switch (state) {
		case CONNECTING:
			if (PlayerIDPacket *pidpack = dynamic_cast<PlayerIDPacket *>(pack)) {
				state = CONNECTED;
				playerid = pidpack->getPlayerID();
				callbacks.onConnect();
			} else if (ConnectRefusedPacket *refpack = dynamic_cast<ConnectRefusedPacket *>(pack)) {
				stringstream buf;
				buf << "Connection to server refused: " << refpack->getMessage();
				setError(buf.str());
			}
			break;	
			
		case CONNECTED:
			if (EntityCreatePacket *ecpack = dynamic_cast<EntityCreatePacket *>(pack)) {
				callbacks.onCreateEntity(ecpack->getEntityID(), ecpack->getEntityName(), ecpack->getUpdateBlob());
			} else if (EntityUpdatePacket *eupack = dynamic_cast<EntityUpdatePacket *>(pack)) {
				callbacks.onUpdateEntity(eupack->getEntityID(), eupack->getUpdateBlob(), eupack->isFullUpdate());
			} else if (PlayerJoinedPacket *pjpack = dynamic_cast<PlayerJoinedPacket *>(pack)) {
				callbacks.onPlayerJoined(pjpack->getID(), pjpack->getTeamID(), pjpack->getUsername());
			} else if (PlayerLeftPacket *plpack = dynamic_cast<PlayerLeftPacket *>(pack)) {
				callbacks.onPlayerLeft(plpack->getID());
			}
			
		default:
			break;
	}
}

void Server::sendFlightInput(const FlightInput &input) {
    getConn().send(FlightInputPacket(input), 0, Message::NORMAL);
}

