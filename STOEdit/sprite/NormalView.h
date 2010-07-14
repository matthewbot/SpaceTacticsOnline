#ifndef STOEDIT_NORMALVIEW_H
#define STOEDIT_NORMALVIEW_H

#include "EditSpriteViewBase.h"

namespace mge {
	class Color;
}

namespace stoedit {
	class ViewProperties;
	class TransformViewData;
	class SpriteData;
	class SpriteControllerRes;

	class NormalView : public EditSpriteViewBase {
		public:
			NormalView(ViewProperties &props, int panewidth, int paneheight, SpriteData &data, const SpriteControllerRes &mres);
			virtual ~NormalView();
			
			// --- View ---
		
			virtual void render(const mge::Viewport &vp);
			virtual bool gotEvent(const InputEvent &event);
			virtual std::string getTitle();
			
		protected:
			virtual void doRenderContents(const mge::Viewport &vp);
			virtual void doRenderPixel(const mge::Viewport &vp, int texx, int texy, float vpx, float vpy, bool selected);
			virtual void doUpdatePixel(int curvalue, int texx, int texy);
			virtual void doCopyValue(int &curvalue, int texx, int texy);
			
		private:
			void drawArrow(const mge::Viewport &vp, float vpx, float vpy, float dir, const mge::Color &color);
			
			void renderHoverCounter(const mge::Viewport &vp);
			
			void flipNormals();
	};
}

#endif
