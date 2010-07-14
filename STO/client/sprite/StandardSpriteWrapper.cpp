#include "StandardSpriteWrapper.h"
#include <MGE/res/Sprite.h>

using namespace sto;
using namespace mge;
using namespace boost;

StandardSpriteWrapper::StandardSpriteWrapper(const shared_ptr<Sprite> &spr) : spr(spr) { }
StandardSpriteWrapper::~StandardSpriteWrapper() { }

void StandardSpriteWrapper::renderRotated(const Viewport &view, float x, float y, float rot, float lightdir) {
	spr->renderRotated(view, x, y, rot);
}

