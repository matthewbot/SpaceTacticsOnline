#ifndef STO_SERVER_CLIENTCONNECTIONCALLBACKS_H
#define STO_SERVER_CLIENTCONNECTIONCALLBACKS_H

#include <STO/shared/net/BaseConnectionCallbacks.h>
#include <STO/shared/input/FlightInput.h>
#include <string>

namespace sto {
	class ClientConnection;

	class ClientConnectionCallbacks : public BaseConnectionCallbacks {
		public:
			inline virtual ~ClientConnectionCallbacks() { }
			
			virtual int onConnect(ClientConnection *conn, const std::string &version, const std::string &username, const std::string &authmsg) = 0;
	};
}

#endif
