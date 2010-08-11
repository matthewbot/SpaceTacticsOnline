#ifndef STO_SHARED_PLAYERLEFTPACKET_H
#define STO_SHARED_PLAYERLEFTPACKET_H

#include "Packet.h"
#include <STO/shared/player/Player.h>

namespace sto {
	class PlayerLeftPacket : public Packet {
		public:
			PlayerLeftPacket();
			PlayerLeftPacket(Player::ID id);
			virtual ~PlayerLeftPacket();
		
			inline Player::ID getID() const { return id; }
		
			virtual void pack(mge::Blob &blob) const;
			virtual void unpack(mge::Blob &blob);
			
		private:
			Player::ID id;
	};
}


#endif
