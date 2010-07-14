#include "SerializeComponentBuilderFactory.h"
#include "SerializeComponentBuilder.h"
#include <MGE/res/system/ResourceNode.h>
#include <memory>
#include <vector>
#include <algorithm>

using namespace sto;
using namespace mge;
using namespace std;

SerializeComponentBuilderFactory::SerializeComponentBuilderFactory() { }
SerializeComponentBuilderFactory::~SerializeComponentBuilderFactory() { }

EntityComponentBuilder *SerializeComponentBuilderFactory::makeComponentBuilder(const string &name, const ResourceNode &node, const ResourceSystem &res) {
	if (node.getString("type", "") != "serialize")
		return NULL;
		
	auto_ptr<SerializeComponentBuilder> sercompbuild(new SerializeComponentBuilder(name));
		
	const ResourceNode &fullupdate = node.get("full");
	const ResourceNode &partialupdate = node.get("partial");
	
	vector<string> partialnames;
	
	for (ResourceNode::const_iterator i = partialupdate.begin(); i != partialupdate.end(); ++i) {
		if (i->second.toString() == "on") {
			const string &name = i->first;
			sercompbuild->addComponentName(name, false);
			partialnames.push_back(name);
		}
	}
	
	for (ResourceNode::const_iterator i = fullupdate.begin(); i != fullupdate.end(); ++i) {
		if (i->second.toString() == "on") {
			const string &name = i->first;
			
			if (find(partialnames.begin(), partialnames.end(), name) == partialnames.end())
				sercompbuild->addComponentName(name, true);
		}
	}
	
	return sercompbuild.release();
}
