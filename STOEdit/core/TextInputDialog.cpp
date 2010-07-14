#include "TextInputDialog.h"
#include "TextInputDialogCallback.h"
#include <STOEdit/input/InputEvent.h>
#include <MGE/gfx/Viewport.h>
#include <MGE/res/Font.h>
#include <cctype>
#include <iostream>

using namespace stoedit;
using namespace mge;
using namespace boost;
using namespace std;

TextInputDialog::TextInputDialog(TextInputDialogCallback *callback, const shared_ptr<mge::Font> &font, const string &prompt, int width)
: callback(callback), font(font), prompt(prompt), width(width) { }

TextInputDialog::~TextInputDialog() { }

int TextInputDialog::getWidth() const { return width; }
int TextInputDialog::getHeight() const { return font->getLineHeight()*2; }

void TextInputDialog::render(Viewport &vp) {
	font->render(vp, 0, font->getLineHeight(), prompt);
	font->render(vp, 0, 0, outbuf + string("_"));
}

Dialog::DialogOutput TextInputDialog::handleEvent(const InputEvent &event) {
	if (event.getType() == InputEvent::KEY_PRESSED) {
		int c = event.getChar();
		if (c) {
			if (isprint(c)) {
				outbuf.append(1, (char)c);
			} else if (c == '\b') {
				if (outbuf.length() > 0)
					outbuf.erase(outbuf.end()-1);
			} else if (c == '\r') {
				callback->gotInput(outbuf);
				return Dialog::CLOSE;
			} else if (c == keycodes::escape) { // keycodes are equilivent to ASCII when possible
				callback->gotCancel();
				return Dialog::CLOSE;
			}
		}
	}
	
	return Dialog::NONE;
}
