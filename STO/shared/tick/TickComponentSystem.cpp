#include "TickComponentSystem.h"
#include "TickableComponent.h"

using namespace sto;
using namespace mge;
using namespace boost;

TickComponentSystem::TickComponentSystem(const FPSTimer &timer) : timer(timer) { }

void TickComponentSystem::updateComponent(const boost::shared_ptr<TickableComponent> &comp) {
	comp->tick(timer.getTDelta());
}
