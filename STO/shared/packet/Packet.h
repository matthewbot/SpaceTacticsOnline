#ifndef STO_SHARED_PACKET
#define STO_SHARED_PACKET

namespace mge {
	class Blob;
}

namespace sto {
	class Packet {
		public:
			inline virtual ~Packet() { }
		
			virtual void pack(mge::Blob &blob) const = 0;
			virtual void unpack(mge::Blob &blob) = 0;
	};
}

#endif
