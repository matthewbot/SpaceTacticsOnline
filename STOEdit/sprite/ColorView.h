#ifndef STOEDIT_COLORVIEW_H
#define STOEDIT_COLORVIEW_H

#include "SpriteViewBase.h"

namespace stoedit {
	class ViewProperties;
	class TransformViewData;
	class SpriteData;
	class SpriteControllerRes;

	class ColorView : public SpriteViewBase {
		public:
			ColorView(ViewProperties &props, int panewidth, int paneheight, SpriteData &data, const SpriteControllerRes &mres);
			virtual ~ColorView();
			
			// --- View ---
			
			virtual void render(const mge::Viewport &view);
			virtual bool gotEvent(const InputEvent &event);
			virtual std::string getTitle();
			
		protected:
			virtual void doRenderContents(const mge::Viewport &view);
	};
}

#endif
