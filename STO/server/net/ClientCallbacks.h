#ifndef STO_SERVER_CLIENTCALLBACKS_H
#define STO_SERVER_CLIENTCALLBACKS_H

#include <STO/shared/net/BaseClientServerCallbacks.h>
#include <boost/smart_ptr.hpp>
#include <string>

namespace sto {
	class Player;
	class Client;

	class ClientCallbacks : public BaseClientServerCallbacks {
		public:
			inline virtual ~ClientCallbacks() { }
			
			virtual void onConnectRefused(Client *conn, const std::string &reason) = 0;
			virtual boost::shared_ptr<Player> onConnect(Client *conn, const std::string &version, const std::string &username, const std::string &authmsg) = 0;
	};
}

#endif
