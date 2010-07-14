#include "SpriteComponentBuilderFactory.h"
#include "SpriteComponentBuilder.h"
#include <MGE/res/system/ResourceNode.h>
#include <MGE/util/Exception.h>

using namespace sto;
using namespace mge;
using namespace std;

SpriteComponentBuilderFactory::SpriteComponentBuilderFactory() { }
SpriteComponentBuilderFactory::~SpriteComponentBuilderFactory() { }

EntityComponentBuilder *SpriteComponentBuilderFactory::makeComponentBuilder(const string &name, const ResourceNode &node, const ResourceSystem &res) {
	if (node.getString("type", "") != "sprite")
		return NULL;
		
	string spritename = node.getString("sprite_r");
	string positionname = node.getString("position_c");
	string rendersystemname = node.getString("render_s");
	
	SpriteComponentBuilder::SpriteType type;
	string typestr = node.getString("spritetype", "standard");
	if (typestr == "standard")
		type = SpriteComponentBuilder::STANDARD;
	else if (typestr == "light")
		type = SpriteComponentBuilder::LIGHT;
	else
		throw Exception(string("Bad spritetype ") + typestr);
	
	return new SpriteComponentBuilder(name, res, spritename, type, positionname, rendersystemname);
}
