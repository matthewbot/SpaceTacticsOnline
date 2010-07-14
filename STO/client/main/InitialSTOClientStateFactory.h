#ifndef STO_CLIENT_INITIALSTOCLIENTSTATEFACTORY_H
#define STO_CLIENT_INITIALSTOCLIENTSTATEFACTORY_H

#include <MGE/state/InitialGameStateFactory.h>
#include "ClientStateSystems.h"
#include <cassert>

namespace sto {
	template <class ClientStateT> class InitialSTOClientStateFactory : public mge::InitialGameStateFactory {
		public:
			InitialSTOClientStateFactory() { }
			virtual ~InitialSTOClientStateFactory() { }
			
			virtual mge::GameState *makeGameState(mge::Logger &log, const mge::KernelSystemMap &systems) {
				ClientStateSystems clientsystems;
				
				mge::KernelSystemMap::const_iterator i = systems.find("GraphicsSystem"); // template trickery could possibly make this shorter
				assert(i != systems.end());
				clientsystems.gfx = (mge::GraphicsSystem *)i->second;
				
				i = systems.find("ResourceSystem");
				assert(i != systems.end());
				clientsystems.res = (mge::ResourceSystem *)i->second;
				
				i = systems.find("NetworkSystem");
				assert(i != systems.end());
				clientsystems.net = (mge::NetworkSystem *)i->second;
				
				clientsystems.log = &log;
				
				return new ClientStateT(clientsystems);
			}
	};
}

#endif
