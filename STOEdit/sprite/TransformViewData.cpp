#include "TransformViewData.h"
#include <STOEdit/core/ViewProperties.h>

using namespace stoedit;
using namespace mge;
using namespace std;

TransformViewData::TransformViewData() { reset(); }
TransformViewData::~TransformViewData() { }

void TransformViewData::reset() {
	translatex = translatey = 0;
	zoom = 1;
}

Transform TransformViewData::getTransform() {
	Transform trans;
	
	trans.scale(zoom, zoom); // zoom...
	trans.translate(translatex, translatey);
	
	return trans;
}

static const std::string datakey = "TransformViewData";

TransformViewData &TransformViewData::makeFromProperties(ViewProperties &props) {
	if (props.checkData(datakey)) {
		TransformViewData &data = (TransformViewData &)props.getData(datakey);
		return data;
	} else {
		TransformViewData *view = new TransformViewData();
		props.addData(datakey, view);
		return *view;
	}
}
