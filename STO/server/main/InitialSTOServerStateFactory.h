#ifndef STO_SERVER_INITIALSTOSERVERSTATEFACTORY_H
#define STO_SERVER_INITIALSTOSERVERSTATEFACTORY_H

#include <MGE/state/InitialGameStateFactory.h>
#include "ServerStateSystems.h"
#include <cassert>

namespace sto {
	template <class ServerStateT> class InitialSTOServerStateFactory : public mge::InitialGameStateFactory {
		public:
			InitialSTOServerStateFactory() { }
			virtual ~InitialSTOServerStateFactory() { }
			
			virtual mge::GameState *makeGameState(mge::Logger &log, const mge::KernelSystemMap &systems) {
				ServerStateSystems serversystems;
				
				mge::KernelSystemMap::const_iterator i = systems.find("ResourceSystem");
				assert(i != systems.end());
				serversystems.res = (mge::ResourceSystem *)i->second;
				
				i = systems.find("NetworkSystem");
				assert(i != systems.end());
				serversystems.net = (mge::NetworkSystem *)i->second;
				
				i = systems.find("FrameRateLimiter");
				assert(i != systems.end());
				serversystems.fps = (mge::FrameRateLimiter *)i->second;
				
				serversystems.log = &log;
				
				return new ServerStateT(serversystems);
			}
	};
}

#endif
