#ifndef STOEDIT_DIALOG_H
#define STOEDIT_DIALOG_H

namespace mge {
	class Viewport;
}

namespace stoedit {
	class InputEvent;

	class Dialog {
		public:
			inline virtual ~Dialog() { }
			
			virtual int getWidth() const = 0;
			virtual int getHeight() const = 0;
			
			virtual void render(mge::Viewport &out) = 0;
			
			enum DialogOutput {
				NONE,
				CLOSE
			};
			
			virtual DialogOutput handleEvent(const InputEvent &event) = 0; // return true to close dialog
	};
}

#endif
