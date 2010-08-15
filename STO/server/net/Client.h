#ifndef STO_SERVER_CLIENT_H
#define STO_SERVER_CLIENT_H

#include <STO/shared/input/FlightInput.h>
#include <STO/shared/net/BaseClientServer.h>
#include <boost/smart_ptr.hpp>

namespace mge {
	class Blob;
}

namespace sto {
	class Player;
	class ClientCallbacks;

	class Client : public BaseClientServer {
		public:
			Client(ClientCallbacks &callbacks, const boost::shared_ptr<mge::Connection> &conn);
			
			inline const boost::shared_ptr<Player> &getPlayer() { return player; }
			
			void sendEntityCreate(int id, const std::string &entityname, const mge::Blob &blob);
			void sendEntityUpdate(int id, bool full, bool remove, const mge::Blob &update);
			void sendPlayerJoined(int id, int teamid, const std::string &name);
			void sendPlayerLeft(int id);
			
			// PlayerController
		
			virtual void sendChatMessage(const Player &from, const std::string &msg);
		    virtual FlightInput getFlightInput();
			
		protected:
			virtual void processPacket(Packet *packet);
		private:
			ClientCallbacks &callbacks;
			FlightInput latestinput;
			boost::shared_ptr<Player> player;
	};
}

#endif
