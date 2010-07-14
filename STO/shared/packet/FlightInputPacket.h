#ifndef STO_SHARED_FLIGHTINPUTPACKET_H
#define STO_SHARED_FLIGHTINPUTPACKET_H

#include <STO/shared/input/FlightInput.h>
#include "Packet.h"

namespace sto {
	class FlightInputPacket : public Packet {
		public:
			FlightInputPacket();
			FlightInputPacket(const FlightInput &input);
			virtual ~FlightInputPacket();
		
			inline const FlightInput &getFlightInput() const { return input; }
		
			virtual void pack(mge::Blob &blob) const;
			virtual void unpack(mge::Blob &blob);
			
		private:
			FlightInput input;
	};
}


#endif
