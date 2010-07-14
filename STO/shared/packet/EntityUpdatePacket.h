#ifndef STO_SHARED_ENTITYUPDATEPACKET_H
#define STO_SHARED_ENTITYUPDATEPACKET_H

#include "Packet.h"
#include <MGE/util/Blob.h>
#include <string>

namespace sto {
	class EntityUpdatePacket : public Packet {
		public:
			EntityUpdatePacket();
			EntityUpdatePacket(int id, bool full, bool remove, const mge::Blob &update);
			virtual ~EntityUpdatePacket();
		
			inline int getEntityID() const { return id; }
			inline bool isFullUpdate() const { return full; }
			inline bool isRemove() const { return remove; }
			inline const mge::Blob &getUpdateBlob() const { return update; }
		
			virtual void pack(mge::Blob &blob) const;
			virtual void unpack(mge::Blob &blob);
			
		private:
			int id;
			bool full;
			bool remove;
			mge::Blob update;
	};
}


#endif
