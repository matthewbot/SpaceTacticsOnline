#include "LightSprite.h"
#include <MGE/gfx/RenderState.h>
#include <MGE/gfx/Viewport.h>
#include <MGE/gfx/texture/Texture.h>
#include <MGE/gfx/primitive/MultiTexQuad.h>
#include <MGE/res/Shader.h>
#include <cmath>

using namespace sto;
using namespace mge;
using namespace boost;
using namespace std;

LightSprite::LightSprite(const string &name, const LightSpriteProps &props, const shared_ptr<Texture> &color, const shared_ptr<Texture> &normal, const shared_ptr<Shader> &shader)
: Resource(name), props(props), color(color), normal(normal), shader(shader) { }
LightSprite::~LightSprite() { }

void LightSprite::renderRotated(const Viewport &view, float x, float y, float rot, float lightdir) {
	MultiTexQuad<2> tquad(Color::WHITE, -props.ox, -props.oy, props.tw, props.th);
	tquad[0].texes[0].set(props.tx, props.ty); 
	tquad[1].texes[0].set(props.tx+props.tw, props.ty);
	tquad[2].texes[0].set(props.tx+props.tw, props.ty+props.th);
	tquad[3].texes[0].set(props.tx, props.ty+props.th);
	tquad.cloneTexes(0, 1);
	
	RenderState state; 
	state.program(shader->getProgram());
	state.programVar("lightvec", ShaderVariableValue(cos(lightdir), sin(lightdir)));
	state.texture(color, 0);
	state.texture(normal, 1);
	
	Transform trans;
	trans.rotate(rot + props.rotoffset).translate(x, y);
	
	view.render(state, trans, tquad);
}
