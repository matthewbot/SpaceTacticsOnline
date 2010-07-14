#ifndef STO_SHARED_CONNECTREFUSEDPACKET_H
#define STO_SHARED_CONNECTREFUSEDPACKET_H

#include "Packet.h"
#include <string>

namespace sto {
	class ConnectRefusedPacket : public Packet {
		public:
			ConnectRefusedPacket();
			ConnectRefusedPacket(const std::string &msg);
			virtual ~ConnectRefusedPacket();
		
			inline const std::string &getMessage() { return msg; }
		
			virtual void pack(mge::Blob &blob) const;
			virtual void unpack(mge::Blob &blob);
			
		private:
			std::string msg;
	};
}

#endif
