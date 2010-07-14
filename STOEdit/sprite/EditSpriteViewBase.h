#ifndef STOEDIT_EDITSPRITEVIEWBASE_H
#define STOEDIT_EDITSPRITEVIEWBASE_H

#include "SpriteViewBase.h"
#include "CurValueViewData.h"

namespace mge {
	class Viewport;
	class Color;
}

namespace stoedit {
	class EditSpriteViewBase : public SpriteViewBase {
		public:
			EditSpriteViewBase(ViewProperties &props, int panewidth, int paneheight, SpriteData &data, const SpriteControllerRes &mres, const std::string &suffix);
			virtual ~EditSpriteViewBase();
		
		protected:
			void renderPixels(const mge::Viewport &vp, int texw, int texh);
			void renderCurrentValue(const mge::Viewport &vp);
			bool handleEvent(const InputEvent &event, int texw, int texh);
		
			virtual void doRenderPixel(const mge::Viewport &vp, int texx, int texy, float vpx, float vpy, bool selected) = 0; // texx/texy is pixel location, vpx/vpy is center of pixel on viwport
			virtual void doUpdatePixel(int curvalue, int texx, int texy) = 0;
			virtual void doUpdateValue(int &curvalue, bool up, bool fast);
			virtual void doCopyValue(int &curvalue, int texx, int texy);
			
			void renderDarkenedSprite(const mge::Viewport &vp, int minpixelzoom);
			
			inline int getCurTexX() const { return curtexx; }
			inline int getCurTexY(int texh) const { return texh - 1 - curtexy; }
			inline int getCurValue() const { return curvaluedata.get(); }
			inline void setCurValue(int val) { curvaluedata.set(val); }
			
			void renderCounter(const mge::Viewport &vp, float x, float y, int val, const mge::Color &col);
			
		private:
			CurValueViewData &curvaluedata;
			int curtexx, curtexy;
	};
}

#endif
