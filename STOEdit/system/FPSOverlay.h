#ifndef STOEDIT_FPSOVERLAY_H
#define STOEDIT_FPSOVERLAY_H

#include <STOEdit/input/InputEventListener.h>
#include <boost/shared_ptr.hpp>

namespace mge {
	class Viewport;
	class Font;
	class GraphicsSystem;
}

namespace stoedit {
	class FPSOverlay : public InputEventListener {
		public:
			FPSOverlay(const boost::shared_ptr<mge::Font> &font);
			virtual ~FPSOverlay();
			
			virtual bool gotEvent(const InputEvent &event);
			
			void render(mge::Viewport &view, const mge::GraphicsSystem &gfx);
			
		private:
			bool show;
			boost::shared_ptr<mge::Font> font;
	};
}

#endif
