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
			typedef boost::shared_ptr<Player> PlayerPtr;
			typedef boost::shared_ptr<Team> TeamPtr;

			template <typename T> struct CompareByNamePtr {
				inline bool operator()(const T &a, const T &b) const {
					return a->getName() < b->getName();
				}
			};
		
			typedef std::map<int, PlayerPtr> PlayerMap;
			typedef std::map<int, TeamPtr> TeamMap;
			typedef std::set<PlayerPtr, CompareByNamePtr<PlayerPtr> > PlayerSet;
			typedef std::map<TeamPtr, PlayerSet> TeamPlayersMap;
			typedef std::map<PlayerPtr, TeamPtr, CompareByNamePtr<PlayerPtr> > PlayerTeamMap;
	
		public:	
			typedef PlayerMap::const_iterator PlayerIterator;
			typedef TeamMap::const_iterator TeamIterator;
		
			PlayerList();
		
			boost::shared_ptr<Player> newPlayer(Player::ID id, const std::string &name, const TeamPtr &team);
			boost::shared_ptr<Team> newTeam(Team::ID id, const std::string &name, const mge::Color &color);
			void removePlayer(const boost::shared_ptr<Player> &player);
		
			inline PlayerIterator beginPlayers() const { return players.begin(); }
			inline PlayerIterator endPlayers() const { return players.end(); }
			
			inline TeamIterator beginTeams() const { return teams.begin(); }
			inline TeamIterator endTeams() const { return teams.end(); }
	
			boost::shared_ptr<Player> getPlayerById(int id);			
			boost::shared_ptr<Team> getTeamById(int id);
			int getPlayerCountByTeam(const boost::shared_ptr<Team> &team) const;
			boost::shared_ptr<Team> getPlayersTeam(const boost::shared_ptr<Player> &player) const;
					
			boost::shared_ptr<Team> findSmallestTeam() const;
			
		private:
			PlayerMap players;	
			TeamMap teams;
			TeamPlayersMap teamplayersmap;
			PlayerTeamMap playerteammap;
	};
}

#endif
