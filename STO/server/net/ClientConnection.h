#ifndef STO_SERVER_CLIENTCONNECTION_H
#define STO_SERVER_CLIENTCONNECTION_H

#include <STO/server/player/PlayerController.h>
#include <STO/shared/net/BaseConnection.h>
#include <boost/smart_ptr.hpp>

namespace sto {
	class ClientConnectionCallbacks;

	class ClientConnection : public BaseConnection, public PlayerController {
		public:
			ClientConnection(ClientConnectionCallbacks &callbacks, const boost::shared_ptr<mge::Connection> &conn);
			
			void update();
			inline const boost::shared_ptr<Player> &getPlayer() { return player; }
			
			// PlayerController
		
			virtual void sendChatMessage(const Player &from, const std::string &msg);
		    virtual FlightInput getFlightInput();
			
		private:
			ClientConnectionCallbacks &callbacks;
			FlightInput latestinput;
			boost::shared_ptr<Player> player;
	};
}

#endif
