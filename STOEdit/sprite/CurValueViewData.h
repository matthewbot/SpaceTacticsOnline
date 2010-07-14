#ifndef STOEDIT_CURVALUEVIEWDATA_H
#define STOEDIT_CURVALUEVIEWDATA_H

#include <STOEdit/core/ViewData.h>
#include <string>

namespace stoedit {
	class ViewProperties;

	class CurValueViewData : public ViewData {
		public:
			CurValueViewData();
			virtual ~CurValueViewData();
			
			inline void set(int curvalue) { this->curvalue = curvalue; }
			inline int get() const { return curvalue; }
			inline int &value() { return curvalue; }
			
			static CurValueViewData &makeFromProperties(ViewProperties &props, const std::string &suffix);
		
		private:
			int curvalue;
	};
}

#endif
