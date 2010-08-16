#ifndef STO_CLIENT_FLIGHTINPUTCOMPONENT_H
#define STO_CLIENT_FLIGHTINPUTCOMPONENT_H

#include <STO/shared/entity/EntityComponent.h>

namespace sto {
	class ThrusterComponent;
	class PositionComponent;
	class FlightInput;

	class FlightInputComponent : public EntityComponent {
		public:
			FlightInputComponent(ThrusterComponent &thrust, const PositionComponent &centerpos); // will need references to guns and the like
			~FlightInputComponent();
			
			void gotInput(const FlightInput &input);
			const PositionComponent &getCenterPos() { return centerpos; }
			
		private:
			ThrusterComponent &thrust;
			const PositionComponent &centerpos;
	};
}

#endif
