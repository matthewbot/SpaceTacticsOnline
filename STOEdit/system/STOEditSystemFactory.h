#ifndef STOEDIT_STOEDITSYSTEMFACTORY_H
#define STOEDIT_STOEDITSYSTEMFACTORY_H

#include <MGE/kernel/KernelSystemFactory.h>

namespace stoedit {
	class STOEditSystemFactory : public mge::KernelSystemFactory {
		public:
			STOEditSystemFactory();
			
			virtual mge::KernelSystem *makeKernelSystem(mge::Logger &logger, const mge::KernelSystemMap &map);
	};
}

#endif
