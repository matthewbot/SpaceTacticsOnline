#ifndef STO_CLIENT_SERVERCONNECTION_H
#define STO_CLIENT_SERVERCONNECTION_H

#include "ServerConnectionCallbacks.h"
#include <STO/shared/net/BaseConnection.h>
#include <STO/shared/input/FlightInput.h>
#include <string>

namespace sto {
	class ServerConnection : public BaseConnection {
		public:
			ServerConnection(ServerConnectionCallbacks &callbacks);
			
			void connect(const boost::shared_ptr<mge::Connection> &conn, const std::string &username);
			
			inline int getPlayerID() { return playerid; }
			
			void update();
			
			void sendFlightInput(const FlightInput &input);
	
		private:
			std::string username;
			int playerid;
			
			ServerConnectionCallbacks &callbacks;
	};
}

#endif
