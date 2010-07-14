#ifndef STO_SHARED_PLAYERIDPACKET_H
#define STO_SHARED_PLAYERIDPACKET_H

#include "Packet.h"
#include <string>

namespace sto {
	class PlayerIDPacket : public Packet {
		public:
			PlayerIDPacket();
			PlayerIDPacket(int playerid);
			virtual ~PlayerIDPacket();
		
			inline int getPlayerID() const { return playerid; }
		
			virtual void pack(mge::Blob &blob) const;
			virtual void unpack(mge::Blob &blob);
			
		private:
			int playerid;
	};
}

#endif
