#ifndef STO_SERVER_PLAYERLIST_H
#define STO_SERVER_PLAYERLIST_H

#include "Player.h"
#include "Team.h"
#include <boost/weak_ptr.hpp>
#include <boost/shared_ptr.hpp>
#include <map>
#include <set>
#include <utility>

namespace sto {
	class PlayerList {
		public:
			typedef boost::shared_ptr<Player> PlayerPtr;
			typedef boost::shared_ptr<Team> TeamPtr;
			
		private:
			template <typename T> struct CompareByNamePtr {
				inline bool operator()(const T &a, const T &b) const {
					return a->getName() < b->getName();
				}
			};
		
			typedef std::set<PlayerPtr, CompareByNamePtr<PlayerPtr> > PlayerSet;
			typedef std::set<TeamPtr, CompareByNamePtr<TeamPtr> > TeamSet;
			typedef std::map<TeamPtr, PlayerSet, CompareByNamePtr<TeamPtr> > TeamMap;
	
		public:	
			typedef PlayerSet::const_iterator PlayerIterator;
			typedef TeamSet::const_iterator TeamIterator;
		
			PlayerList();
		
			PlayerPtr newPlayer(const std::string &name, PlayerController *controller, const TeamPtr &team);
			TeamPtr newTeam(const std::string &name, const mge::Color &color);
		
			inline PlayerIterator beginPlayers() const { return players.begin(); }
			inline PlayerIterator endPlayers() const { return players.end(); }
			
			inline TeamIterator beginTeams() const { return teams.begin(); }
			inline TeamIterator endTeams() const { return teams.end(); }
			
			std::pair<PlayerIterator, PlayerIterator> getPlayersByTeam(TeamPtr team) const;
			int getPlayerCountByTeam(TeamPtr team) const;
					
			TeamPtr findSmallestTeam() const;
			
		private:
			PlayerSet players;	
			TeamSet teams;
			TeamMap teammap;
			
			Player::ID nextplayerid;
			Team::ID nextteamid;
	};
}

#endif
