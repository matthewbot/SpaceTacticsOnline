#ifndef STO_CLIENT_CLIENTGAMESTATE_H
#define STO_CLIENT_CLIENTGAMESTATE_H

#include "PlayerEntityHolder.h"
#include <STO/client/net/ServerConnection.h>
#include <STO/client/net/ServerConnectionCallbacks.h>
#include <STO/client/main/ClientStateSystems.h>
#include <STO/shared/entity/EntityContainer.h>
#include <STO/shared/serial/SerializeComponent.h>
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

	class ClientGameState : public mge::GameState, private ServerConnectionCallbacks {
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
			
			ServerConnection serverconn;
			
			boost::shared_ptr<mge::Font> debugfont;
			
			// --- ServerConnectionCallback ---
			
			virtual void onConnect();
			virtual void onDisconnect(BaseConnection *conn);
            virtual void onError(BaseConnection *conn, const std::string &error);
            virtual void onCreateEntity(int id, const std::string &name, const mge::Blob &update);
            virtual void onUpdateEntity(int id, const mge::Blob &update, bool isfull);
	};
}

#endif
