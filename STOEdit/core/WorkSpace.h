#ifndef STOEDIT_WORKSPACE_H
#define STOEDIT_WORKSPACE_H

#include "PaneManager.h"
#include "DialogManager.h"
#include "PaneFrameRenderer.h"
#include <STOEdit/input/InputEventListener.h>
#include <boost/shared_ptr.hpp>
#include <memory>

namespace mge {
	class Viewport;
	class Font;
}

namespace stoedit {
	class PaneLayout;
	class Dialog;
	
	struct WorkSpaceProps {
		WorkSpaceProps();
		
		FrameRenderProps frame;
	};

	class WorkSpace : public InputEventListener {
		public:
			WorkSpace(int width, int height);
			WorkSpace(const WorkSpaceProps &props, int width, int height);
			virtual ~WorkSpace();
			
			inline WorkSpaceProps &getProps() { return props; }
			inline const WorkSpaceProps &getProps() const { return props; }
			inline PaneManager &getPanes() { return panes; }
			inline const PaneManager &getPanes() const { return panes; }
			inline DialogManager &getDialogManager() { return dialogman; }
			inline const DialogManager &getDialogManager() const { return dialogman; }
			
			void render(mge::Viewport &view);
			
			bool gotEvent(const InputEvent &event);
		
		private:
			WorkSpaceProps props;
		
			PaneFrameRenderer renderer;
			PaneManager panes;
			DialogManager dialogman;
			
			boost::shared_ptr<mge::Font> titlefont;
	};
}

#endif
