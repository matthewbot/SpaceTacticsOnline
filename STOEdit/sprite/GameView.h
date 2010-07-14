#ifndef STOEDIT_GAMEVIEW_H
#define STOEDIT_GAMEVIEW_H

#include "SpriteViewBase.h"

namespace stoedit {
	class ViewProperties;
	class TransformViewData;
	class SpriteData;
	class SpriteControllerRes;

	class GameView : public SpriteViewBase {
		public:
			GameView(ViewProperties &props, int panewidth, int paneheight, SpriteData &data, const SpriteControllerRes &mres);
			virtual ~GameView();
			
			// --- View ---
			
			virtual void render(const mge::Viewport &view);
			virtual bool gotEvent(const InputEvent &event);
			virtual std::string getTitle();
			
		protected:
			virtual void doRenderContents(const mge::Viewport &view);

		private:
			void drawAngleIndicator(const mge::Viewport &vp);
		
			float spriteangle;
			float lightangle;
			int rendertype;
			
			bool smoothcolor, smoothnormal;
			
			float prevmouseangle;
			
			const static int MAX_RENDERTYPE = 2;
	};
}

#endif
