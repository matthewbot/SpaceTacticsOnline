#ifndef STOEDIT_DEPTHVIEW_H
#define STOEDIT_DEPTHVIEW_H

#include "EditSpriteViewBase.h"

namespace mge {
	class Color;
}

namespace stoedit {
	class ViewProperties;
	class TransformViewData;
	class SpriteData;
	class SpriteControllerRes;

	class DepthView : public EditSpriteViewBase {
		public:
			DepthView(ViewProperties &props, int panewidth, int paneheight, SpriteData &data, const SpriteControllerRes &mres);
			virtual ~DepthView();
			
			// --- View ---
		
			virtual void render(const mge::Viewport &out);
			virtual bool gotEvent(const InputEvent &event);
			virtual std::string getTitle();
			
		protected:
			virtual void doRenderContents(const mge::Viewport &vp);
			virtual void doRenderPixel(const mge::Viewport &vp, int texx, int texy, float vpx, float vpy, bool selected);
			virtual void doUpdatePixel(int curvalue, int texx, int texy);
			virtual void doCopyValue(int &curvalue, int texx, int texy);
			
		private:
			void drawDepthIndicator(const mge::Viewport &out, float x, float y, float amt, const mge::Color &color);
			void adjustAllDepth(int amt);
	};
}

#endif
