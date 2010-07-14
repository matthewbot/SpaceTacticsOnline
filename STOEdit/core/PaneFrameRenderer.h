#ifndef STOEDIT_PANEFRAMERENDERER_H
#define STOEDIT_PANEFRAMERENDERER_H

#include <boost/shared_ptr.hpp>
#include <MGE/gfx/util/Color.h>
#include <MGE/gfx/ViewSection.h>
#include <string>

namespace mge {
	class Font;
	class Viewport;
}

namespace stoedit {
	struct FrameRenderProps {
		boost::shared_ptr<mge::Font> titlefont;
		mge::Color bordercolor, titlecolor, seltitlecolor;
		int bordersize;
	};

	class PaneFrameRenderer { 
		public:
			PaneFrameRenderer(const FrameRenderProps &props); // stores reference
			~PaneFrameRenderer();
			
			mge::ViewSection getSubsection(int panewidth, int paneheight);
			void renderFrame(mge::Viewport &view, int panewidth, int paneheight, const std::string &title, bool selected);
			
		private:
			const FrameRenderProps &props;
			
			void drawBorders(mge::Viewport &view, int width, int height); 
			int drawTitleBar(mge::Viewport &view, int width, int height, const std::string &title, bool selected);
			
			static void drawQuadRect(mge::Viewport &view, const mge::Color &color, float x, float y, float w, float h, float thickness);
	};
}

#endif
