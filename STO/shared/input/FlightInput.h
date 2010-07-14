#ifndef STO_SHARED_FLIGHTINPUT_H
#define STO_SHARED_FLIGHTINPUT_H

#include <STO/shared/thruster/ThrusterStats.h>

namespace sto {
	struct FlightInput {
		float mousedir, mousedist; // mouse in polar (mouse 9 times out of 10 for flying, so more useful this way)
		
		ThrusterStats::ThrustSpeed speed;
		// TODO flight control, weapon control, etc
	};
}

#endif
