#include "ViewProperties.h"
#include "ViewData.h"
#include <MGE/util/Exception.h>

using namespace stoedit;
using namespace mge;
using namespace std;

ViewProperties::ViewProperties() { }
ViewProperties::~ViewProperties() {
	for (PropertyMap::iterator i = props.begin(); i != props.end(); ++i) {
		delete i->second;
	}
}

bool ViewProperties::checkData(const std::string &data) const {
	PropertyMap::const_iterator i = props.find(data);
	return i != props.end();
}

void ViewProperties::addData(const std::string &name, ViewData *data) {
	props[name] = data;
}

ViewData &ViewProperties::getData(const std::string &name) const {
	PropertyMap::const_iterator i = props.find(name);
	if (i == props.end())
		throw Exception(string("ViewProperties contains no data named ") + name);
		
	return *i->second;
}
