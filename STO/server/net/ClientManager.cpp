#include "ClientManager.h"
#include "Client.h"
#include <STO/shared/player/Player.h>
#include <STO/shared/player/PlayerList.h>
#include <MGE/net/NetworkSystem.h>
#include <MGE/util/Logger.h>
#include <boost/lambda/lambda.hpp>
#include <boost/lambda/bind.hpp>
#include <algorithm>

using namespace sto;
using namespace mge;
using namespace boost;
using namespace boost::lambda;
using namespace std;

ClientManager::ClientManager(PlayerList &players, NetworkSystem *net, Logger *log)
: players(players), net(net), log(log), nextplayerid(1) { }
ClientManager::~ClientManager() { }

void ClientManager::broadcastEntityCreate(int id, const std::string &entityname, const mge::Blob &update) {
	for (ConnectionList::iterator i = connections.begin(); i != connections.end(); ++i)
		(*i)->sendEntityCreate(id, entityname, update);
}

void ClientManager::broadcastEntityUpdate(int id, bool full, bool remove, const mge::Blob &update) {
	for (ConnectionList::iterator i = connections.begin(); i != connections.end(); ++i)
		(*i)->sendEntityUpdate(id, full, remove, update);
}

void ClientManager::update() {
	// accept new connections
	while (net->connectionAvailable()) {
		boost::shared_ptr<Client> conn(new Client(*this, net->acceptConnection()));
		connections.push_back(conn);
	}
	
	// update existing ones
	for (ConnectionList::iterator i = connections.begin(); i != connections.end(); ++i) {
		(*i)->update();
	}
	
	// remove those queued for removal
	for (vector<Client *>::iterator i = connections_remove.begin(); i != connections_remove.end(); ++i) {
		ConnectionList::iterator pos = find_if(connections.begin(), connections.end(), bind(&boost::shared_ptr<Client>::get, _1) == *i);
		assert(pos != connections.end());
		connections.erase(pos);
	}
	
	connections_remove.clear();
}

void ClientManager::onConnectRefused(Client *conn, const std::string &reason) {
	log->log("main", INFO) << "Connection from " << conn->getIP() << " refused: " << reason << endl;
	removeLater(conn);
}

shared_ptr<Player> ClientManager::onConnect(Client *conn, const std::string &version, const std::string &username, const std::string &authmsg) {
	shared_ptr<Team> team = players.findSmallestTeam();
	int id = nextplayerid++;
	
	boost::shared_ptr<Player> player = players.newPlayer(id, username, team);
	
	for (ConnectionList::iterator i = connections.begin(); i != connections.end(); ++i)
		(*i)->sendPlayerJoined(id, team->getID(), username);
	
	log->log("main", INFO) << "Connection from " << conn->getIP() << " joined as '" << username << "' on team '" << team->getName() << "'" << endl;
	
	return player;
}

void ClientManager::onDisconnect(BaseClientServer *bconn) {
	Client *conn = static_cast<Client *>(bconn);
	if (conn->getPlayer()) {
		log->log("main", INFO) << "'" << conn->getPlayer()->getName() << "' disconnected" << endl;
		for (ConnectionList::iterator i = connections.begin(); i != connections.end(); ++i)
			(*i)->sendPlayerLeft(conn->getPlayer()->getID());
	} else
		log->log("main", INFO) << "Connection from " << conn->getIP() << " disconnected before authenticating" << endl;
	removeLater(conn);
}

void ClientManager::onError(BaseClientServer *bconn, const std::string &msg) {
	Client *conn = static_cast<Client *>(bconn);
	log->log("main", INFO) << "'" << conn->getPlayer()->getName() << "' disconnected due to error: " << msg << endl;
	removeLater(conn);
}

void ClientManager::removeLater(Client *conn) {
	connections_remove.push_back(conn);
}


