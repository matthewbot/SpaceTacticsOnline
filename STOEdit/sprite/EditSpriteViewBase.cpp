#include "EditSpriteViewBase.h"
#include "SpriteControllerRes.h"
#include "TransformViewData.h"
#include "SpriteData.h"
#include "CurValueViewData.h"
#include <STOEdit/input/InputEvent.h>
#include <MGE/gfx/Transform.h>
#include <MGE/gfx/Viewport.h>
#include <MGE/gfx/RenderState.h>
#include <MGE/gfx/texture/Texture.h>
#include <MGE/gfx/primitive/Quad.h>
#include <MGE/gfx/primitive/TexQuad.h>
#include <MGE/util/Vector2D.h>
#include <MGE/res/Font.h>
#include <boost/shared_ptr.hpp>
#include <sstream>
#include <iostream>

using namespace stoedit;
using namespace mge;
using namespace std;
using namespace boost;

EditSpriteViewBase::EditSpriteViewBase(ViewProperties &props, int panewidth, int paneheight, SpriteData &data, const SpriteControllerRes &mres, const string &suffix)
: SpriteViewBase(props, panewidth, paneheight, data, mres),
	curvaluedata(CurValueViewData::makeFromProperties(props, suffix)),
  curtexx(0), curtexy(0) { }
EditSpriteViewBase::~EditSpriteViewBase() { }

void EditSpriteViewBase::renderPixels(const Viewport &vp, int texw, int texh) {
	Transform vptrans(vp.getTransform());
	vptrans.invert();
	const ViewSection &rootclip = vp.getRootClip();
	
	Vector2D vec(rootclip.x, rootclip.y);
	vec = vptrans.transform(vec);
	int startx = (int)(vec.getX() - 0.5f + texw/2.0f);
	int starty = (int)(vec.getY() - 0.5f + texh/2.0f);
	
	vec = Vector2D(rootclip.x + rootclip.w, rootclip.y + rootclip.h);
	vec = vptrans.transform(vec);
	int endx = (int)(vec.getX() + 0.5f + texw/2.0f);
	int endy = (int)(vec.getY() + 0.5f + texh/2.0f);
	
	if (startx < 0)
		startx = 0;
	else if (startx >= texw)
		return;
	
	if (starty < 0)
		starty = 0;
	else if (starty >= texh)
		return;
		
	if (endx < 0)
		return;
	else if (endx >= texw)
		endx = texw;
		
	if (endy < 0)
		return;
	else if (endy >= texh)
		endy = texh;

	for (int x=startx; x < endx; x++) {
		for (int y=starty; y < endy; y++) {
			float vpx = x + 0.5f - texw/2;
			float vpy = y + 0.5f - texh/2;
		
			if (vp.contains(vpx, vpy)) {
				bool selected = (x == curtexx && y == curtexy);
				int texy = texh-1 - y;
				
				doRenderPixel(vp, x, texy, vpx, vpy, selected);
			}
		}
	}
}

void EditSpriteViewBase::renderCurrentValue(const mge::Viewport &vp) {
	renderCounter(vp, 0, 0, curvaluedata.get(), Color::WHITE);
}

void EditSpriteViewBase::renderCounter(const mge::Viewport &vp, float x, float y, int val, const Color &col) {
	int lheight = mres.valuefont->getLineHeight()+2;
	int lwidth = mres.valuefont->getWidth("360")+4;
	
	{
		Quad quad(col, x, y, lwidth, lheight);
		vp.render(quad);
	}
	
	x += 1; y += 1;
	lheight -= 2; lwidth -= 2;
	
	{
		Quad quad(Color::BLACK, x, y, lwidth, lheight);
		vp.render(quad);
	}
	
	x += 1; y += 1;
	lheight -= 2; lwidth -= 2;
	
	{
		stringstream buf;
		buf << val;
		string bufstr(buf.str());
		
		int strwidth = mres.valuefont->getWidth(bufstr);
		mres.valuefont->render(vp, x+lwidth-strwidth-1, y, bufstr, Color::WHITE);
	}
}

bool EditSpriteViewBase::handleEvent(const InputEvent &event, int texw, int texh) {
	if (event.getType() == InputEvent::CLICK_HOVER) { // if we're hovering
		Vector2D texpos = getTexPos(event.getMouseX(), event.getMouseY(), texw, texh); // convert mouse to texture position

		curtexx = (int)texpos.getX(); // save our current texture position
		curtexy = (int)texpos.getY();
	}
	
	if (event.getType() == InputEvent::CLICK_SINGLE && event.isKeyHeld(keycodes::lalt)) {
		bool up = (event.getButton() == mousebtns::wheelup);
		bool fast = event.isKeyHeld(keycodes::lshift);
		
		doUpdateValue(curvaluedata.value(), up, fast);
		return true;
	}
	
	if (texw != 0) {
		if ((event.getType() == InputEvent::CLICK_SINGLE || event.getType() == InputEvent::CLICK_DRAG) && event.getButton() == mousebtns::left) {
			Vector2D texpos = getTexPos(event.getMouseX(), event.getMouseY(), texw, texh);
			int texx = (int)texpos.getX();
			int texy = texh-1 - (int)texpos.getY();
			
			if (texx >= 0 && texy >= 0 && texx < texw && texy < texh) {
				doUpdatePixel(curvaluedata.get(), texx, texy);
				return true;
			}
		} else if (event.getType() == InputEvent::CLICK_SINGLE && event.getButton() == mousebtns::middle) {
			Vector2D texpos = getTexPos(event.getMouseX(), event.getMouseY(), texw, texh);
			int texx = (int)texpos.getX();
			int texy = texh-1 - (int)texpos.getY();			
		
			if (texx >= 0 && texy >= 0 && texx < texw && texy < texh) {
				doCopyValue(curvaluedata.value(), texx, texy);
				return true;
			}
		}
	}
	
	return SpriteViewBase::handleEvent(event);
}

void EditSpriteViewBase::doUpdateValue(int &curvalue, bool up, bool fast) {
	int amt = fast ? 10 : 1;

	if (up) {
		curvalue += amt;
		if (curvalue >= 360)
			curvalue -= 360;
	} else {
		curvalue -= amt;
		if (curvalue < 0)
			curvalue += 360;
	}
}

void EditSpriteViewBase::doCopyValue(int &curvalue, int texx, int texy) { }

void EditSpriteViewBase::renderDarkenedSprite(const Viewport &vp, int minzoom) {
	const shared_ptr<Texture> &colortex = data.getColor().getTex();
	
	if (colortex) {
		int texw = colortex->getWidth(), texh = colortex->getHeight();
		
		{
			RenderState state;
			state.texture(colortex);
			
			TexQuad quad(Color::fromInt(100, 100, 100), -texw/2, -texh/2, 0, 0, texw, texh);
			vp.render(state, quad);
		}
		
		if (transdata.getZoom() >= minzoom)
			renderPixels(vp, texw, texh);
	}
}
