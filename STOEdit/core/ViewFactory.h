#ifndef STOEDIT_VIEWFACTORY_H
#define STOEDIT_VIEWFACTORY_H

#include <memory>

namespace mge {
	class ViewSection;
}

namespace stoedit {
	class View;
	class ViewProperties;
	
	class ViewFactory {
		public:
			inline virtual ~ViewFactory() { };
			
			virtual std::auto_ptr<View> makeView(ViewProperties &props, int width, int height) = 0;
	};
}

#endif
