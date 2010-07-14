#ifndef STO_CLIENT_CLIENTSTATESYSTEMS_H
#define STO_CLIENT_CLIENTSTATESYSTEMS_H

namespace mge {
	class GraphicsSystem;
	class ResourceSystem;
	class NetworkSystem;
	class Logger;
}

namespace sto {
	struct ClientStateSystems {
		mge::GraphicsSystem *gfx;
		mge::ResourceSystem *res;
		mge::NetworkSystem *net;
		mge::Logger *log;
	};
}

#endif
