#include "MotionComponentBuilderFactory.h"
#include "MotionComponentBuilder.h"
#include <MGE/res/system/ResourceNode.h>

using namespace sto;
using namespace mge;
using namespace std;

MotionComponentBuilderFactory::MotionComponentBuilderFactory() { }
MotionComponentBuilderFactory::~MotionComponentBuilderFactory() { }

EntityComponentBuilder *MotionComponentBuilderFactory::makeComponentBuilder(const string &name, const ResourceNode &node, const ResourceSystem &res) {
	if (node.getString("type", "") != "motion")
		return NULL;
		
	string posname = node.getString("position_c");
	string tickname = node.getString("tick_s");
	float hs = node.getFloat("hspeed", 0);
	float vs = node.getFloat("vspeed", 0);
	float rotspeed = node.getFloat("rotspeed", 0);
	
	return new MotionComponentBuilder(name, posname, tickname, hs, vs, rotspeed);
}
