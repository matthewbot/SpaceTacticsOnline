#include "FlightInputComponent.h"
#include "FlightInput.h"
#include <STO/shared/thruster/ThrusterComponent.h>

using namespace sto;

FlightInputComponent::FlightInputComponent(ThrusterComponent &thrust) : thrust(thrust) { }
FlightInputComponent::~FlightInputComponent() { }

void FlightInputComponent::gotInput(const FlightInput &input) {
	thrust.setDestDir(input.mousedir);
	thrust.setSpeed(input.speed);
}
