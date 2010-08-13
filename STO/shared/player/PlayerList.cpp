#include "PlayerList.h"

using namespace sto;
using namespace mge;
using namespace boost;
using namespace std;

PlayerList::PlayerList() { }

PlayerList::PlayerPtr PlayerList::newPlayer(Player::ID id, const string &name, const TeamPtr &team) {
	PlayerPtr player(new Player(id, name));
	players.insert(make_pair(id, player));
	teamplayersmap[team].insert(player);
	playerteammap.insert(make_pair(player, team));
	
	return player;
}

void PlayerList::removePlayer(const shared_ptr<Player> &player) {
	int id = player->getID();
	shared_ptr<Team> team = getPlayersTeam(player);
	players.erase(id);
	teamplayersmap[team].erase(player);
	playerteammap.erase(player);
}

PlayerList::TeamPtr PlayerList::newTeam(Team::ID id, const string &name, const Color &color) {
	TeamPtr team(new Team(id++, name, color));
	teams.insert(make_pair(id, team));
	teamplayersmap.insert(make_pair(team, PlayerSet()));
	return team;
}

shared_ptr<Player> PlayerList::getPlayerById(int id) {
	PlayerMap::const_iterator i = players.find(id);
	if (i != players.end())
		return i->second;
	else
		return shared_ptr<Player>();
}

shared_ptr<Team> PlayerList::getTeamById(int id) {
	TeamMap::const_iterator i = teams.find(id);
	if (i != teams.end())
		return i->second;
	else
		return shared_ptr<Team>();
}

int PlayerList::getPlayerCountByTeam(const shared_ptr<Team> &team) const {
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

shared_ptr<Team> PlayerList::getPlayersTeam(const shared_ptr<Player> &player) const {
	PlayerTeamMap::const_iterator i = playerteammap.find(player);
	return i->second;
}


