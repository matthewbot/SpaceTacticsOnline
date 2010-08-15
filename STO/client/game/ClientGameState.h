#ifndef STO_CLIENT_CLIENTGAMESTATE_H
#define STO_CLIENT_CLIENTGAMESTATE_H

#include "PlayerEntityHolder.h"
#include <STO/client/net/Server.h>
#include <STO/client/net/ServerCallbacks.h>
#include <STO/client/main/ClientStateSystems.h>
#include <STO/shared/entity/EntityContainer.h>
#include <STO/shared/serial/SerializeComponent.h>
#include <STO/shared/player/PlayerList.h>
#include <MGE/state/GameState.h>
#include <MGE/util/input/InputAccumulator.h>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <map>

namespace mge {
	class ResourceSystem;
	class Font;
}

namespace sto {
	class RenderComponentSystem;
	class FlightInput;

	class ClientGameState : public mge::GameState, private ServerCallbacks {
		public:
			ClientGameState(const ClientStateSystems &systems);
			~ClientGameState();
			
			virtual mge::GameStateStatus update();
			
		private:
		    FlightInput getInput();
		
			ClientStateSystems systems;
			mge::InputAccumulator input;
			
			EntityContainer entities;
			typedef std::map<int, boost::weak_ptr<SerializeComponent> > SerializeEntityMap;
			SerializeEntityMap serialize_entities;
			boost::shared_ptr<RenderComponentSystem> rendersys;
			PlayerEntityHolder player;
			
			Server serverconn;
			PlayerList players;
			
			boost::shared_ptr<mge::Font> debugfont;
			
			// --- ServerCallback ---
			
			virtual void onConnect();
			virtual void onDisconnect(BaseClientServer *conn);
            virtual void onError(BaseClientServer *conn, const std::string &error);
            virtual void onCreateEntity(int id, const std::string &name, const mge::Blob &update);
            virtual void onUpdateEntity(int id, const mge::Blob &update, bool isfull);
            virtual void onPlayerJoined(int id, int teamid, const std::string &username);
            virtual void onPlayerLeft(int id);
	};
}

#endif
