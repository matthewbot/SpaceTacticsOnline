#include "SerializeComponentBuilder.h"
#include "SerializeComponent.h"
#include "SerializableComponent.h"
#include <boost/bind.hpp>
#include <memory>
#include <algorithm>

using namespace sto;
using namespace mge;
using namespace boost;
using namespace std;

SerializeComponentBuilder::SerializeComponentBuilder(const string &name) : name(name) { }
SerializeComponentBuilder::~SerializeComponentBuilder() { }

void SerializeComponentBuilder::addComponentName(const string &name, bool full) {
	if (full)
		fullcomponentnames.push_back(name);
	else
	  partialcomponentnames.push_back(name);
}

NamedComponent SerializeComponentBuilder::makeComponent(const ComponentMap &components, const ComponentSystemMap &compsystems) {
	auto_ptr<SerializeComponent> sercomp(new SerializeComponent());
	
	for_each(fullcomponentnames.begin(), fullcomponentnames.end(), bind(&SerializeComponentBuilder::doRegister, this, ref(*sercomp), cref(components), true, _1));
	for_each(partialcomponentnames.begin(), partialcomponentnames.end(), bind(&SerializeComponentBuilder::doRegister, this, ref(*sercomp), cref(components), false, _1)); 
	
	return make_pair(name, sercomp.release());
}


void SerializeComponentBuilder::doRegister(SerializeComponent &sercomp, const ComponentMap &components, bool fullonly, const string &name) {
	SerializableComponent *comp = dynamic_cast<SerializableComponent *>(&lookup_ref<EntityComponent>(name, components));
	
	if (!comp)
		throw Exception(string("Component ") + name + string(" isn't serializable!"));
	
	sercomp.registerComponent(*comp, fullonly);	
}
