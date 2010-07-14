#include "InitialSTOServerStateFactory.h"
#include <STO/server/game/ServerGameState.h>
#include <STO/shared/init.h>
#include <MGE/kernel/Kernel.h>
#include <MGE/kernel/KernelBuilder.h>
#include <MGE/util/Logger.h>
#include <MGE/fs/FileSystemFactory.h>
#include <MGE/res/system/ResourceSystemFactory.h>
#include <MGE/net/NetworkSystemFactory.h>
#include <MGE/state/GameStateSystemFactory.h>
#include <MGE/util/FrameRateLimiterFactory.h>
#include <iostream>

using namespace sto;
using namespace mge;
using namespace std;

static void initResourceSystem(ResourceSystem &res, const KernelSystemMap &systems);

int main(int argc, char **argv) {
	Logger log;
	log.addStream(cout);
	log.setLogLevel(DEBUG);

	Kernel kernel;
	
	try {
		KernelBuilder builder;
		builder.addFactory(10, new FileSystemFactory("JeffAndMatt", "STO", argv[0])); // get filesystem up because other things need pointers to it
		builder.addFactory(9, new ResourceSystemFactory(initResourceSystem)); // the resource system, with our custom init function
		builder.addFactory(-100, new NetworkSystemFactory());
		builder.addFactory(0, new GameStateSystemFactory(new InitialSTOServerStateFactory<ServerGameState>())); // must be last
		builder.addFactory(1000, new FrameRateLimiterFactory(100));
		
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
	initSharedEntityBuilder(res);
}
