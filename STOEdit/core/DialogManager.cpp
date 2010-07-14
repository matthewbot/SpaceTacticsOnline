#include "DialogManager.h"
#include "PaneFrameRenderer.h"
#include "Dialog.h"
#include <STOEdit/input/InputEvent.h>
#include <MGE/gfx/Viewport.h>
#include <MGE/gfx/ViewSection.h>
#include <MGE/gfx/primitive/Quad.h>
#include <MGE/gfx/util/Color.h>
#include <cassert>

using namespace stoedit;
using namespace mge;
using namespace std;

DialogManager::DialogManager(int screenwidth, int screenheight) 
: screenwidth(screenwidth), screenheight(screenheight) { }
DialogManager::~DialogManager() { }

void DialogManager::setDialog(Dialog *newdialog) {
	dialog = auto_ptr<Dialog>(newdialog);
	dialogchanged = true;
}

void DialogManager::clearDialog() {
	dialog.reset();
}

bool DialogManager::hasDialog() const {
	return dialog.get() != 0;
}

void DialogManager::render(Viewport &vp) {
	if (!dialog.get())
		return;
		
	int width = dialog->getWidth()+4; // 2 pixel border on both sides
	int height = dialog->getHeight()+4;
	int xpos = screenwidth/2-width/2;
	int ypos = screenheight/2-height/2;


	vp.render(Quad(Color::WHITE, xpos, ypos, width, height));
	vp.render(Quad(Color::BLACK, xpos+1, ypos+1, width-2, height-2));
	
	ViewSection clip = { xpos+2, ypos+2, width-4, height-4 };
	Viewport clipvp(vp, clip);
	
	Transform trans;
	trans.translate(xpos+2, ypos+2);
	
	Viewport dialogvp(clipvp, trans);
	
	dialog->render(dialogvp);
}

bool DialogManager::gotEvent(const InputEvent &event) {
	if (!dialog.get())
		return false;
		
	InputEvent newevent;
	
	int dwidth = dialog->getWidth(), dheight = dialog->getHeight();
	ViewSection oldsection = { screenwidth/2-dwidth/2, screenheight/2-dheight/2, dwidth, dheight };
	
	if (oldsection.inside(event.getMouseX(), event.getMouseY())) { // if its in bounds
		ViewSection newsection = { 0, 0, dwidth, dheight }; // prepare its inner section
		newevent = InputEvent(event, oldsection, newsection); // and translate the event
	} else { // out of bounds
		if (event.getType() == InputEvent::KEY_PRESSED || event.getType() == InputEvent::KEY_RELEASED)  // is it a keyboard event?
			newevent = InputEvent(event.getType(), 0, 0, event.beginKeys(), event.endKeys(), event.getKey(), event.getChar(), 0); // clone it, but 0 out the mouse coords (TODO: constructor for this)
		else // not keyboard event?
			return true; // they don't get it
	} 
	
	dialogchanged = false; // TODO: fix hack...
	if (dialog->handleEvent(newevent) == Dialog::CLOSE)
		if (!dialogchanged)
			clearDialog();
		
	return true;
}
