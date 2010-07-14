#ifndef STO_CLIENT_RENDERCOMPONENTSYSTEM_H
#define STO_CLIENT_RENDERCOMPONENTSYSTEM_H

#include <STO/shared/entity/EntityComponentSystemBase.h>
#include <MGE/gfx/Viewport.h>
#include <boost/shared_ptr.hpp>

namespace mge {
	class Sprite;
}


namespace sto {
	class RenderableComponent;
	class PlayerEntityHolder;

	class RenderComponentSystem : public EntityComponentSystemBase<RenderableComponent> {
		public:
			RenderComponentSystem(const mge::Viewport &viewp, const PlayerEntityHolder &player, const boost::shared_ptr<mge::Sprite> &bgsprite);
			virtual ~RenderComponentSystem();
			
			inline mge::Viewport &getViewport() { return viewp; }
			
			inline const mge::Viewport &getView() const { return viewp; }
			inline mge::Viewport &getView() { return viewp; }
			
			virtual void update();
			
		protected:
			virtual void updateComponent(const boost::shared_ptr<RenderableComponent> &comp);
			
		private:
			mge::Viewport makeSubview() const;
		
			mge::Viewport viewp;
			const PlayerEntityHolder &player; // not ideal, but can't find a cleaner solution. EntityComponent update loop forces this system to grab rather than be given the position of the player
			float lightdir; // current lighting direction, for RenderableComponents that need it
			boost::shared_ptr<mge::Sprite> bgsprite;
	};
}

#endif
