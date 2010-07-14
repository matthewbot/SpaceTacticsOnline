#ifndef STO_SHARED_PACKETMANAGER_H
#define STO_SHARED_PACKETMANAGER_H

#include <vector>

namespace mge {
	class Blob;
}

namespace sto {
	class Packet;
	class PacketFactory;

	class PacketManager {
		public:
			PacketManager();
			~PacketManager();
			
			void addFactory(PacketFactory *factory);
			
			void encode(const Packet &pack, mge::Blob &blob) const;
			Packet *decode(mge::Blob &blob) const;
			
		private:
			typedef std::vector<PacketFactory *> FactoryList;
			FactoryList factories;
	};
}

#endif
