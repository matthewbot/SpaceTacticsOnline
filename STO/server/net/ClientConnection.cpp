#include "ClientConnection.h"
#include <MGE/net/Connection.h>
#include <STO/shared/packet/ConnectPacket.h>
#include <STO/shared/packet/PlayerIDPacket.h>
#include <STO/shared/packet/FlightInputPacket.h>
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

void ClientConnection::update() {
	if (!hasConn())
		return;

	if (getConn().getState() == Connection::TIMEOUT) {
		setError("Connection timeout");
		return;
	}
	
	while (true) {
		scoped_ptr<Packet> pack(getConn().receive());
		
		if (!pack)
			break;
		
		switch (state) {
			case CONNECTING:
				if (ConnectPacket *connpack = dynamic_cast<ConnectPacket *>(pack.get())) {
					int pid = callbacks.onConnect(this, connpack->getVersion(), connpack->getUsername(), connpack->getAuthmsg());
					getConn().send(PlayerIDPacket(pid), 1, Message::NORMAL);
				}
				break;	
				
			case CONNECTED:
				if (FlightInputPacket *flightpack = dynamic_cast<FlightInputPacket *>(pack.get())) {
					latestinput = flightpack->getFlightInput();
				}
			default:
				break;
		}
	}
}

void ClientConnection::sendChatMessage(const Player &from, const string &msg) {
	// TODO
}

FlightInput ClientConnection::getFlightInput() {
	return latestinput;
}

