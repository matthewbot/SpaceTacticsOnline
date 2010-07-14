#ifndef STO_SHARED_DESTROYCOMPONENT_H
#define STO_SHARED_DESTROYCOMPONENT_H

#include "EntityComponent.h"
#include "Entity.h"

namespace sto {
	class DestroyComponent : public EntityComponent {
		public:
			DestroyComponent(Entity &entity);
			virtual ~DestroyComponent();
			
			inline void flagDestroy() { entity.setDestroyFlag(); }
			inline bool isFlagged() const { return entity.getDestroyFlag(); }
			
		private:
			Entity &entity;
	};
}

#endif
