#include "PaneFrameRenderer.h"
#include <MGE/gfx/primitive/Quad.h>
#include <MGE/gfx/Viewport.h>
#include <MGE/gfx/ViewSection.h>
#include <MGE/res/Font.h>
#include <cassert>

using namespace stoedit;
using namespace mge;
using namespace std;

PaneFrameRenderer::PaneFrameRenderer(const FrameRenderProps &props) : props(props) { }
PaneFrameRenderer::~PaneFrameRenderer() { }

ViewSection PaneFrameRenderer::getSubsection(int panewidth, int paneheight) {
	int lheight = props.titlefont->getLineHeight();
	int bsize = props.bordersize;
	
	ViewSection sect = { props.bordersize, props.bordersize, panewidth-bsize*2, paneheight-bsize*2-lheight };
	return sect;
}

void PaneFrameRenderer::renderFrame(Viewport &rootvp, int panewidth, int paneheight, const string &title, bool selected) {
	drawBorders(rootvp, panewidth, paneheight);
	drawTitleBar(rootvp, panewidth, paneheight, title, selected);
}

void PaneFrameRenderer::drawBorders(Viewport &vp, int width, int height) {
	drawQuadRect(vp, props.bordercolor, 0, 0, width, height, props.bordersize);
}

int PaneFrameRenderer::drawTitleBar(mge::Viewport &vp, int width, int height, const std::string &title, bool selected) {
	int lheight = props.titlefont->getLineHeight();
	int bsize = props.bordersize;
	Color col = selected ? props.seltitlecolor : props.titlecolor;
	int ypos = height - props.bordersize;
	
	Quad titlequad(col, props.bordersize, ypos, width - bsize*2, -lheight); // draw in the upper part of the pane not covered by the border
	vp.render(titlequad);
	
	props.titlefont->render(vp, bsize + 1, ypos-props.titlefont->getLineHeight(), title); // draw the font on top of the quad
	
	return lheight;
}

void PaneFrameRenderer::drawQuadRect(Viewport &vp, const mge::Color &color, float x, float y, float w, float h, float thickness) {
	vp.render(Quad(color, x, y, thickness, h));
	vp.render(Quad(color, x, y+h, x+w, -thickness));
	vp.render(Quad(color, x+w, y+h, -thickness, -h));
	vp.render(Quad(color, x+w, y, -w, thickness));
}
