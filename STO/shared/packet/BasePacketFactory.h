#ifndef STO_SHARED_BASEPACKETFACTORY_H
#define STO_SHARED_BASEPACKETFACTORY_H

#include "PacketFactory.h"

namespace sto {
	template <typename PacketT, int ID> class BasePacketFactory : public PacketFactory {
		public:
			BasePacketFactory() { }
			
			virtual int getID() const { return ID; }
			virtual Packet *makePacket() { return new PacketT(); }
			virtual bool isMatch(const Packet &packet, const std::type_info &packettype) { return packettype == typeid(PacketT); }
	};
}

#endif
