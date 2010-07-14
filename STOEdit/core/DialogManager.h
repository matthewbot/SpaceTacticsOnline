#ifndef STOEDIT_DIALOGMANAGER_H
#define STOEDIT_DIALOGMANAGER_H

#include <memory>

namespace mge {
	class Viewport;
}

namespace stoedit {
	class Dialog;
	class InputEvent;

	class DialogManager {
		public:
			DialogManager(int screenwidth, int screenheight);
			~DialogManager();
			
			void setDialog(Dialog *dialog);
			void clearDialog();
			bool hasDialog() const;
			
			void render(mge::Viewport &vp);
			bool gotEvent(const InputEvent &event); // relative to workspace
			
		private:
			int screenwidth, screenheight;
			std::auto_ptr<Dialog> dialog;
			bool dialogchanged;
	};
}

#endif
