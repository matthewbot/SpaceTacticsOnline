#ifndef STO_SHARED_CONNECTPACKET_H
#define STO_SHARED_CONNECTPACKET_H

#include "Packet.h"
#include <string>

namespace sto {
	class ConnectPacket : public Packet {
		public:
			ConnectPacket();
			ConnectPacket(const std::string &version, const std::string &username, const std::string &authmsg);
			virtual ~ConnectPacket();
		
			inline const std::string &getVersion() { return version; }
			inline const std::string &getUsername() { return username; }
			inline const std::string &getAuthmsg() { return authmsg; }
		
			virtual void pack(mge::Blob &blob) const;
			virtual void unpack(mge::Blob &blob);
			
		private:
			std::string version;
			std::string username;
			std::string authmsg;
	};
}

#endif
