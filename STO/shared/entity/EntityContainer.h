#ifndef MGE_ENTITY_ENTITYCONTAINER_H
#define MGE_ENTITY_ENTITYCONTAINER_H

#include <list>
#include <map>
#include <string>
#include <boost/shared_ptr.hpp>

namespace sto {
	class Entity;
	class EntityComponentSystem;
	
	typedef std::map<std::string, boost::shared_ptr<EntityComponentSystem> > ComponentSystemMap;

	class EntityContainer {
		typedef std::list<Entity *> EntityList;			
		
		public:
			EntityContainer();
			~EntityContainer();
			
			void addSystem(const std::string &name, const boost::shared_ptr<EntityComponentSystem> &system);
			inline const ComponentSystemMap &getSystemMap() const { return componentsystems; }
			void update();
			
			typedef EntityList::const_iterator const_iterator;
			inline const_iterator begin() const { return entities.begin(); }
			inline const_iterator end() const { return entities.end(); }
			
			void addEntity(Entity *entity);
			void removeEntity(Entity *entity);
			
		private:
			EntityList entities;
			ComponentSystemMap componentsystems;
	};
}

#endif
