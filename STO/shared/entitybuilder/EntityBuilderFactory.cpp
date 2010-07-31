#include "EntityBuilderFactory.h"
#include "EntityComponentBuilderFactory.h"
#include "EntityBuilder.h"
#include <MGE/res/system/ResourceNode.h>
#include <MGE/res/system/ResourceSystem.h>
#include <MGE/util/Exception.h>
#include <memory>

using namespace sto;
using namespace mge;
using namespace std;

EntityBuilderFactory::EntityBuilderFactory(const ResourceSystem &res) : res(res) { }
EntityBuilderFactory::~EntityBuilderFactory() { }

void EntityBuilderFactory::addFactory(EntityComponentBuilderFactory *factory) {
	factories.push_back(factory);
}

Resource *EntityBuilderFactory::makeResource(const string &name, const ResourceNode &basenode) {
	if (basenode.getString("type", "") != "entity")
		return NULL;

	auto_ptr<EntityBuilder> builder(new EntityBuilder(name));
	ResourceNode node = resolveInherit(basenode);

	for (ResourceNode::const_iterator i = node.begin(); i != node.end(); ++i) {
		if (i->first == "type" || i->first == "inherit")
			continue;
		
		EntityComponentBuilder *componentbuilder = NULL;
		for (FactoryList::const_iterator j = factories.begin(); j != factories.end(); ++j) {
			try {
				componentbuilder = (*j)->makeComponentBuilder(i->first, i->second, res);
				if (componentbuilder)
					break;
			} catch (Exception &ex) {
				throw Exception(string("Got exception while creating EntityBuilder for ") + name + string(" component ") + i->first + string(": ") + string(ex.what()));
			}
		}
	
		if (!componentbuilder)
			throw Exception(string("No component builder exists for component ") + i->first + string(" of entity ") + name);
		
		builder->addComponentBuilder(componentbuilder);
	}

	return builder.release();
}

ResourceNode EntityBuilderFactory::resolveInherit(const mge::ResourceNode &node) {
	const ResourceNode &root = res.getRoot();

	string str = node.getString("inherit", "");
	if (str.length() > 0) {
		if (!root.has(str))
			throw Exception(string("Resource properties named ") + str + string(" doesn't exist in inherit command"));
			
		return merge(node, resolveInherit(root.get(str)));
	} else
		return node;
}

ResourceNode EntityBuilderFactory::merge(const mge::ResourceNode &node, const mge::ResourceNode &other) {
	if (node.getType() != ResourceNode::LIST)
		return node;
	
	ResourceNode merged(other); 
	
	for (ResourceNode::const_iterator i = node.begin(); i != node.end(); i++) {
		if (i->second.getType() == ResourceNode::LIST) {
			if (merged.has(i->first))
				merged.set(i->first, merge(i->second, merged.get(i->first)));
			else
				merged.set(i->first, i->second);
		} else
			merged.set(i->first, i->second);
	}
	
	return merged;
}
