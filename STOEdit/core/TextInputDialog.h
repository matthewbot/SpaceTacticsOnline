#ifndef STOEDIT_TEXTINPUTDIALOG_H
#define STOEDIT_TEXTINPUTDIALOG_H

#include "Dialog.h"
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <vector>

namespace mge {
	class Font;
}

namespace stoedit {
	class TextInputDialogCallback;

	class TextInputDialog : public Dialog {
		public:
			TextInputDialog(TextInputDialogCallback *callback, const boost::shared_ptr<mge::Font> &font, const std::string &prompt, int width);
			virtual ~TextInputDialog();
			
		// --- Dialog ---
			
			virtual int getWidth() const;
			virtual int getHeight() const;
			
			virtual void render(mge::Viewport &out);
			virtual DialogOutput handleEvent(const InputEvent &event);
			
		private:
			boost::scoped_ptr<TextInputDialogCallback> callback;
			boost::shared_ptr<mge::Font> font;
			std::string prompt;
			int width;
			
			std::string outbuf;
	};
}

#endif
