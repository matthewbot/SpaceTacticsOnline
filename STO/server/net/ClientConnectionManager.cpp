#include "ClientConnectionManager.h"
#include "ClientConnection.h"
#include <STO/server/player/Player.h>
#include <STO/server/player/PlayerList.h>
#include <MGE/net/NetworkSystem.h>
#include <MGE/util/Logger.h>

using namespace sto;
using namespace mge;
using namespace boost;
using namespace std;

ClientConnectionManager::ClientConnectionManager(PlayerList &players, NetworkSystem *net, Logger *log) : players(players), net(net), log(log) { }
ClientConnectionManager::~ClientConnectionManager() { }

void ClientConnectionManager::update() {
	while (net->connectionAvailable()) {
		boost::shared_ptr<ClientConnection> conn(new ClientConnection(*this, net->acceptConnection()));
		connections.push_back(conn);
	}
	
	for (ConnectionList::iterator i = connections.begin(); i != connections.end(); ++i) {
		(*i)->update();
	}
}

int ClientConnectionManager::onConnect(ClientConnection *conn, const std::string &version, const std::string &username, const std::string &authmsg) {
	shared_ptr<Team> team = players.findSmallestTeam();
	shared_ptr<Player> player = players.newPlayer(username, conn, team);
	
	log->log("main", INFO) << "New player '" << username << "' joined team " << team->getName() << endl;
	
	return player->getID();
}

void ClientConnectionManager::onError(BaseConnection *conn, const std::string &msg) {
	log->log("main", INFO) << "Connection error: " << msg << endl;
}

