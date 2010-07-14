#include "ThrusterComponentBuilder.h"
#include "ThrusterComponent.h"
#include <STO/shared/motion/MotionComponent.h>
#include <STO/shared/tick/TickComponentSystem.h>

using namespace sto;
using namespace boost;
using namespace std;

ThrusterComponentBuilder::ThrusterComponentBuilder(const string &name, const string &motname, const string &tickname, const ThrusterStats &stats)
: name(name), motname(motname), tickname(tickname), stats(stats) { }
ThrusterComponentBuilder::~ThrusterComponentBuilder() { }

NamedComponent ThrusterComponentBuilder::makeComponent(const ComponentMap &components, const ComponentSystemMap &compsystems) {
	MotionComponent &mot = lookup_ref<MotionComponent>(motname, components);
	
	shared_ptr<ThrusterComponent> thrustcomp(new ThrusterComponent(mot, stats));
	
	TickComponentSystem &ticksys = lookup_ref<TickComponentSystem>(tickname, compsystems);
	ticksys.registerComponent(static_pointer_cast<TickableComponent>(thrustcomp));
	
	return make_pair(name, thrustcomp);
}
