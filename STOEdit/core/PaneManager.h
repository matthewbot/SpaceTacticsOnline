#ifndef STOEDIT_PANEMANAGER_H
#define STOEDIT_PANEMANAGER_H

#include <MGE/gfx/ViewSection.h>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

namespace mge {
	class Viewport;
	class Font;
}

namespace stoedit {
	class Pane;
	class PaneLayout;
	class PaneFrameRenderer;
	class InputEvent;

	class PaneManager : boost::noncopyable {
		public:
			PaneManager(PaneFrameRenderer &framerenderer, int width, int height);
			~PaneManager();
			
			void setLayout(const PaneLayout &layout);
			Pane *pickPane(int x, int y);
			
			bool gotEvent(const InputEvent &event);
			void render(mge::Viewport &out);
			
			Pane *getSelectedPane() const;
			
		private:
			void deletePanes();
		
			PaneFrameRenderer &framerenderer;
			int width, height;
		
			struct PaneEntry {
				mge::ViewSection sect;
				Pane *pane;
			};
			
			typedef std::vector<PaneEntry> PaneList;
			PaneList panes;
			PaneList::iterator selectedpane;
			
			PaneList::iterator pickPaneIter(int x, int y);
	};
}

#endif
