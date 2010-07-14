#include "ClientConnectionList.h"
#include "ClientConnection.h"
#include <STO/server/player/Player.h>
#include <STO/server/player/PlayerList.h>
#include <MGE/net/NetworkSystem.h>

using namespace sto;
using namespace mge;
using namespace boost;
using namespace std;

ClientConnectionList::ClientConnectionList(PlayerList &players, mge::NetworkSystem *net) : players(players), net(net) { }
ClientConnectionList::~ClientConnectionList() { }

void ClientConnectionList::update() {
	while (net->connectionAvailable()) {
		boost::shared_ptr<ClientConnection> conn(new ClientConnection(*this, net->acceptConnection()));
		connections.push_back(conn);
	}
	
	for (ConnectionList::iterator i = connections.begin(); i != connections.end(); ++i) {
		(*i)->update();
	}
}

int ClientConnectionList::onConnect(ClientConnection *conn, const std::string &version, const std::string &username, const std::string &authmsg) {
	shared_ptr<Player> player = players.newPlayer(username, conn, players.findSmallestTeam());
	return player->getID();
}

void ClientConnectionList::onError(BaseConnection *conn, const std::string &msg) { }


