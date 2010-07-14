#include "PlayerList.h"

using namespace sto;
using namespace mge;
using namespace std;

PlayerList::PlayerList() : nextplayerid(1), nextteamid(1) { }

PlayerList::PlayerPtr PlayerList::newPlayer(const string &name, PlayerController *controller, const TeamPtr &team) {
	PlayerPtr player(new Player(nextplayerid++, name, controller));
	players.insert(player);
	teammap[team].insert(player);
	return player;
}

PlayerList::TeamPtr PlayerList::newTeam(const string &name, const Color &color) {
	TeamPtr team(new Team(nextteamid++, name, color));
	teams.insert(team);
	teammap.insert(make_pair(team, PlayerSet()));
	return team;
}

std::pair<PlayerList::PlayerIterator, PlayerList::PlayerIterator> PlayerList::getPlayersByTeam(TeamPtr team) const {
	TeamMap::const_iterator i = teammap.find(team);
	return make_pair(i->second.begin(), i->second.end());
}

int PlayerList::getPlayerCountByTeam(TeamPtr team) const {
	TeamMap::const_iterator i = teammap.find(team);
	return i->second.size();
}

PlayerList::TeamPtr PlayerList::findSmallestTeam() const {
	TeamPtr smallest;
	int smallestsize = -1;
	
	for (TeamMap::const_iterator i = teammap.begin(); i != teammap.end(); ++i) {
		int size = i->second.size();
		
		if (smallestsize < size) {
			smallestsize = size;
			smallest = i->first;
		}
	}
	
	return smallest;
}

