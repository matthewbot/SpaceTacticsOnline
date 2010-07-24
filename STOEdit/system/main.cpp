#include <MGE/kernel/Kernel.h>
#include <MGE/kernel/KernelBuilder.h>
#include <MGE/gfx/system/GraphicsSystemFactory.h>
#include <MGE/res/system/ResourceSystemFactory.h>
#include <MGE/util/Logger.h>
#include <MGE/util/FrameRateLimiterFactory.h>
#include "STOEditSystemFactory.h"
#include <iostream>

using namespace mge;
using namespace stoedit;
using namespace std;

int main(int argc, char *argv[]) {
	Logger log;
	log.addStream(cout);
	log.setLogLevel(DEBUG);

	Kernel kernel;
	
	try {
		KernelBuilder builder;
		builder.addFactory(100, new GraphicsSystemFactory(900, 600, false, "STOEdit"));
		builder.addFactory(10, new ResourceSystemFactory(string("stoedit.res")));
		builder.addFactory(0, new STOEditSystemFactory());
		builder.addFactory(10000, new FrameRateLimiterFactory(100));
		
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
