#include "FlightInputComponentBuilderFactory.h"
#include "FlightInputComponentBuilder.h"
#include <MGE/res/system/ResourceNode.h>

using namespace sto;
using namespace mge;
using namespace std;

FlightInputComponentBuilderFactory::FlightInputComponentBuilderFactory() { }
FlightInputComponentBuilderFactory::~FlightInputComponentBuilderFactory() { }

EntityComponentBuilder *FlightInputComponentBuilderFactory::makeComponentBuilder(const string &name, const ResourceNode &node, const ResourceSystem &res) {
	if (node.getString("type", "") != "input")
		return NULL;
		
	string thrustname = node.getString("thruster_c");
	
	return new FlightInputComponentBuilder(name, thrustname);
}
