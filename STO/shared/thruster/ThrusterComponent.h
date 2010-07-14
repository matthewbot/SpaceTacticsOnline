#ifndef STO_SHARED_THRUSTERCOMPONENT_H
#define STO_SHARED_THRUSTERCOMPONENT_H

#include "ThrusterStats.h"
#include <STO/shared/entity/EntityComponent.h>
#include <STO/shared/tick/TickableComponent.h>
#include <STO/shared/serial/SerializableComponent.h>

namespace sto {
	class MotionComponent;

	class ThrusterComponent : public EntityComponent, public TickableComponent, public SerializableComponent {
		public:
			ThrusterComponent(MotionComponent &mot, const ThrusterStats &stats);
			
			inline ThrusterStats &getStats() { return stats; }
			inline const ThrusterStats &getStats() const { return stats; }
			inline float getDestDir() const { return destdir; }
			
			inline void setDestDir(float destdir) { this->destdir = destdir; }
			inline void setSpeed(ThrusterStats::ThrustSpeed speed) { this->speed = speed; }
			
			virtual void tick(float tdelta);
			
		protected:
			virtual void visitData(DataVisitor &visit);
			
		private:
			void doRotation(float tdelta);
			void doSpeed(float tdelta);
			
		
			MotionComponent &mot;
			ThrusterStats stats;
			float destdir;
			ThrusterStats::ThrustSpeed speed;
	};
}

#endif
