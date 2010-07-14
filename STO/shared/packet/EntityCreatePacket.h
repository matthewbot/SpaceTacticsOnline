#ifndef STO_SHARED_ENTITYCREATEPACKET_H
#define STO_SHARED_ENTITYCREATEPACKET_H

#include "Packet.h"
#include <MGE/util/Blob.h>
#include <string>

namespace sto {
	class EntityCreatePacket : public Packet {
		public:
			EntityCreatePacket();
			EntityCreatePacket(int id, const std::string &entityname, const mge::Blob &update);
			virtual ~EntityCreatePacket();
		
			inline int getEntityID() const { return id; }
			inline const std::string &getEntityName() const { return entityname; }
			inline const mge::Blob &getUpdateBlob() const { return update; }
		
			virtual void pack(mge::Blob &blob) const;
			virtual void unpack(mge::Blob &blob);
			
		private:
			int id;
			std::string entityname;
			mge::Blob update;
	};
}


#endif
