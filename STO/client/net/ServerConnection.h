#ifndef STO_CLIENT_SERVERCONNECTION_H
#define STO_CLIENT_SERVERCONNECTION_H

#include "ServerConnectionCallbacks.h"
#include <STO/shared/net/BaseClientServer.h>
#include <STO/shared/input/FlightInput.h>
#include <string>

namespace sto {
	class ServerConnection : public BaseClientServer {
		public:
			ServerConnection(ServerConnectionCallbacks &callbacks);
			
			void connect(const boost::shared_ptr<mge::Connection> &conn, const std::string &username);
			void sendFlightInput(const FlightInput &input);
			
			inline int getPlayerID() { return playerid; }
			
		protected:
			virtual void connectionEstablished();
			virtual void processPacket(Packet *packet);
			
		private:
			std::string username;
			int playerid;
			
			ServerConnectionCallbacks &callbacks;
	};
}

#endif
