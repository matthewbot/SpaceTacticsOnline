#include "SerializableComponent.h"
#include "DataSerializer.h"
#include "DataDeserializer.h"

using namespace sto;
using namespace mge;

SerializableComponent::SerializableComponent() { }
SerializableComponent::~SerializableComponent() { }

void SerializableComponent::serialize(Blob &blob) {
	DataSerializer serial(blob);
	visitData(serial);
}

void SerializableComponent::deserialize(Blob &blob) {
	DataDeserializer deserial(blob);
	visitData(deserial);
}
