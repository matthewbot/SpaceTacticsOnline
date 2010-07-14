#ifndef STO_SHARED_ENTITYCOMPONENTBUILDERFACTORY_H
#define STO_SHARED_ENTITYCOMPONENTBUILDERFACTORY_H

#include <string>

namespace mge {
	class ResourceNode;
	class ResourceSystem;
}

namespace sto {
	class EntityComponentBuilder;

	class EntityComponentBuilderFactory {
		public:
			inline virtual ~EntityComponentBuilderFactory() { }
			
			virtual EntityComponentBuilder *makeComponentBuilder(const std::string &name, const mge::ResourceNode &node, const mge::ResourceSystem &res) = 0;
	};
}

#endif
