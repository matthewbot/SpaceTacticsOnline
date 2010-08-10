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
	class PlayerListCallbacks {
		public:
			virtual void playerJoined(const boost::shared_ptr<Player> &player) = 0;
			virtual void playerLeft(const boost::shared_ptr<Player> &player) = 0;
	};

	class PlayerList {
			typedef boost::shared_ptr<Player> PlayerPtr;
			typedef boost::shared_ptr<Team> TeamPtr;

			template <typename T> struct CompareByNamePtr {
				inline bool operator()(const T &a, const T &b) const {
					return a->getName() < b->getName();
				}
			};
		
			typedef std::set<PlayerPtr, CompareByNamePtr<PlayerPtr> > PlayerSet;
			typedef std::set<TeamPtr, CompareByNamePtr<TeamPtr> > TeamSet;
			typedef std::map<TeamPtr, PlayerSet, CompareByNamePtr<TeamPtr> > TeamPlayersMap;
			typedef std::map<PlayerPtr, TeamPtr, CompareByNamePtr<PlayerPtr> > PlayerTeamMap;
	
		public:	
			typedef PlayerSet::const_iterator PlayerIterator;
			typedef TeamSet::const_iterator TeamIterator;
		
			PlayerList(PlayerListCallbacks &callbacks);
		
			boost::shared_ptr<Player> newPlayer(Player::ID id, const std::string &name, const TeamPtr &team);
			boost::shared_ptr<Team> newTeam(Team::ID id, const std::string &name, const mge::Color &color);
			void removePlayer(const boost::shared_ptr<Player> &player);
		
			inline PlayerIterator beginPlayers() const { return players.begin(); }
			inline PlayerIterator endPlayers() const { return players.end(); }
			
			inline TeamIterator beginTeams() const { return teams.begin(); }
			inline TeamIterator endTeams() const { return teams.end(); }
			
			std::pair<PlayerIterator, PlayerIterator> getPlayersByTeam(const boost::shared_ptr<Team> &team) const;
			int getPlayerCountByTeam(const boost::shared_ptr<Team> &team) const;
			boost::shared_ptr<Team> getPlayersTeam(const boost::shared_ptr<Player> &player) const;
					
			boost::shared_ptr<Team> findSmallestTeam() const;
			
		private:
			PlayerListCallbacks &callbacks;
			PlayerSet players;	
			TeamSet teams;
			TeamPlayersMap teamplayersmap;
			PlayerTeamMap playerteammap;
	};
}

#endif
