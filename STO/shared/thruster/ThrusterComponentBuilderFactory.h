#ifndef STO_SHARED_THRUSTERCOMPONENTBUILDERFACTORY_H
#define STO_SHARED_THRUSTERCOMPONENTBUILDERFACTORY_H

#include <STO/shared/entitybuilder/EntityComponentBuilderFactory.h>

namespace sto {
	class ThrusterComponentBuilderFactory : public EntityComponentBuilderFactory {
		public:
			ThrusterComponentBuilderFactory();
			~ThrusterComponentBuilderFactory();
			
			virtual EntityComponentBuilder *makeComponentBuilder(const std::string &name, const mge::ResourceNode &node, const mge::ResourceSystem &res);
	
		private:
			static float doubleLookup(const std::string &key, const mge::ResourceNode &primary, const mge::ResourceNode &secondary);
	};
}

#endif
