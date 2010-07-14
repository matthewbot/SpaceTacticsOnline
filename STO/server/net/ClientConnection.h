#ifndef STO_SERVER_CLIENTCONNECTION_H
#define STO_SERVER_CLIENTCONNECTION_H

#include "ClientConnectionCallbacks.h"
#include <STO/server/player/PlayerController.h>
#include <STO/shared/net/BaseConnection.h>

namespace sto {
	class ClientConnection : public BaseConnection, public PlayerController {
		public:
			ClientConnection(ClientConnectionCallbacks &callbacks, const boost::shared_ptr<mge::Connection> &conn);
			
			void update();
			
			// PlayerController
		
			virtual void sendChatMessage(const Player &from, const std::string &msg);
		    virtual FlightInput getFlightInput();
			
		private:
			ClientConnectionCallbacks &callbacks;
			FlightInput latestinput;
	};
}

#endif
