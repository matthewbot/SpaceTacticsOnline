#include "ThrusterComponentBuilderFactory.h"
#include "ThrusterComponentBuilder.h"
#include "ThrusterStats.h"
#include <MGE/res/system/ResourceNode.h>

using namespace sto;
using namespace mge;
using namespace std;

ThrusterComponentBuilderFactory::ThrusterComponentBuilderFactory() { }
ThrusterComponentBuilderFactory::~ThrusterComponentBuilderFactory() { }

EntityComponentBuilder *ThrusterComponentBuilderFactory::makeComponentBuilder(const string &name, const ResourceNode &node, const ResourceSystem &res) {
	if (node.getString("type", "") != "thruster")
		return NULL;
		
	
	ThrusterStats stats;
	const ResourceNode &statdef = node.get("default");
	
	for (int i=0; i < ThrusterStats::MAX_THRUST_VAL; i++) {
		ThrusterStats::ThrustSpeed speed = (ThrusterStats::ThrustSpeed)i;
		ThrusterStats::SpeedStat &speedstat = stats.stat[speed];
		
		std::string name = speedToStr(speed);
		if (node.has(name)) {
			const ResourceNode &statnode = node.get(name);
			
			speedstat.rotaccel = doubleLookup("rotaccel", statnode, statdef);
			speedstat.rotmaxspeed = doubleLookup("rotmaxspeed", statnode, statdef);
			speedstat.rotbrake = doubleLookup("rotbrake", statnode, statdef);
			speedstat.accel = doubleLookup("accel", statnode, statdef);
			speedstat.maxspeed = doubleLookup("maxspeed", statnode, statdef);
			speedstat.brake = doubleLookup("brake", statnode, statdef);
		} else {
			speedstat.rotaccel = statdef.getFloat("rotaccel");
			speedstat.rotmaxspeed = statdef.getFloat("rotmaxspeed");
			speedstat.rotbrake = statdef.getFloat("rotbrake");
			speedstat.accel = statdef.getFloat("accel");
			speedstat.maxspeed = statdef.getFloat("maxspeed");
			speedstat.brake = statdef.getFloat("brake");
		}
	}
	
	string motname = node.getString("motion_c");
	string tickname = node.getString("tick_s");
	
	return new ThrusterComponentBuilder(name, motname, tickname, stats);
}

float ThrusterComponentBuilderFactory::doubleLookup(const std::string &key, const ResourceNode &primary, const ResourceNode &secondary) {
	if (primary.has(key))
		return primary.getFloat(key);
	else
		return secondary.getFloat(key);
}
