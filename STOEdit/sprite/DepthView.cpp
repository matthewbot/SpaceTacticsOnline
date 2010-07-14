#include "DepthView.h"
#include "SpriteData.h"
#include "TransformViewData.h"
#include "SpriteControllerRes.h"
#include <STOEdit/input/InputEvent.h>
#include <MGE/gfx/Viewport.h>
#include <MGE/gfx/RenderState.h>
#include <MGE/gfx/texture/Texture.h>
#include <MGE/gfx/primitive/TexQuad.h>
#include <MGE/gfx/primitive/Quad.h>
#include <MGE/gfx/primitive/Line.h>
#include <MGE/gfx/util/Color.h>
#include <MGE/util/Vector2D.h>
#include <MGE/res/Font.h>
#include <cmath>
#include <iostream>
#include <sstream>

using namespace std;
using namespace stoedit;
using namespace mge;
using namespace boost;

DepthView::DepthView(ViewProperties &props, int panewidth, int paneheight, SpriteData &data, const SpriteControllerRes &mres) 
: EditSpriteViewBase(props, panewidth, paneheight, data, mres, "DepthView") { }
  
DepthView::~DepthView() { }

void DepthView::render(const Viewport &vp) {
	renderContents(vp);
	renderCurrentValue(vp);
}

void DepthView::doRenderContents(const Viewport &vp) {
	renderDarkenedSprite(vp, 20);
}

void DepthView::doRenderPixel(const Viewport &vp, int texx, int texy, float vpx, float vpy, bool selected) {
	const FloatMap::pixel_t &pix = data.getNormal().getFloats().pix(texx, texy);

	float depth = sqrt(pix.nx*pix.nx + pix.ny*pix.ny);

	Color color = selected ? Color::RED : Color::WHITE;
		
	if (depth > 0) {
		drawDepthIndicator(vp, vpx, vpy, depth, color);
	} else {
		Quad quad(color, vpx-0.1f, vpy-0.1f, 0.2f, 0.2f);
		
		vp.render(quad);
	}
}

void DepthView::drawDepthIndicator(const Viewport &vp, float x, float y, float amt, const Color &col) {
	stringstream buf;
	buf << ceil(amt*100); // could use a C string and sprintf if this becomes inefficient
	string amtstr(buf.str());
	
	int linewidth = mres.valuefont->getWidth(amtstr);
	int lineheight = mres.valuefont->getLineHeight();
	
	Transform fonttrans;
	fonttrans.scale(1.0f/(linewidth+6), 1.0f/(lineheight+6));
	fonttrans.translate(x, y);
	
	mres.valuefont->render(vp, -linewidth/2, -lineheight/2, buf.str(), col, fonttrans);
}

void DepthView::doUpdatePixel(int curvalue, int texx, int texy) {
	FloatMap::pixel_t &pix = data.getNormal().getFloats().pix(texx, texy);
	
	float mag = (float)curvalue/100;
	float dir = atan2(pix.ny, pix.nx);
	
	pix.nx = mag*cos(dir);
	pix.ny = mag*sin(dir);
	
	data.getNormal().regenTex();
}

void DepthView::doCopyValue(int &curvalue, int texx, int texy) {
	FloatMap::pixel_t &pix = data.getNormal().getFloats().pix(texx, texy);
	
	float mag = sqrt(pix.nx*pix.nx + pix.ny*pix.ny);
	
	curvalue = (int)(mag*100);
}

bool DepthView::gotEvent(const InputEvent &event) {
	if (event.getType() == InputEvent::KEY_PRESSED) {
		char ch = event.getChar();
		if (ch == 'u') {
			adjustAllDepth(getCurValue());
			return true;
		} else if (ch == 'd') {
			adjustAllDepth(-getCurValue());
			return true;
		}
	}

	const shared_ptr<Texture> &colortex = data.getColor().getTex();
	if (colortex)
		return EditSpriteViewBase::handleEvent(event, colortex->getWidth(), colortex->getHeight());
	else
		return EditSpriteViewBase::handleEvent(event, -1, -1);
}

void DepthView::adjustAllDepth(int amt) {
	FloatPixTex &tex = data.getNormal();
	FloatMap &pixmap = tex.getFloats();
	
	int texx,texy;
	for (texx=0; texx < tex.getWidth(); texx++) {
		for (texy=0; texy < tex.getHeight(); texy++) {
			FloatMap::pixel_t &pix = pixmap.pix(texx, texy);
			
			float mag = sqrt(pix.nx*pix.nx + pix.ny*pix.ny);
			if (mag < 0.01f)
				continue;
			float dir = atan2(pix.ny, pix.nx);
			
			mag += amt/100.0f;
			if (mag > 1)
				mag = 1;
			else if (mag < 0)
				mag = 0;
				
			pix.nx = mag * cos(dir);
			pix.ny = mag * sin(dir);
		}
	}
	
	tex.regenTex();
}

string DepthView::getTitle() { return "Depth view"; }
