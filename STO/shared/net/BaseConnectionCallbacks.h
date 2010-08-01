#ifndef STO_SHARED_BASECONNECTIONCALLBACKS_H
#define STO_SHARED_BASECONNECTIONCALLBACKS_H

#include <string>

namespace sto {
	class BaseConnection;

	class BaseConnectionCallbacks {
		public:
			inline virtual ~BaseConnectionCallbacks() { }
			virtual void onError(BaseConnection *conn, const std::string &error) = 0;
			virtual void onDisconnect(BaseConnection *conn) = 0;
	};
}

#endif
