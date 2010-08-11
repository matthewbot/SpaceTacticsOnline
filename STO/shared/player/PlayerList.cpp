#include "PlayerList.h"

using namespace sto;
using namespace mge;
using namespace std;

PlayerList::PlayerList() { }

PlayerList::PlayerPtr PlayerList::newPlayer(Player::ID id, const string &name, const TeamPtr &team) {
	PlayerPtr player(new Player(id, name));
	players.insert(player);
	teamplayersmap[team].insert(player);
	playerteammap.insert(make_pair(player, team));
	
	return player;
}

PlayerList::TeamPtr PlayerList::newTeam(Team::ID id, const string &name, const Color &color) {
	TeamPtr team(new Team(id++, name, color));
	teams.insert(team);
	teamplayersmap.insert(make_pair(team, PlayerSet()));
	return team;
}

std::pair<PlayerList::PlayerIterator, PlayerList::PlayerIterator> PlayerList::getPlayersByTeam(const boost::shared_ptr<Team> &team) const {
	TeamPlayersMap::const_iterator i = teamplayersmap.find(team);
	return make_pair(i->second.begin(), i->second.end());
}

int PlayerList::getPlayerCountByTeam(const boost::shared_ptr<Team> &team) const {
	TeamPlayersMap::const_iterator i = teamplayersmap.find(team);
	return i->second.size();
}

PlayerList::TeamPtr PlayerList::findSmallestTeam() const {
	TeamPtr smallest;
	int smallestsize = -1;
	
	for (TeamPlayersMap::const_iterator i = teamplayersmap.begin(); i != teamplayersmap.end(); ++i) {
		int size = i->second.size();
		
		if (smallestsize < size) {
			smallestsize = size;
			smallest = i->first;
		}
	}
	
	return smallest;
}

boost::shared_ptr<Team> PlayerList::getPlayersTeam(const boost::shared_ptr<Player> &player) const {
	PlayerTeamMap::const_iterator i = playerteammap.find(player);
	return i->second;
}


