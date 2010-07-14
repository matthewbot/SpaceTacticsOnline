#include "BaseConnection.h"

using namespace sto;
using namespace std;

BaseConnection::BaseConnection(BaseConnectionCallbacks &callbacks) : state(DISCONNECTED), callbacks(callbacks) {
}

void BaseConnection::setConn(PacketConnection *newconn) {
	conn = auto_ptr<PacketConnection>(newconn);
	state = ESTABLISHING;
}
 

void BaseConnection::disconnect() {
    if (conn.get()) {
	    conn->disconnect();
	    state = DISCONNECTED;
	    conn.reset();
	}
}

void BaseConnection::setError(const std::string &msg) {
    disconnect();
	errmsg = msg;
	state = ERROR;
	callbacks.onError(this, msg);
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
