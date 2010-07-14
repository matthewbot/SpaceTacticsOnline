#ifndef STO_SHARED_MOTIONCOMPONENTBUILDERFACTORY_H
#define STO_SHARED_MOTIONCOMPONENTBUILDERFACTORY_H

#include <STO/shared/entitybuilder/EntityComponentBuilderFactory.h>

namespace sto {
	class MotionComponentBuilderFactory : public EntityComponentBuilderFactory {
		public:
			MotionComponentBuilderFactory();
			~MotionComponentBuilderFactory();
			
			virtual EntityComponentBuilder *makeComponentBuilder(const std::string &name, const mge::ResourceNode &node, const mge::ResourceSystem &res);
	};
}

#endif
