#include "PaneManager.h"
#include "Pane.h"
#include "PaneLayout.h"
#include "PaneFrameRenderer.h"
#include <STOEdit/input/InputEvent.h>
#include <MGE/gfx/Viewport.h>
#include <MGE/gfx/primitive/Point.h>
#include <MGE/res/Font.h>

using namespace stoedit;
using namespace mge;

PaneManager::PaneManager(PaneFrameRenderer &framerenderer, int width, int height) 
: framerenderer(framerenderer), width(width), height(height), selectedpane(panes.end()) { }

PaneManager::~PaneManager() {
	deletePanes();
}

void PaneManager::deletePanes() {
	for (PaneList::iterator i = panes.begin(); i != panes.end(); ++i) {
		delete i->pane;
	}
	panes.clear();
	selectedpane = panes.end();
}

void PaneManager::setLayout(const PaneLayout &layout) {
	deletePanes();

	for (PaneLayout::const_iterator i = layout.begin(); i != layout.end(); ++i) {
		PaneEntry entry = { *i, new Pane(framerenderer, i->w, i->h) };
		panes.push_back(entry);
	}
	selectedpane = panes.end();
}

Pane *PaneManager::getSelectedPane() const {
	if (selectedpane == panes.end())
		return NULL;
	else
		return selectedpane->pane;
}

void PaneManager::render(Viewport &out) {
	for (PaneList::iterator i = panes.begin(); i != panes.end(); ++i) {
		Viewport clippedview(out, i->sect); // make a clipped view
		
		Transform trans;
		trans.translate(i->sect.x, i->sect.y);
		Viewport transview(clippedview, trans); // then make a translated view from the clipped view
		
		i->pane->render(transview, i == selectedpane);
	}
}

bool PaneManager::gotEvent(const InputEvent &event) {
	if (event.getType() == InputEvent::CLICK_SINGLE && event.getButton() == mousebtns::left) {
		PaneList::iterator pane = pickPaneIter(event.getMouseX(), event.getMouseY());
		if (pane != panes.end() && pane != selectedpane) {
			selectedpane = pane;
			return true;
		}
	}
	
	if (selectedpane != panes.end()) {
		ViewSection &oldsection = selectedpane->sect;
		ViewSection newsection = { 0, 0, selectedpane->sect.w, selectedpane->sect.h };
		
		InputEvent localevent(event, oldsection, newsection);
		return selectedpane->pane->gotEvent(localevent);
	}
	
	return false;
}

Pane *PaneManager::pickPane(int x, int y) {
	PaneList::iterator i = pickPaneIter(x, y);
	return i != panes.end() ? i->pane : NULL;
}

PaneManager::PaneList::iterator PaneManager::pickPaneIter(int x, int y) {
	for (PaneList::iterator i = panes.begin(); i != panes.end(); ++i) {
		ViewSection &s = i->sect;
		if (s.x < x && s.y < y && s.x + s.w > x && s.y + s.h > y)
			return i;
	}
	
	return panes.end();
}
