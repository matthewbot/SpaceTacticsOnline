#include "ColorView.h"
#include "SpriteData.h"
#include <MGE/gfx/Viewport.h>
#include <MGE/gfx/RenderState.h>
#include <MGE/gfx/texture/Texture.h>
#include <MGE/gfx/primitive/TexQuad.h>
#include <MGE/gfx/util/Color.h>
#include <iostream>

using namespace std;
using namespace stoedit;
using namespace mge;
using namespace boost;

ColorView::ColorView(ViewProperties &props, int panewidth, int paneheight, SpriteData &data, const SpriteControllerRes &mres) 
: SpriteViewBase(props, panewidth, paneheight, data, mres) { }
ColorView::~ColorView() { }

void ColorView::render(const Viewport &vp) {
	renderContents(vp);
}

void ColorView::doRenderContents(const Viewport &vp) {
	const shared_ptr<Texture> &tex = data.getColor().getTex();
	
	if (tex) {
		int texw = tex->getWidth(), texh = tex->getHeight(); // TODO: TexQuad helper method
		TexQuad quad(Color::WHITE, -texw/2, -texh/2, 0, 0, texw, texh);	
		
		RenderState state;
		state.texture(tex);
		
		vp.render(state, quad);
	}
}

bool ColorView::gotEvent(const InputEvent &event) {
	return SpriteViewBase::handleEvent(event);
}

string ColorView::getTitle() { return "Color view"; }
