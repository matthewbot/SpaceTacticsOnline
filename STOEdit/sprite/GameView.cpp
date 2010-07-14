#include "GameView.h"
#include "SpriteData.h"
#include "SpriteControllerRes.h"
#include <STOEdit/input/InputEvent.h>
#include <MGE/gfx/Viewport.h>
#include <MGE/gfx/RenderState.h>
#include <MGE/gfx/texture/Texture.h>
#include <MGE/gfx/primitive/MultiTexQuad.h>
#include <MGE/gfx/util/Color.h>
#include <MGE/gfx/primitive/Quad.h>
#include <MGE/res/Shader.h>
#include <iostream>
#include <cmath>

using namespace std;
using namespace stoedit;
using namespace mge;
using namespace boost;

GameView::GameView(ViewProperties &props, int panewidth, int paneheight, SpriteData &data, const SpriteControllerRes &mres) 
: SpriteViewBase(props, panewidth, paneheight, data, mres),
  spriteangle(0), lightangle(90), rendertype(0),
  smoothcolor(false), smoothnormal(false) { }
GameView::~GameView() { }

void GameView::render(const Viewport &vp) {
	renderContents(vp);
	
	drawAngleIndicator(vp);
}

void GameView::doRenderContents(const Viewport &vp) {
	const shared_ptr<Texture> &tex = data.getColor().getTex();
	const shared_ptr<Texture> &normtex = data.getNormal().getTex();
	
	if (tex) {
		int texw = tex->getWidth(), texh = tex->getHeight();
		MultiTexQuad<2> quad(Color::WHITE, -texw/2, -texh/2, texw, texh);	
		
		quad[0].texes[0].set(0, 0); // set up tex coords for 0
		quad[1].texes[0].set(texw, 0);
		quad[2].texes[0].set(texw, texh);
		quad[3].texes[0].set(0, texh);
		quad.cloneTexes(0, 1); // clone from 0 to 1
		
		RenderState state;
		state.program(mres.gameshader->getProgram());
		state.programVar("lightvec", ShaderVariableValue(cos(lightangle), sin(lightangle)));
		state.programVar("rendertype", ShaderVariableValue(rendertype));
		state.texture(!smoothcolor ? tex : data.getColor().getSmoothTex(), 0);
		state.texture(!smoothnormal ? normtex : data.getNormal().getSmoothTex(), 1);
		
		Transform trans;
		trans.rotate(spriteangle);
		
		vp.render(state, trans, quad);
	}
}

void GameView::drawAngleIndicator(const Viewport &vp) {
	Transform trans;
	
	trans.translate(min(panewidth, paneheight)/2 - 8, 0);	
	trans.rotate(lightangle);
	trans.translate(panewidth/2, paneheight/2);

	Viewport subview(vp, trans);
	subview.render(Quad(Color::YELLOW, -5, -5, 10, 10));
}

bool GameView::gotEvent(const InputEvent &event) {
	if ((event.getType() == InputEvent::CLICK_SINGLE || event.getType() == InputEvent::CLICK_DRAG) && event.getButton() == mousebtns::left) {
		float mvecx = event.getMouseX() - panewidth/2;
		float mvecy = event.getMouseY() - paneheight/2;
		float angle = atan2(mvecy, mvecx);
	
		if (!event.isKeyHeld(keycodes::lshift))
		 	lightangle = angle;
		else 
			spriteangle = angle-90;
		
		return true;
	} else if (event.getType() == InputEvent::KEY_PRESSED || event.getType() == InputEvent::KEY_RELEASED) {
		if (event.getKey() == '\t') {
			if (event.getType() == InputEvent::KEY_PRESSED) {
				rendertype++;
				if (rendertype >= MAX_RENDERTYPE)
					rendertype = 0;
			}
		
			return true;
		} else if (event.getKey() == 'c') {
			if (event.getType() == InputEvent::KEY_PRESSED) {
				smoothcolor = !smoothcolor;
			}
			
			return true;
		} else if (event.getKey() == 'n') {
			if (event.getType() == InputEvent::KEY_PRESSED) {
				smoothnormal = !smoothnormal;
			}
			
			return true;
		}		
	}

	return SpriteViewBase::handleEvent(event);
}

string GameView::getTitle() { return "Game view"; }
