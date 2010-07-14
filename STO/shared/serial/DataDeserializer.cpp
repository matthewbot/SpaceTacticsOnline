#include "DataDeserializer.h"
#include <MGE/util/Blob.h>
#include <cmath>

using namespace sto;
using namespace mge;
using namespace std;

DataDeserializer::DataDeserializer(mge::Blob &blob) : blob(blob) { }
DataDeserializer::~DataDeserializer() { }

void DataDeserializer::visit(bool &val) {
	val = (blob.get<char>() != 0);
}

void DataDeserializer::visit(char &val) {
	val = blob.get<char>();
}

void DataDeserializer::visit(short &val) {
	val = blob.get<short>();
}

void DataDeserializer::visit(int &val) {
	val = blob.get<int>();
}

void DataDeserializer::visit(float &val, int magnitude) {
	if (magnitude > 0)
		val = (float)blob.get<short>() * pow((float)10, magnitude);
	else
		val = blob.get<float>();
}
