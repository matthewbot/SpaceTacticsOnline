#ifndef STO_CLIENT_SPRITECOMPONENT_H
#define STO_CLIENT_SPRITECOMPONENT_H

#include <STO/client/render/RenderableComponent.h>
#include <STO/shared/position/PositionComponent.h>
#include <STO/shared/entity/EntityComponent.h>
#include <boost/shared_ptr.hpp>

namespace mge {
	class Sprite;
}

namespace sto {
	class SpriteWrapper;

	class SpriteComponent : public RenderableComponent, public EntityComponent {
		public:
			SpriteComponent(const boost::shared_ptr<SpriteWrapper> &sprite, PositionComponent &pos);
			virtual ~SpriteComponent();
			
			virtual void render(const mge::Viewport &view, float lightdir);
			
		private:
			boost::shared_ptr<SpriteWrapper> sprite;
			PositionComponent &pos;
	};
}

#endif
