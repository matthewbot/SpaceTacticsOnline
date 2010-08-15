#ifndef STO_CLIENT_Server_H
#define STO_CLIENT_Server_H

#include "ServerCallbacks.h"
#include <STO/shared/net/BaseClientServer.h>
#include <STO/shared/input/FlightInput.h>
#include <string>

namespace sto {
	class Server : public BaseClientServer {
		public:
			Server(ServerCallbacks &callbacks);
			
			void connect(const boost::shared_ptr<mge::Connection> &conn, const std::string &username);
			void sendFlightInput(const FlightInput &input);
			
			inline int getPlayerID() { return playerid; }
			
		protected:
			virtual void connectionEstablished();
			virtual void processPacket(Packet *packet);
			
		private:
			std::string username;
			int playerid;
			
			ServerCallbacks &callbacks;
	};
}

#endif
