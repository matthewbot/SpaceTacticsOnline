#include "ClientConnection.h"
#include "ClientConnectionCallbacks.h"
#include <STO/server/player/Player.h>
#include <STO/shared/packet/ConnectPacket.h>
#include <STO/shared/packet/ConnectRefusedPacket.h>
#include <STO/shared/packet/PlayerIDPacket.h>
#include <STO/shared/packet/FlightInputPacket.h>
#include <STO/version.h>
#include <MGE/net/Connection.h>
#include <boost/scoped_ptr.hpp>

using namespace sto;
using namespace mge;
using namespace boost;
using namespace std;

ClientConnection::ClientConnection(ClientConnectionCallbacks &callbacks, const boost::shared_ptr<mge::Connection> &conn) 
: BaseConnection(callbacks), callbacks(callbacks) {
	setConn(new PacketConnection(conn));
	state = CONNECTING;
}

void ClientConnection::processPacket(Packet *pack) {
	switch (getConn().getState()) {
		case CONNECTING:
			if (ConnectPacket *connpack = dynamic_cast<ConnectPacket *>(pack)) {
				string refuse_reason;
				if (connpack->getVersion() != STO_VERSION_STRING)
					refuse_reason = "Invalid client version '" + connpack->getVersion() + "'";
				if (connpack->getAuthmsg() != STO_AUTHORIZE_MESSAGE)
					refuse_reason = "Bad authorization message '" + connpack->getAuthmsg() + "'";
					
				if (refuse_reason.size() == 0) {
					player = callbacks.onConnect(this, connpack->getVersion(), connpack->getUsername(), connpack->getAuthmsg());
					getConn().send(PlayerIDPacket(player->getID()), 1, Message::RELIABLE);
					state = CONNECTED;
				} else {
					callbacks.onConnectRefused(this, refuse_reason);
					getConn().send(ConnectRefusedPacket(refuse_reason), 1, Message::RELIABLE);
					setError("Connection refused");
				}
			}
			break;	
			
		case CONNECTED:
			if (FlightInputPacket *flightpack = dynamic_cast<FlightInputPacket *>(pack)) {
				latestinput = flightpack->getFlightInput();
			}
		default:
			break;
	}
}

void ClientConnection::sendChatMessage(const Player &from, const string &msg) {
	// TODO
}

FlightInput ClientConnection::getFlightInput() {
	return latestinput;
}

