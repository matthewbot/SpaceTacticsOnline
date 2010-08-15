#ifndef STO_SERVER_CLIENTMANAGER_H
#define STO_SERVER_CLIENTMANAGER_H

#include "ClientCallbacks.h"
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
	class Client;

	class ClientManager : public ClientCallbacks {
		typedef std::list<boost::shared_ptr<Client> > ConnectionList;
	
		public:
			typedef ConnectionList::const_iterator ConnectionIterator;
		
			ClientManager(PlayerList &players, mge::NetworkSystem *net, mge::Logger *log);
			~ClientManager();
			
			void broadcastEntityCreate(int id, const std::string &entityname, const mge::Blob &blob);
			void broadcastEntityUpdate(int id, bool full, bool remove, const mge::Blob &update);

			void update();
			
			inline ConnectionIterator begin() const { return connections.begin(); }
			inline ConnectionIterator end() const { return connections.end(); }
			
			// ClientCallbacks
			
			virtual void onConnectRefused(Client *conn, const std::string &reason);
			virtual boost::shared_ptr<Player> onConnect(Client *conn, const std::string &version, const std::string &username, const std::string &authmsg);
			virtual void onDisconnect(BaseClientServer *conn);
			virtual void onError(BaseClientServer *conn, const std::string &error);
			
		private:
			void removeLater(Client *conn);
		
			PlayerList &players;
			mge::NetworkSystem *net;
			mge::Logger *log;
		
			ConnectionList connections;
			std::vector<Client *> connections_remove;
			int nextplayerid;
	};
}

#endif
