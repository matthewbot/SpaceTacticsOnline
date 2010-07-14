#include "RenderComponentSystem.h"
#include "RenderableComponent.h"
#include <STO/client/game/PlayerEntityHolder.h>
#include <STO/shared/position/PositionComponent.h>
#include <MGE/res/Sprite.h>
#include <MGE/gfx/RenderRoot.h>
#include <MGE/gfx/Transform.h>
#include <MGE/gfx/primitive/Quad.h>
#include <cmath>

using namespace sto;
using namespace mge;

RenderComponentSystem::RenderComponentSystem(const Viewport &viewp, const PlayerEntityHolder &player, const boost::shared_ptr<mge::Sprite> &bgsprite)
: viewp(viewp), player(player), lightdir(0.2f), bgsprite(bgsprite) { }
RenderComponentSystem::~RenderComponentSystem() { }

static int roundDown(int x, int amt) {
	int ret = x/amt*amt;
	if (x < 0)
		ret -= amt;
	return ret;
}

void RenderComponentSystem::update() {
	const RenderRoot &root = viewp.getRoot();
	int x = (int)(player.getPosition()->getX() - root.getWidth()/2);
	int y = (int)(player.getPosition()->getY() - root.getHeight()/2);
	x = roundDown(x, bgsprite->getWidth());
	y = roundDown(y, bgsprite->getHeight());
	
	Viewport view = makeSubview();
	bgsprite->renderTiled(view, x, y, 2, 2);
	

	EntityComponentSystemBase<RenderableComponent>::update();
}

void RenderComponentSystem::updateComponent(const boost::shared_ptr<RenderableComponent> &comp) {
	comp->render(makeSubview(), lightdir);
}


Viewport RenderComponentSystem::makeSubview() const {
	const RenderRoot &root = viewp.getRoot();
	Viewport subview(viewp);
	
	subview.getTransform().translate(-player.getPosition()->getX() + root.getWidth()/2, -player.getPosition()->getY() + root.getHeight()/2);
	
	return subview;
}
