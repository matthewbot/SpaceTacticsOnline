#ifndef STO_SHARED_PACKETFACTORY_H
#define STO_SHARED_PACKETFACTORY_H

#include <typeinfo>

namespace sto {
	class Packet;

	class PacketFactory {
		public:
			inline virtual ~PacketFactory() { }
			
			virtual int getID() const = 0;
			virtual Packet *makePacket() = 0;
			virtual bool isMatch(const Packet &packet, const std::type_info &packettype) = 0;
	};
}

#endif
