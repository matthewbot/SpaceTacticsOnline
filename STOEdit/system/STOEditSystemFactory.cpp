#include "STOEditSystemFactory.h"
#include "STOEditSystem.h"
#include <MGE/gfx/system/GraphicsSystem.h>
#include <MGE/res/system/ResourceSystem.h>
#include <cassert>

using namespace stoedit;
using namespace mge;

STOEditSystemFactory::STOEditSystemFactory() { }

KernelSystem *STOEditSystemFactory::makeKernelSystem(Logger &logger, const KernelSystemMap &map) {
	KernelSystemMap::const_iterator i = map.find("GraphicsSystem");
	assert(i != map.end());
		
	GraphicsSystem &gfx = (GraphicsSystem &)*i->second;
	
	i = map.find("ResourceSystem");
	assert(i != map.end());
	
	ResourceSystem &res = (ResourceSystem &)*i->second;

	return new STOEditSystem(gfx, res);
}

