#ifndef STO_SHARED_SERIALIZECOMPONENTBUILDERFACTORY_H
#define STO_SHARED_SERIALIZECOMPONENTBUILDERFACTORY_H

#include <STO/shared/entitybuilder/EntityComponentBuilderFactory.h>

namespace sto {
	class SerializeComponentBuilder;

	class SerializeComponentBuilderFactory : public EntityComponentBuilderFactory {
		public:
			SerializeComponentBuilderFactory();
			~SerializeComponentBuilderFactory();
			
			virtual EntityComponentBuilder *makeComponentBuilder(const std::string &name, const mge::ResourceNode &node, const mge::ResourceSystem &res);
	};
}

#endif
