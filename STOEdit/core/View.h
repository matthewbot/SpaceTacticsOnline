#ifndef STOEDIT_VIEW_H
#define STOEDIT_VIEW_H

#include <boost/noncopyable.hpp>
#include <string>

namespace mge {
	class Viewport;
}

namespace stoedit {
	class InputEvent;

	class View : boost::noncopyable {
		public:
			inline virtual ~View() { }
			
			virtual void render(const mge::Viewport &out) = 0;
			virtual bool gotEvent(const InputEvent &event) = 0;
			
			virtual std::string getTitle() = 0;
	};
}

#endif
