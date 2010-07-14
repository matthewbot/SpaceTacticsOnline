#ifndef STO_SHARED_ENTITYBUILDER_H
#define STO_SHARED_ENTITYBUILDER_H

#include "EntityComponentBuilder.h"
#include <STO/shared/entity/EntityContainer.h>
#include <MGE/res/Resource.h>
#include <vector>
#include <utility>

namespace sto {
	class EntityComponentBuilder;
	class Entity;

	class EntityBuilder : public mge::Resource {
		typedef std::vector<EntityComponentBuilder *> ComponentBuilderList;
	
		public:
			EntityBuilder(const std::string &name);
			~EntityBuilder();
			void addComponentBuilder(EntityComponentBuilder *builder);
			
			std::pair<Entity *, ComponentMap> makeEntity(const ComponentSystemMap &compsystems) const;
			
		private:
			ComponentBuilderList componentbuilders;
	};
}

#endif

