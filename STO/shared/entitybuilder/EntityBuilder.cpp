#include "EntityBuilder.h"
#include "EntityComponentBuilder.h"
#include <STO/shared/entity/Entity.h>
#include <STO/shared/entity/EntityComponent.h>
#include <MGE/util/Exception.h>
#include <memory>

using namespace sto;
using namespace mge;
using namespace boost;
using namespace std;

EntityBuilder::EntityBuilder(const string &name) : Resource(name) { }
EntityBuilder::~EntityBuilder() {
	for (ComponentBuilderList::iterator i = componentbuilders.begin(); i != componentbuilders.end(); ++i)
		delete *i;
}

void EntityBuilder::addComponentBuilder(EntityComponentBuilder *builder) {
	componentbuilders.push_back(builder);
}

pair<Entity *, ComponentMap> EntityBuilder::makeEntity(const ComponentSystemMap &compsystems) const {
	try {
		auto_ptr<Entity> entity(new Entity());
		ComponentMap components;
	
		for (ComponentBuilderList::const_iterator i = componentbuilders.begin(); i != componentbuilders.end(); ++i) {
			NamedComponent component((*i)->makeComponent(components, compsystems));
		
			components.insert(component);
			entity->addComponent(shared_ptr<EntityComponent>(component.second));
		}
	
		return make_pair(entity.release(), components);
	} catch (Exception &ex) {
		throw Exception(string("Got exception while making entity ") + name + string(": ") + string(ex.what()));
	}
}

