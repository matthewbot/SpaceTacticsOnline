#include "FPSOverlay.h"
#include <STOEdit/input/InputEvent.h>
#include <MGE/gfx/renderer/RenderStats.h>
#include <MGE/gfx/system/GraphicsSystem.h>
#include <MGE/gfx/Viewport.h>
#include <MGE/res/Font.h>
#include <sstream>

using namespace stoedit;
using namespace mge;
using namespace std;

FPSOverlay::FPSOverlay(const boost::shared_ptr<mge::Font> &font) : show(false), font(font) { }
FPSOverlay::~FPSOverlay() { }

bool FPSOverlay::gotEvent(const InputEvent &event) {
	if (event.getType() == InputEvent::KEY_PRESSED || event.getType() == InputEvent::KEY_RELEASED) {
		if (event.getKey() == '`') {
			if (event.getType() == InputEvent::KEY_PRESSED)
				show = !show;
				
			return true;
		}
	}
	
	return false;
}

void FPSOverlay::render(Viewport &vp, const GraphicsSystem &gfx) {
	if (show) {
		stringstream buf;
		buf << "FPS " << gfx.getTimer().getFPS() << " " << gfx.getRenderManager().getStats();
		font->render(vp, 20, gfx.getDisplay().getHeight()-20, buf.str());
	}
}
