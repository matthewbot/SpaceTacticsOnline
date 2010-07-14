#include "Pane.h"
#include "View.h"
#include "ViewFactory.h"
#include "PaneFrameRenderer.h"
#include <STOEdit/input/InputEvent.h>
#include <MGE/gfx/Viewport.h>
#include <MGE/gfx/primitive/Quad.h>
#include <MGE/gfx/primitive/Point.h>
#include <MGE/res/Font.h>
#include <iostream>

using namespace mge;
using namespace stoedit;
using namespace std;

Pane::Pane(PaneFrameRenderer &framerenderer, int width, int height) 
: framerenderer(framerenderer), width(width), height(height), innersection(framerenderer.getSubsection(width, height)) { }
Pane::~Pane() { }

void Pane::clearView() {
	view.reset();
}

void Pane::setView(ViewFactory &viewfact) {
	view = viewfact.makeView(props, innersection.w, innersection.h);
}

void Pane::render(Viewport &out,  bool selected) {
	string title = view.get() ? view->getTitle() : "Empty";

	framerenderer.renderFrame(out, width, height, title, selected);

	if (view.get()) {
		Viewport clipview(out, innersection); // TODO: make helper function/extra constructor
		
		Transform trans;
		trans.translate(innersection.x, innersection.y);
		Viewport transview(clipview, trans);
		
		transview.render(Point(Color::RED, 0, 0));
		view->render(transview);
	}
}

bool Pane::gotEvent(const InputEvent &event) {
	if (view.get()) {
		ViewSection oldsection = {0, 0, width, height };
		InputEvent innerevent(event, oldsection, innersection);
	
		return view->gotEvent(innerevent);
	}
	
	return false;
}
