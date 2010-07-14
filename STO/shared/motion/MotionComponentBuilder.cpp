#include "MotionComponentBuilder.h"
#include "MotionComponent.h"
#include <STO/shared/position/PositionComponent.h>
#include <STO/shared/tick/TickComponentSystem.h>

using namespace sto;
using namespace boost;
using namespace std;

MotionComponentBuilder::MotionComponentBuilder(const string &name, const string &posname, const string &tickname, float hs, float vs, float rots)
: name(name), posname(posname), tickname(tickname), hs(hs), vs(vs), rots(rots) { }
MotionComponentBuilder::~MotionComponentBuilder() { }

NamedComponent MotionComponentBuilder::makeComponent(const ComponentMap &components, const ComponentSystemMap &compsystems) {
	PositionComponent &pos = lookup_ref<PositionComponent>(posname, components);
	
	shared_ptr<MotionComponent> motcomp(new MotionComponent(pos, hs, vs, rots));
	
	TickComponentSystem &ticksys = lookup_ref<TickComponentSystem>(tickname, compsystems);
	ticksys.registerComponent(static_pointer_cast<TickableComponent>(motcomp));

	return make_pair(name, motcomp);
}
