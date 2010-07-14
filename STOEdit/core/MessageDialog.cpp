#include "MessageDialog.h"
#include <STOEdit/input/InputEvent.h>
#include <MGE/gfx/Viewport.h>
#include <MGE/res/Font.h>
#include <cctype>

using namespace stoedit;
using namespace mge;
using namespace boost;
using namespace std;

MessageDialog::MessageDialog(const shared_ptr<mge::Font> &font, const string &msg, int width)
: font(font), msg(msg), width(width) { }

MessageDialog::~MessageDialog() { }

int MessageDialog::getWidth() const { return width; }
int MessageDialog::getHeight() const { return font->getLineHeight(); }

void MessageDialog::render(Viewport &vp) {
	font->render(vp, 0, 0, msg);
}

Dialog::DialogOutput MessageDialog::handleEvent(const InputEvent &event) {
	if (event.getType() == InputEvent::KEY_PRESSED || event.getType() == InputEvent::CLICK_SINGLE)
		return Dialog::CLOSE;
	
	return Dialog::NONE;
}
