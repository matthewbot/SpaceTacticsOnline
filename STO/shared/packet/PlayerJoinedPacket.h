#ifndef STO_SHARED_PLAYERJOINEDPACKET_H
#define STO_SHARED_PLAYERJOINEDPACKET_H

#include "Packet.h"
#include <string>

namespace sto {
	class PlayerJoinedPacket : public Packet {
		public:
			PlayerJoinedPacket();
			PlayerJoinedPacket(int id, int tamid, const std::string &username);
			virtual ~PlayerJoinedPacket();
		
			inline int getID() const { return id; }
			inline int getTeamID() const { return teamid; }
			inline const std::string &getUsername() const { return username; }
		
			virtual void pack(mge::Blob &blob) const;
			virtual void unpack(mge::Blob &blob);
			
		private:
			int id;
			int teamid;
			std::string username;
	};
}


#endif
