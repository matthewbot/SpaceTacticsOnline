#ifndef STO_SERVER_CLIENTCONNECTIONCALLBACKS_H
#define STO_SERVER_CLIENTCONNECTIONCALLBACKS_H

#include <STO/shared/net/BaseClientServerCallbacks.h>
#include <boost/smart_ptr.hpp>
#include <string>

namespace sto {
	class Player;
	class ClientConnection;

	class ClientConnectionCallbacks : public BaseClientServerCallbacks {
		public:
			inline virtual ~ClientConnectionCallbacks() { }
			
			virtual void onConnectRefused(ClientConnection *conn, const std::string &reason) = 0;
			virtual boost::shared_ptr<Player> onConnect(ClientConnection *conn, const std::string &version, const std::string &username, const std::string &authmsg) = 0;
	};
}

#endif
