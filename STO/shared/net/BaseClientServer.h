#ifndef STO_SHARED_BASECLIENTSERVER_H
#define STO_SHARED_BASECLIENTSERVER_H

#include "BaseClientServerCallbacks.h"
#include <STO/shared/packet/PacketConnection.h>
#include <string>
#include <memory>

namespace sto {
	class BaseClientServer {
		public:
			BaseClientServer(BaseClientServerCallbacks &callbacks);
			inline ~BaseClientServer() { disconnect(); }
			
			void update();
		
			enum State { ESTABLISHING, CONNECTING, CONNECTED, DISCONNECTED, ERROR };
			inline State getState() { return state; }
			inline const std::string &getErrorMsg() { return errmsg; }
			inline int getPing() const { return conn->getPing(); }
			inline std::string getIP() const { return conn->getIP(); }
			
			void disconnect();
			
			static std::string stateToString(State st);
			
		protected:
			virtual void connectionEstablished();
			virtual void processPacket(Packet *packet) = 0;
			void setError(const std::string &msg);
			inline PacketConnection &getConn() { return *conn; }
			inline bool hasConn() { return conn.get(); }
			void setConn(PacketConnection *newconn);
			
			State state;
			
		private:
			std::auto_ptr<PacketConnection> conn;
			std::string errmsg;
			BaseClientServerCallbacks &callbacks;
	};
}

#endif
