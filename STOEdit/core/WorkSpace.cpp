#include "WorkSpace.h"
#include "ViewFactory.h"
#include "Pane.h"
#include <STOEdit/input/InputEvent.h>
#include <MGE/res/Font.h>
#include <MGE/gfx/util/Color.h>

using namespace stoedit;
using namespace mge;
using namespace std;
using namespace boost;

WorkSpace::WorkSpace(int width, int height) 
: props(), renderer(props.frame), panes(renderer, width, height), dialogman(width, height) { }

WorkSpace::WorkSpace(const WorkSpaceProps &pr, int width, int height) 
: props(pr), renderer(props.frame), panes(renderer, width, height), dialogman(width, height) { }

WorkSpace::~WorkSpace() { }

void WorkSpace::render(Viewport &out) {	
	panes.render(out);
	dialogman.render(out);
}

bool WorkSpace::gotEvent(const InputEvent &event) {
	if (dialogman.gotEvent(event)) 
		return true;

	return panes.gotEvent(event);
}

WorkSpaceProps::WorkSpaceProps() {
	frame.bordersize = 2;
	frame.bordercolor = Color::fromInt(200, 200, 200);
	frame.titlecolor = Color::fromInt(100, 100, 100);
	frame.seltitlecolor = Color::fromInt(100, 100, 180);
}
