#include "BaseConnection.h"
#include <boost/scoped_ptr.hpp>

using namespace sto;
using namespace mge;
using namespace boost;
using namespace std;

BaseConnection::BaseConnection(BaseConnectionCallbacks &callbacks) : state(DISCONNECTED), callbacks(callbacks) {
}

void BaseConnection::setConn(PacketConnection *newconn) {
	conn = auto_ptr<PacketConnection>(newconn);
	state = ESTABLISHING;
}

void BaseConnection::update() {
	if (!hasConn())
		return;

	Connection::State connstate = getConn().getState();
	if (connstate == Connection::TIMEOUT) {
		setError("Connection timeout");
		return;
	} else if (connstate == Connection::DISCONNECTED) {
		disconnect();
		return;
	} else if (connstate != Connection::CONNECTED) {
		return;
	}
	
	if (state == ESTABLISHING) {
		connectionEstablished();
		return;
	}
	
	while (true) {
		scoped_ptr<Packet> pack(getConn().receive());
		
		if (!pack)
			break;
			
		processPacket(pack.get());
	}
}

void BaseConnection::connectionEstablished() { }

void BaseConnection::disconnect() {
	if (state == DISCONNECTED || state == ERROR)
		return;

	if (conn.get() && conn->getState() == Connection::CONNECTED)
		conn->disconnect();
	   
	state = DISCONNECTED;
	callbacks.onDisconnect(this);
	conn.reset();
}

void BaseConnection::setError(const std::string &msg) {
	if (conn.get() && conn->getState() == Connection::CONNECTED)
		conn->disconnect();
		
	errmsg = msg;
	state = ERROR;
	callbacks.onError(this, msg);
	conn.reset();
}

string BaseConnection::stateToString(BaseConnection::State state) {
	switch (state) {
		case ESTABLISHING:
			return "establishing";
			break;
	
		case CONNECTING:
			return "connecting";
			break;
			
		case CONNECTED:
			return "connected";
			break;
			
		case DISCONNECTED:
			return "disconnected";
			break;
			
		case ERROR:
			return "error";
			break;
	}
	
	return "[bad state]";
}
