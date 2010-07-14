#include "PositionComponentBuilderFactory.h"
#include "PositionComponentBuilder.h"
#include <MGE/res/system/ResourceNode.h>

using namespace sto;
using namespace mge;
using namespace std;

PositionComponentBuilderFactory::PositionComponentBuilderFactory() { }
PositionComponentBuilderFactory::~PositionComponentBuilderFactory() { }

EntityComponentBuilder *PositionComponentBuilderFactory::makeComponentBuilder(const string &name, const ResourceNode &node, const ResourceSystem &res) {
	if (node.getString("type", "") != "position")
		return NULL;
		
	float x = node.getFloat("xpos", 0);
	float y = node.getFloat("ypos", 0);
	float facedir = node.getFloat("facedir", 0);
	string chainname = node.getString("chain_c", "");
	
	return new PositionComponentBuilder(name, chainname, x, y, facedir);
}
