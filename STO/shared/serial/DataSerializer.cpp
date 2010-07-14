#include "DataSerializer.h"
#include <MGE/util/Blob.h>
#include <cmath>

using namespace sto;
using namespace mge;

DataSerializer::DataSerializer(Blob &blob) : blob(blob) { }
DataSerializer::~DataSerializer() { }

void DataSerializer::visit(bool &val) {
	blob.put<char>(val ? 0x42 : 0);
}

void DataSerializer::visit(char &val) {
	blob.put(val);
}

void DataSerializer::visit(short &val) {
	blob.put(val);
}

void DataSerializer::visit(int &val) {
	blob.put(val);
}

void DataSerializer::visit(float &val, int magnitude) {
	if (magnitude > 0) {
		blob.put( (short)(val * pow((float)10, magnitude)) );
	} else {
		blob.put(val);
	}
}
