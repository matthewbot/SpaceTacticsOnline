#ifndef STOEDIT_SPRITEVIEWBASE_H
#define STOEDIT_SPRITEVIEWBASE_H

#include <STOEdit/core/View.h>

namespace mge {
	class Transform;
	class Vector2D;
}

namespace stoedit {
	class ViewProperties;
	class SpriteData;
	struct SpriteControllerRes;
	class TransformViewData;

	class SpriteViewBase : public View {
		public:
			SpriteViewBase(ViewProperties &props, int panewidth, int paneheight, SpriteData &data, const SpriteControllerRes &res);
			virtual ~SpriteViewBase();
	
		protected:
			void renderContents(const mge::Viewport &view);
			bool handleEvent(const InputEvent &event);
		
			virtual void doRenderContents(const mge::Viewport &view) = 0;
			
			mge::Transform getContentsTransform() const;
			mge::Vector2D getTexPos(int mousex, int mousey, int texw, int texh);
			mge::Vector2D getViewPos(int texx, int texy, int texw, int texh);
		
			SpriteData &data;
			const SpriteControllerRes &mres;
			int panewidth, paneheight;
			
			TransformViewData &transdata;
			
		private:
			void doTranslate(int deltax, int deltay);
			void doScale(float amt, int xpos, int ypos);
			void doReset();
			
			int prevdragx, prevdragy;
	};
}

#endif
