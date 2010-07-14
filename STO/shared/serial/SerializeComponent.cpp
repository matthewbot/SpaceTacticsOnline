#include "SerializeComponent.h"
#include "SerializableComponent.h"
#include <boost/bind.hpp>
#include <boost/ref.hpp>
#include <functional>
#include <algorithm>

using namespace sto;
using namespace mge;
using namespace boost;
using namespace std;

SerializeComponent::SerializeComponent() { }
SerializeComponent::~SerializeComponent() { }

void SerializeComponent::registerComponent(SerializableComponent &component, bool fullonly) {
	fullcomps.push_back(&component);
	if (!fullonly)
		partialcomps.push_back(&component);
}

void SerializeComponent::serialize(mge::Blob &blob, bool full) {
	SerializableList &list = full ? fullcomps : partialcomps;
	for_each(list.begin(), list.end(), bind(&SerializableComponent::serialize, _1, ref(blob)));
}

void SerializeComponent::deserialize(mge::Blob &blob, bool full) {
	SerializableList &list = full ? fullcomps : partialcomps;
	for_each(list.begin(), list.end(), bind(&SerializableComponent::deserialize, _1, ref(blob)));
}
