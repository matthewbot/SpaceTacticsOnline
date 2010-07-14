#include "ThrusterStats.h"
#include <MGE/util/Exception.h>

using namespace sto;
using namespace mge;
using namespace std;

string sto::speedToStr(ThrusterStats::ThrustSpeed speed) {
	switch (speed) {
		case ThrusterStats::BRAKE:
			return "brake";
			
		case ThrusterStats::CRUISE:
			return "cruise";
			
		case ThrusterStats::ACCEL:
			return "accel";
			
		case ThrusterStats::BOOST:
			return "boost";
			
		default:
			throw Exception("Bad ThrustSpeed?");
	}
}
