#ifndef STO_SHARED_POSITIONCOMPONENT_H
#define STO_SHARED_POSITIONCOMPONENT_H

#include <STO/shared/entity/EntityComponent.h>
#include <STO/shared/serial/SerializableComponent.h>
#include <MGE/util/Vector2D.h>

namespace sto {
	class PositionComponent : public EntityComponent, public SerializableComponent {
		public:
			PositionComponent();
			PositionComponent(float x, float y, float rot, PositionComponent *parentpos);
			virtual ~PositionComponent();
			
			const mge::Vector2D getPosition() const;
			float getX() const;
			float getY() const;
			float getRotation() const;
			
			void setPosition(const mge::Vector2D &pos);
			inline void setX(float x) { pos.setX(x); }
			inline void setY(float y) { pos.setY(y); }
			void setRotation(float rot);
			
		protected:
			virtual void visitData(DataVisitor &visit);
			
		private:
			PositionComponent *parentpos;
			mge::Vector2D pos;
			float rot;
	};
}

#endif
