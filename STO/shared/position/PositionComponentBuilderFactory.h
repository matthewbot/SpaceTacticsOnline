#ifndef STO_SHARED_POSITIONCOMPONENTBUILDERFACTORY_H
#define SOT_SHARED_POSITIONCOMPONENTBUILDERFACTORY_H

#include <STO/shared/entitybuilder/EntityComponentBuilderFactory.h>

namespace sto {
	class PositionComponentBuilderFactory : public EntityComponentBuilderFactory {
		public:
			PositionComponentBuilderFactory();
			~PositionComponentBuilderFactory();
			
			virtual EntityComponentBuilder *makeComponentBuilder(const std::string &name, const mge::ResourceNode &node, const mge::ResourceSystem &res);
	};
}

#endif
