#ifndef STOEDIT_MESSAGEDIALOG_H
#define STOEDIT_MESSAGEDIALOG_H

#include "Dialog.h"
#include <string>
#include <boost/shared_ptr.hpp>
#include <boost/scoped_ptr.hpp>
#include <vector>

namespace mge {
	class Font;
}

namespace stoedit {
	class MessageDialog : public Dialog {
		public:
			MessageDialog(const boost::shared_ptr<mge::Font> &font, const std::string &msg, int width);
			virtual ~MessageDialog();
			
		// --- Dialog ---
			
			virtual int getWidth() const;
			virtual int getHeight() const;
			
			virtual void render(mge::Viewport &out);
			virtual DialogOutput handleEvent(const InputEvent &event);
			
		private:
			boost::shared_ptr<mge::Font> font;
			std::string msg;
			int width;
	};
}

#endif
