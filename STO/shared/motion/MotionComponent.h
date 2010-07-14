#ifndef STO_SHARED_MOTIONCOMPONENT_H
#define STO_SHARED_MOTIONCOMPONENT_H

#include <STO/shared/entity/EntityComponent.h>
#include <STO/shared/tick/TickableComponent.h>
#include <STO/shared/serial/SerializableComponent.h>
#include <MGE/util/Vector2D.h>

namespace sto {
	class PositionComponent;

	class MotionComponent : public EntityComponent, public TickableComponent, public SerializableComponent {
		public:
			MotionComponent(PositionComponent &pos);
			MotionComponent(PositionComponent &pos, float hs, float vs, float rotspeed=0);
			MotionComponent(PositionComponent &pos, const mge::Vector2D &motion, float rotspeed=0);
			virtual ~MotionComponent();
			
			inline const mge::Vector2D &getMotion() const { return motion; }
			inline float getSpeed() const { return motion.getMagnitude(); }
			inline float getHSpeed() const { return motion.getX(); }
			inline float getVSpeed() const { return motion.getY(); }
			inline float getRotSpeed() const { return rotspeed; }
			PositionComponent &getPositionComponent() { return pos; }
			const PositionComponent &getPositionComponent() const { return pos; }
			
			void setMotion(const mge::Vector2D &motion);
			inline void setHSpeed(float hspeed) { motion.setX(hspeed); }
			inline void setVSpeed(float vspeed) { motion.setY(vspeed); }
			inline void setRotSpeed(float rotspeed) { this->rotspeed = rotspeed; }
			
			virtual void tick(float tdelta);
		
		protected:
			virtual void visitData(DataVisitor &visit);
		
		private:
			PositionComponent &pos;
			mge::Vector2D motion;
			float rotspeed;
	};
}


#endif
