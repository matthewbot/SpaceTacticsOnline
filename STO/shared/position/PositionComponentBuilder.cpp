#include "PositionComponentBuilder.h"
#include "PositionComponent.h"

using namespace sto;
using namespace std;

PositionComponentBuilder::PositionComponentBuilder(const string &name, const string &chainname, float x, float y, float dir) 
: name(name), chainname(chainname), x(x), y(y), dir(dir) { }
PositionComponentBuilder::~PositionComponentBuilder() { }

NamedComponent PositionComponentBuilder::makeComponent(const ComponentMap &components, const ComponentSystemMap &compsystems) {
	PositionComponent *chainpos;
	
	if (chainname.length() > 0) 
		chainpos = &lookup_ref<PositionComponent>(chainname, components);
	else 
		chainpos = NULL;

	return make_pair(name, new PositionComponent(x, y, dir, chainpos)); // TODO
}
