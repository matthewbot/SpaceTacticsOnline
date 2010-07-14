#include "CurValueViewData.h"
#include <STOEdit/core/ViewProperties.h>

using namespace stoedit;
using namespace std;

CurValueViewData::CurValueViewData() : curvalue(0) { }
CurValueViewData::~CurValueViewData() { }

static const std::string datakey_prefix = "CurValueViewData_";

CurValueViewData &CurValueViewData::makeFromProperties(ViewProperties &props, const string &suffix) {
	string datakey(datakey_prefix + suffix);

	if (props.checkData(datakey)) {
		CurValueViewData &data = (CurValueViewData &)props.getData(datakey);
		return data;
	} else {
		CurValueViewData *view = new CurValueViewData();
		props.addData(datakey, view);
		return *view;
	}
}
