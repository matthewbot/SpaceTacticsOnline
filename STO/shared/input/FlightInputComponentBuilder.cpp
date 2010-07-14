#include "FlightInputComponentBuilder.h"
#include "FlightInputComponent.h"
#include <STO/shared/thruster/ThrusterComponent.h>

using namespace sto;
using namespace std;

FlightInputComponentBuilder::FlightInputComponentBuilder(const std::string &name, const std::string &thrustname)
: name(name), thrustname(thrustname) { }
FlightInputComponentBuilder::~FlightInputComponentBuilder() { }

NamedComponent FlightInputComponentBuilder::makeComponent(const ComponentMap &components, const ComponentSystemMap &compsystems) {
	ThrusterComponent &thrust = lookup_ref<ThrusterComponent>(thrustname, components);
	
	return make_pair(name, new FlightInputComponent(thrust));
}
