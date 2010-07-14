#include "SpriteViewBase.h"
#include "TransformViewData.h"
#include <MGE/gfx/Viewport.h>
#include <MGE/util/Vector2D.h>
#include <STOEdit/input/InputEvent.h>

using namespace stoedit;
using namespace mge;
using namespace std;

SpriteViewBase::SpriteViewBase(ViewProperties &props, int panewidth, int paneheight, SpriteData &data, const SpriteControllerRes &mres) 
: data(data), mres(mres), panewidth(panewidth), paneheight(paneheight),
  transdata(TransformViewData::makeFromProperties(props)) { }
SpriteViewBase::~SpriteViewBase() { }

void SpriteViewBase::renderContents(const Viewport &vp) {
	Viewport contentsvp(vp, getContentsTransform());
	doRenderContents(contentsvp);
}

Vector2D SpriteViewBase::getTexPos(int mousex, int mousey, int texw, int texh) {
	Transform viewtrans(getContentsTransform());
	viewtrans.invert();
	
	Vector2D texpos = viewtrans.transform(Vector2D(mousex, mousey));
	
	return texpos + Vector2D(texw/2, texh/2);
}

mge::Vector2D SpriteViewBase::getViewPos(int texx, int texy, int texw, int texh) {
	Transform viewtrans(getContentsTransform());
	
	return viewtrans.transform(Vector2D(texx - texw/2.0f + .5f, texy - texh/2.0f + .5f));
}

Transform SpriteViewBase::getContentsTransform() const {
	Transform trans(transdata.getTransform());
	trans.translate(panewidth/2, paneheight/2);
	
	return trans;
}

static const float SCALEFACT = 1.2f;

bool SpriteViewBase::handleEvent(const InputEvent &event) {
	if (event.getType() == InputEvent::CLICK_SINGLE || event.getType() == InputEvent::CLICK_DOUBLE || event.getType() == InputEvent::CLICK_DRAG) {
		if (event.getButton() == mousebtns::wheelup) {
			doScale(SCALEFACT, event.getMouseX(), event.getMouseY());
			return true;
		} else if (event.getButton() == mousebtns::wheeldown) {
			doScale(1.0f/SCALEFACT, event.getMouseX(), event.getMouseY());
			return true;
		}
		
		if (event.getButton() == mousebtns::right) {
			if (event.getType() == InputEvent::CLICK_DOUBLE) {
				doReset();
			} else if (event.getType() == InputEvent::CLICK_DRAG) {
				int deltax = event.getMouseX() - prevdragx, deltay = event.getMouseY() - prevdragy;
				doTranslate(deltax, deltay);
			}
			
			prevdragx = event.getMouseX(); prevdragy = event.getMouseY();
			return true;
		}
	}
	
	return false;
}


void SpriteViewBase::doTranslate(int deltax, int deltay) {
	transdata.setTranslateX(transdata.getTranslateX() + deltax);
	transdata.setTranslateY(transdata.getTranslateY() + deltay);
}

void SpriteViewBase::doScale(float amt, int xpos, int ypos) {
	transdata.setZoom(transdata.getZoom() * amt);
	transdata.setTranslateX(transdata.getTranslateX() * amt);
	transdata.setTranslateY(transdata.getTranslateY() * amt);
}

void SpriteViewBase::doReset() {
	transdata.reset();
}
