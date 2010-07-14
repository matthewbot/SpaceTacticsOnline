#include "init.h"
#include <STO/shared/entitybuilder/EntityBuilderFactory.h>
#include <STO/shared/position/PositionComponentBuilderFactory.h>
#include <STO/shared/motion/MotionComponentBuilderFactory.h>
#include <STO/shared/thruster/ThrusterComponentBuilderFactory.h>
#include <STO/shared/input/FlightInputComponentBuilderFactory.h>
#include <STO/shared/serial/SerializeComponentBuilderFactory.h>
#include <MGE/res/system/ResourceSystem.h>
#include <MGE/gfx/system/GraphicsSystem.h>
#include <MGE/util/Exception.h>
#include <utility>

using namespace sto;
using namespace mge;
using namespace std;

EntityBuilderFactory *sto::initSharedEntityBuilder(ResourceSystem &res) {
	res.loadFile("shared/main.res");
	
	EntityBuilderFactory *factory = new EntityBuilderFactory(res);
	
	factory->addFactory(new PositionComponentBuilderFactory());
	factory->addFactory(new MotionComponentBuilderFactory());
	factory->addFactory(new ThrusterComponentBuilderFactory());
	factory->addFactory(new FlightInputComponentBuilderFactory());
	factory->addFactory(new SerializeComponentBuilderFactory());
	
	res.registerResourceFactory(factory);
	
	return factory;
}
	
	
