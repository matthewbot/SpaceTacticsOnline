#include "Client.h"
#include "ClientCallbacks.h"
#include <STO/shared/player/Player.h>
#include <STO/shared/packet/ConnectPacket.h>
#include <STO/shared/packet/ConnectRefusedPacket.h>
#include <STO/shared/packet/PlayerIDPacket.h>
#include <STO/shared/packet/FlightInputPacket.h>
#include <STO/shared/packet/EntityCreatePacket.h>
#include <STO/shared/packet/EntityUpdatePacket.h>
#include <STO/shared/packet/PlayerJoinedPacket.h>
#include <STO/shared/packet/PlayerLeftPacket.h>
#include <STO/version.h>
#include <MGE/net/Connection.h>
#include <MGE/util/Blob.h>
#include <boost/scoped_ptr.hpp>

using namespace sto;
using namespace mge;
using namespace boost;
using namespace std;

Client::Client(ClientCallbacks &callbacks, const boost::shared_ptr<mge::Connection> &conn) 
: BaseClientServer(callbacks), callbacks(callbacks) {
	setConn(new PacketConnection(conn));
	state = CONNECTING;
}

void Client::sendEntityCreate(int id, const std::string &entityname, const mge::Blob &update) {
	getConn().send(EntityCreatePacket(id, entityname, update), 1, Message::RELIABLE);
}

void Client::sendEntityUpdate(int id, bool full, bool remove, const mge::Blob &update) {
	getConn().send(EntityUpdatePacket(id, full, remove, update), 2, Message::NORMAL);
}

void Client::sendPlayerJoined(int id, int teamid, const std::string &username) {
	getConn().send(PlayerJoinedPacket(id, teamid, username), 1, Message::RELIABLE);
}

void Client::sendPlayerLeft(Player::ID id) {
	getConn().send(PlayerLeftPacket(id), 1, Message::RELIABLE);
}

void Client::processPacket(Packet *pack) {
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

void Client::sendChatMessage(const Player &from, const string &msg) {
	// TODO
}

FlightInput Client::getFlightInput() {
	return latestinput;
}

