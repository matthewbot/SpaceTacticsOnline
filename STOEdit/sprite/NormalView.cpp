#include "NormalView.h"
#include "SpriteData.h"
#include "TransformViewData.h"
#include "SpriteControllerRes.h"
#include <STOEdit/input/InputEvent.h>
#include <MGE/gfx/Viewport.h>
#include <MGE/gfx/RenderState.h>
#include <MGE/gfx/texture/Texture.h>
#include <MGE/gfx/primitive/TexQuad.h>
#include <MGE/gfx/primitive/Line.h>
#include <MGE/gfx/primitive/Quad.h>
#include <MGE/gfx/util/Color.h>
#include <MGE/util/Vector2D.h>
#include <MGE/res/Font.h>
#include <iostream>
#include <cmath>
#include <cassert>
#include <sstream>

using namespace stoedit;
using namespace mge;
using namespace std;
using namespace boost;

NormalView::NormalView(ViewProperties &props, int panewidth, int paneheight, SpriteData &data, const SpriteControllerRes &mres) 
: EditSpriteViewBase(props, panewidth, paneheight, data, mres, "NormalView") { }
  
NormalView::~NormalView() { }

void NormalView::render(const Viewport &vp) {
	renderContents(vp);
	renderCurrentValue(vp);
	renderHoverCounter(vp);
}

void NormalView::doRenderContents(const Viewport &vp) {
	renderDarkenedSprite(vp, 20);
}

void NormalView::doRenderPixel(const Viewport &vp, int texx, int texy, float vpx, float vpy, bool selected) {
	const FloatMap::pixel_t &pix = data.getNormal().getFloats().pix(texx, texy);

	Color col = selected ? Color::RED : Color::WHITE;

	if (pix.nx != 0 || pix.ny != 0) {
		float dir = atan2(pix.ny, pix.nx);

		drawArrow(vp, vpx, vpy, dir, col);
	}
}

void NormalView::drawArrow(const Viewport &out, float x, float y, float rad, const Color &color) {
	float cosrad = cos(rad), sinrad = sin(rad);
	float cosradh = cos(rad+PI/2), sinradh = sin(rad+PI/2);

	float tipx = x+0.5f*cosrad, tipy = y+0.5f*sinrad;
	float tailx = x-0.2f*cosrad, taily = y-0.2f*sinrad;
	float cross1x = x+0.15f*cosradh, cross1y = y+0.15f*sinradh;
	float cross2x = x-0.15f*cosradh, cross2y = y-0.15f*sinradh;

	out.render(Line(color, tailx, taily, tipx, tipy));
	out.render(Line(color, cross1x, cross1y, cross2x, cross2y));
}

void NormalView::doUpdatePixel(int curvalue, int texx, int texy) {
	FloatMap::pixel_t &pix = data.getNormal().getFloats().pix(texx, texy);
	
	float mag = sqrt(pix.nx*pix.nx + pix.ny*pix.ny);
	float dir = (float)curvalue / 180 * PI;
	
	pix.nx = mag*cos(dir);
	pix.ny = mag*sin(dir);
	
	data.getNormal().regenTex();
}

void NormalView::doCopyValue(int &curvalue, int texx, int texy) {
	FloatMap::pixel_t &pix = data.getNormal().getFloats().pix(texx, texy);
	
	float angle = atan2(pix.ny, pix.nx);
	
	curvalue = (int)(angle/PI*180);
	if (curvalue < 0)
		curvalue += 360;
}

void NormalView::renderHoverCounter(const mge::Viewport &vp) {
	const FloatPixTex &pixels = data.getNormal();
	int texx = getCurTexX(), texy = getCurTexY(pixels.getHeight());

	
	if (texx < 0 || texy < 0)
		return;
	if (texx >= pixels.getWidth() || texy >= pixels.getHeight())
		return;
	
	const FloatMap::pixel_t &pix = pixels.getFloats().pix(texx, texy);
	
	if (pix.nx == 0 && pix.ny == 0)
		return;
	
	int val = (int)(atan2(pix.ny, pix.nx) / PI * 180);
	if (val < 0)
		val += 360;
	
	renderCounter(vp, 100, 0, val, Color::RED);
}

bool NormalView::gotEvent(const InputEvent &event) { 
	if (event.getType() == InputEvent::KEY_PRESSED) {
		char ch = event.getChar();
		if (ch == 'f' && event.isKeyHeld(keycodes::lalt)) {
			int curval = getCurValue();
			curval += 180;
			if (curval >= 360)
				curval -= 360;
			setCurValue(curval);
			return true;
		} else if (ch == 'm') {
			flipNormals();
			return true;
		}
	}

	const shared_ptr<Texture> &colortex = data.getColor().getTex();
	if (colortex)
		return EditSpriteViewBase::handleEvent(event, colortex->getWidth(), colortex->getHeight());
	else
		return EditSpriteViewBase::handleEvent(event, -1, -1);
}

void NormalView::flipNormals() {
	FloatPixTex &tex = data.getNormal();
	FloatMap &pixmap = tex.getFloats();
	
	int texxstart = tex.getWidth() / 2;
	if (tex.getWidth() % 2)
		texxstart++;
	
	int texx,texy;
	for (texx=texxstart; texx < tex.getWidth(); texx++) {
		for (texy=0; texy < tex.getHeight(); texy++) {
			int otexx = tex.getWidth() - texx - 1;
			
			FloatMap::pixel_t &pix = pixmap.pix(texx, texy);
			const FloatMap::pixel_t &opix = pixmap.pix(otexx, texy);
			
			pix.nx = -opix.nx;
			pix.ny = opix.ny;
		}
	}
	
	tex.regenTex();
}

string NormalView::getTitle() { return "Normal view"; }
