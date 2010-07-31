#ifndef STO_SERVER_CLIENTCONNECTIONLIST_H
#define STO_SERVER_CLIENTCONNECTIONLIST_H

#include "ClientConnectionCallbacks.h"
#include <boost/shared_ptr.hpp>
#include <list>

namespace mge {
	class NetworkSystem;
}

namespace sto {
	class PlayerList;
	class ClientConnection;

	class ClientConnectionManager : public ClientConnectionCallbacks {
		typedef std::list<boost::shared_ptr<ClientConnection> > ConnectionList;
	
		public:
			typedef ConnectionList::const_iterator ConnectionIterator;
		
			ClientConnectionManager(PlayerList &players, mge::NetworkSystem *net);
			~ClientConnectionManager();
			
			void update();
			
			inline ConnectionIterator begin() const { return connections.begin(); }
			inline ConnectionIterator end() const { return connections.end(); }
			
			// ClientConnectionCallbacks
			
			virtual int onConnect(ClientConnection *conn, const std::string &version, const std::string &username, const std::string &authmsg);
			virtual void onError(BaseConnection *conn, const std::string &error);
			
		private:
			PlayerList &players;
			mge::NetworkSystem *net;
		
			ConnectionList connections;
	};
}

#endif
