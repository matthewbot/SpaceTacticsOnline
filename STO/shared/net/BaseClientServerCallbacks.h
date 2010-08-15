#ifndef STO_SHARED_BASECLIENTSERVERCALLBACKS_H
#define STO_SHARED_BASECLIENTSERVERCALLBACKS_H

#include <string>

namespace sto {
	class BaseClientServer;

	class BaseClientServerCallbacks {
		public:
			virtual void onError(BaseClientServer *conn, const std::string &error) = 0;
			virtual void onDisconnect(BaseClientServer *conn) = 0;
	};
}

#endif
