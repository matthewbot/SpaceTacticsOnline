#include "FlightInputPacket.h"
#include <MGE/util/Blob.h>

using namespace sto;
using namespace mge;

FlightInputPacket::FlightInputPacket() { }
FlightInputPacket::FlightInputPacket(const FlightInput &input) : input(input) { }
FlightInputPacket::~FlightInputPacket() { }

void FlightInputPacket::pack(Blob &blob) const {
	blob.putShortFloat(3, input.mousedir);
	blob.put((short)input.mousedist);
	blob.put((char)input.speed);
}

void FlightInputPacket::unpack(Blob &blob) {
	input.mousedir = blob.getShortFloat(3);
	input.mousedist = blob.get<short>();
	input.speed = (ThrusterStats::ThrustSpeed)blob.get<char>();
}
