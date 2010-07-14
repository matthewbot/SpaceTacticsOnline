#ifndef STOEDIT_PANE_H
#define STOEDIT_PANE_H

#include "ViewProperties.h"
#include <MGE/gfx/ViewSection.h>
#include <utility>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

namespace mge {
	class Viewport;
}

namespace stoedit {
	class View;
	class ViewFactory;
	class PaneFrameRenderer;
	class InputEvent;

	class Pane : boost::noncopyable {
		public:
			Pane(PaneFrameRenderer &framerenderer, int width, int height);
			~Pane();
			
			void clearView();
			void setView(ViewFactory &viewfact);
			
			void render(mge::Viewport &view, bool selected);
			bool gotEvent(const InputEvent &event);
			
		private:
			PaneFrameRenderer &framerenderer;
			int width, height;	
			mge::ViewSection innersection;
				
			std::auto_ptr<View> view;
			ViewProperties props;
	};
}

#endif
