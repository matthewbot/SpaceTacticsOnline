#ifndef STO_SERVER_CLIENTCONNECTIONLIST_H
#define STO_SERVER_CLIENTCONNECTIONLIST_H

#include "ClientConnectionCallbacks.h"
#include <boost/shared_ptr.hpp>
#include <list>
#include <vector>

namespace mge {
	class NetworkSystem;
	class Logger;
	class Blob;
}

namespace sto {
	class PlayerList;
	class ClientConnection;

	class ClientConnectionManager : public ClientConnectionCallbacks {
		typedef std::list<boost::shared_ptr<ClientConnection> > ConnectionList;
	
		public:
			typedef ConnectionList::const_iterator ConnectionIterator;
		
			ClientConnectionManager(PlayerList &players, mge::NetworkSystem *net, mge::Logger *log);
			~ClientConnectionManager();
			
			void broadcastEntityCreate(int id, const std::string &entityname, const mge::Blob &blob);
			void broadcastEntityUpdate(int id, bool full, bool remove, const mge::Blob &update);

			void update();
			
			inline ConnectionIterator begin() const { return connections.begin(); }
			inline ConnectionIterator end() const { return connections.end(); }
			
			// ClientConnectionCallbacks
			
			virtual void onConnectRefused(ClientConnection *conn, const std::string &reason);
			virtual boost::shared_ptr<Player> onConnect(ClientConnection *conn, const std::string &version, const std::string &username, const std::string &authmsg);
			virtual void onDisconnect(BaseConnection *conn);
			virtual void onError(BaseConnection *conn, const std::string &error);
			
		private:
			void removeLater(ClientConnection *conn);
		
			PlayerList &players;
			mge::NetworkSystem *net;
			mge::Logger *log;
		
			ConnectionList connections;
			std::vector<ClientConnection *> connections_remove;
			int nextplayerid;
	};
}

#endif
