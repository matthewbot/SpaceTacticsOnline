#include "InitialSTOClientStateFactory.h"
#include <STO/client/game/ClientGameState.h>
#include <STO/client/sprite/SpriteComponentBuilderFactory.h>
#include <STO/client/sprite/LightSpriteFactory.h>
#include <STO/shared/entitybuilder/EntityBuilderFactory.h>
#include <STO/shared/init.h>
#include <MGE/kernel/Kernel.h>
#include <MGE/kernel/KernelBuilder.h>
#include <MGE/gfx/system/GraphicsSystemFactory.h>
#include <MGE/gfx/system/GraphicsSystem.h>
#include <MGE/res/system/ResourceSystemFactory.h>
#include <MGE/res/system/ResourceSystem.h>
#include <MGE/snd/system/AudioSystemFactory.h>
#include <MGE/net/NetworkSystemFactory.h>
#include <MGE/fs/FileSystemFactory.h>
#include <MGE/state/GameStateSystemFactory.h>
#include <MGE/util/Logger.h>
#include <MGE/util/Exception.h>
#include <MGE/util/FrameRateLimiterFactory.h>
#include <iostream>

using namespace sto;
using namespace mge;
using namespace std;

static void initResourceSystem(ResourceSystem &res, const KernelSystemMap &systems);

int main(int argc, char *argv[]) {
	Logger log;
	log.addStream(cout);
	log.setLogLevel(DEBUG);

	Kernel kernel;
	
	try {
		KernelBuilder builder;
		builder.addFactory(10, new FileSystemFactory("JeffAndMatt", "STO", argv[0])); // get filesystem up because other things need pointers to it
		builder.addFactory(100, new GraphicsSystemFactory(900, 600, false, "Space Tactics Online")); // then get graphics system ASAP so something can go on the screen (TODO: Loading screen or something)
		builder.addFactory(8, new AudioSystemFactory()); // audio system needs to come before..
		builder.addFactory(9, new ResourceSystemFactory(initResourceSystem)); // the resource system, with our custom init function
		builder.addFactory(-100, new NetworkSystemFactory());
		builder.addFactory(1000, new FrameRateLimiterFactory(200));
		builder.addFactory(0, new GameStateSystemFactory(new InitialSTOClientStateFactory<ClientGameState>())); // must be last
		
		kernel = builder.buildKernel(log);
	} catch (std::exception &ex) {
		log.log("main", ERROR) << "Got exception while initializing:" << endl << ex.what() << endl;
		return 1;
	}
  
	try	{
		kernel.run();
	} catch (std::exception &ex) {
		log.log("main", ERROR) << "Got exception while running: " << endl << ex.what() << endl;
		return 1;
	}
	
	return 0;
}

static void initResourceSystem(ResourceSystem &res, const KernelSystemMap &systems) {
	EntityBuilderFactory *factory = initSharedEntityBuilder(res);
	
	res.loadFile("client/main.res");
	
	factory->addFactory(new SpriteComponentBuilderFactory());
	
	KernelSystemMap::const_iterator i = systems.find("GraphicsSystem");
	if (i == systems.end())
		throw Exception("No GraphicsSystem?");
	GraphicsSystem &gfx = (GraphicsSystem &)*i->second;
	res.registerResourceFactory(new LightSpriteFactory(res, gfx.getTextureManager()));
}

