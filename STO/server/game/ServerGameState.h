#ifndef STO_SERVER_SERVERGAMESTATE_H
#define STO_SERVER_SERVERGAMESTATE_H

#include <STO/server/player/PlayerList.h>
#include <STO/server/net/ClientConnectionList.h>
#include <STO/server/main/ServerStateSystems.h>
#include <MGE/state/GameState.h>

namespace sto {
	class ServerGameState : public mge::GameState {
		public:
			ServerGameState(const ServerStateSystems &systems);
			
			virtual mge::GameStateStatus update();
			
		private:
			ServerStateSystems systems;
			PlayerList players;
			ClientConnectionList connections;
	};
}

#endif
