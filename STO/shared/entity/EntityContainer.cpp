#include "EntityContainer.h"
#include "Entity.h"
#include "EntityComponentSystem.h"
#include <algorithm>
#include <functional>

using namespace sto;
using namespace boost;
using namespace std;

EntityContainer::EntityContainer() { }
EntityContainer::~EntityContainer() { }

void EntityContainer::addSystem(const std::string &name, const boost::shared_ptr<EntityComponentSystem> &system) {
	componentsystems[name] = system;
}

void EntityContainer::update() {
	for (ComponentSystemMap::const_iterator i = componentsystems.begin(); i != componentsystems.end(); ++i) {
		i->second->update();
	}
	
	remove_if(entities.begin(), entities.end(), mem_fun(&Entity::getDestroyFlag));
}

void EntityContainer::addEntity(Entity *entity) {
	entities.push_back(entity);
}

void EntityContainer::removeEntity(Entity *entity) {
	entities.remove(entity);
}
