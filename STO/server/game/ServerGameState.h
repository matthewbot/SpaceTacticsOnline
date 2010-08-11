#ifndef STO_SERVER_SERVERGAMESTATE_H
#define STO_SERVER_SERVERGAMESTATE_H

#include <STO/server/net/ClientConnectionManager.h>
#include <STO/server/main/ServerStateSystems.h>
#include <STO/shared/entity/EntityContainer.h>
#include <STO/shared/player/PlayerList.h>
#include <MGE/state/GameState.h>
#include <boost/smart_ptr.hpp>
#include <map>
#include <string>

namespace sto {
	class SerializeComponent;
	class FlightInputComponent;

	class ServerGameState : public mge::GameState {
		public:
			ServerGameState(const ServerStateSystems &systems);
			
			void spawnPlayerEntity(const std::string &buildername, const boost::shared_ptr<Player> &player);
			
			virtual mge::GameStateStatus update();
			
		private:
			ServerStateSystems systems;
			PlayerList players;
			ClientConnectionManager connections;
			
			EntityContainer entities;
			typedef std::map<int, boost::weak_ptr<SerializeComponent> > SerializeEntityMap;
			SerializeEntityMap serialize_entities;
			typedef std::map<int, boost::weak_ptr<FlightInputComponent> > PlayerInputMap;
			PlayerInputMap flightinput_entities;
			int nextid;
	};
}

#endif
