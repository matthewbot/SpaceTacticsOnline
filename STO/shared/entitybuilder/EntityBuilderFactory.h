#ifndef STO_SHARED_ENTITYBUILDERFACTORY_H
#define STO_SHARED_ENTITYBUILDERFACTORY_H

#include <MGE/res/system/ResourceFactory.h>
#include <vector>

namespace mge {
	class ResourceSystem;
}

namespace sto {
	class EntityComponentBuilderFactory;

	class EntityBuilderFactory : public mge::ResourceFactory {
		typedef std::vector<EntityComponentBuilderFactory *> FactoryList;
	
		public:
			EntityBuilderFactory(const mge::ResourceSystem &res);
			virtual ~EntityBuilderFactory();
			
			void addFactory(EntityComponentBuilderFactory *factory);
			
			virtual mge::Resource *makeResource(const std::string &name, const mge::ResourceNode &props);
			
		private:
			mge::ResourceNode resolveInherit(const mge::ResourceNode &node);
			static mge::ResourceNode merge(const mge::ResourceNode &node, const mge::ResourceNode &other);
		
			const mge::ResourceSystem &res;
			FactoryList factories;
	};
}

#endif
