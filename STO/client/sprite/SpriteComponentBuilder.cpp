#include "SpriteComponentBuilder.h"
#include "SpriteComponent.h"
#include "StandardSpriteWrapper.h"
#include "LightSprite.h"
#include <STO/client/render/RenderComponentSystem.h>
#include <STO/shared/position/PositionComponent.h>
#include <MGE/util/Exception.h>
#include <MGE/res/system/ResourceSystem.h>
#include <MGE/res/Sprite.h>

using namespace sto;
using namespace mge;
using namespace boost;
using namespace std;

SpriteComponentBuilder::SpriteComponentBuilder(const string &name, const ResourceSystem &ressys, const string &spritename, SpriteType spritetype, const string &posname, const string &rendersystemname) 
: name(name), ressys(ressys), spritename(spritename), spritetype(spritetype), posname(posname), rendersystemname(rendersystemname) { }

NamedComponent SpriteComponentBuilder::makeComponent(const ComponentMap &components, const ComponentSystemMap &compsystems) {
	PositionComponent &pos = lookup_ref<PositionComponent>(posname, components);
	shared_ptr<SpriteWrapper> spritewrap;
	
	if (spritetype == STANDARD) {
		shared_ptr<Sprite> sprite = ressys.get<Sprite>(spritename);
		spritewrap = shared_ptr<SpriteWrapper>(new StandardSpriteWrapper(sprite));
	} else if (spritetype == LIGHT) {
		spritewrap = static_pointer_cast<SpriteWrapper>(ressys.get<LightSprite>(spritename));
	} else
		throw Exception("Bad spritetype?");
	
	shared_ptr<SpriteComponent> spritecomp(new SpriteComponent(spritewrap, pos));

	RenderComponentSystem &rendersys = lookup_ref<RenderComponentSystem>(rendersystemname, compsystems); // TODO function for this
	rendersys.registerComponent(spritecomp);
	
	return make_pair(name, spritecomp);
}
