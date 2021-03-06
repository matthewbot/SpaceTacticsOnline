#ifndef STO_SERVER_SERVERSTATESYSTEMS_H
#define STO_SERVER_SERVERSTATESYSTEMS_H

namespace mge {
	class ResourceSystem;
	class NetworkSystem;
	class Logger;
	class FrameRateLimiter;
}

namespace sto {
	struct ServerStateSystems {
		mge::ResourceSystem *res;
		mge::NetworkSystem *net;
		mge::Logger *log;
		mge::FrameRateLimiter *fps;
	};
}

#endif
