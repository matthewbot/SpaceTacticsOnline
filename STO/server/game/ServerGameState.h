#ifndef STO_SERVER_SERVERGAMESTATE_H
#define STO_SERVER_SERVERGAMESTATE_H

#include <STO/server/player/PlayerList.h>
#include <STO/server/net/ClientConnectionManager.h>
#include <STO/server/main/ServerStateSystems.h>
#include <STO/shared/entity/EntityContainer.h>
#include <MGE/state/GameState.h>
#include <boost/smart_ptr.hpp>

namespace sto {
	class SerializeComponent;
	class FlightInputComponent;

	class ServerGameState : public mge::GameState {
		public:
			ServerGameState(const ServerStateSystems &systems);
			
			virtual mge::GameStateStatus update();
			
		private:
			ServerStateSystems systems;
			PlayerList players;
			ClientConnectionManager connections;
	};
}

#endif
