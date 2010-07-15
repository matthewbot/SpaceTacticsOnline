#ifndef STO_SHARED_THRUSTERSTATS_H
#define STO_SHARED_THRUSTERSTATS_H

#include <string>

namespace sto {
	struct ThrusterStats {
		enum ThrustSpeed { // TODO seperate header possibly?
			BRAKE,
			CRUISE,
			ACCEL,
			BOOST,
			MAX_THRUST_VAL
		};
		
		struct SpeedStat {
			float rotaccel, rotmaxspeed, rotbrake;
			float accel, maxspeed, brake;
		} stat[MAX_THRUST_VAL];
	};
	
	std::string speedToStr(ThrusterStats::ThrustSpeed speed);
}

#endif
