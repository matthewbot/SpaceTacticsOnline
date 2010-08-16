#include "FlightInputComponentBuilder.h"
#include "FlightInputComponent.h"
#include <STO/shared/thruster/ThrusterComponent.h>
#include <STO/shared/position/PositionComponent.h>

using namespace sto;
using namespace std;

FlightInputComponentBuilder::FlightInputComponentBuilder(const string &name, const string &thrustname, const string &centerposname)
: name(name), thrustname(thrustname), centerposname(centerposname) { }
FlightInputComponentBuilder::~FlightInputComponentBuilder() { }

NamedComponent FlightInputComponentBuilder::makeComponent(const ComponentMap &components, const ComponentSystemMap &compsystems) {
	ThrusterComponent &thrust = lookup_ref<ThrusterComponent>(thrustname, components);
	PositionComponent &centerpos = lookup_ref<PositionComponent>(centerposname, components);
	
	return make_pair(name, new FlightInputComponent(thrust, centerpos));
}
