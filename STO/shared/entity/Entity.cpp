#include "Entity.h"
#include "EntityComponent.h"
#include "DestroyComponent.h"

using namespace sto;
using namespace boost;
using namespace std;

Entity::Entity() { }
Entity::~Entity() { }

void Entity::addComponent(const shared_ptr<EntityComponent> &comp) {
	components.push_back(comp);
}

