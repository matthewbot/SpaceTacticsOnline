#include "SpriteComponent.h"
#include "SpriteWrapper.h"
#include <MGE/res/Sprite.h>

using namespace sto;
using namespace mge;
using namespace boost;

SpriteComponent::SpriteComponent(const boost::shared_ptr<SpriteWrapper> &sprite, PositionComponent &pos)
: sprite(sprite), pos(pos) { }
SpriteComponent::~SpriteComponent() { }

void SpriteComponent::render(const mge::Viewport &view, float lightdir) {
	sprite->renderRotated(view, pos.getX(), pos.getY(), pos.getRotation(), lightdir);
}
