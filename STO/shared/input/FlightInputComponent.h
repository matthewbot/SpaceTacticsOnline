#ifndef STO_CLIENT_FLIGHTINPUTCOMPONENT_H
#define STO_CLIENT_FLIGHTINPUTCOMPONENT_H

#include <STO/shared/entity/EntityComponent.h>

namespace sto {
	class ThrusterComponent;
	class FlightInput;

	class FlightInputComponent : public EntityComponent {
		public:
			FlightInputComponent(ThrusterComponent &thrust); // will need references to guns and the like
			~FlightInputComponent();
			
			void gotInput(const FlightInput &input);
			
		private:
			ThrusterComponent &thrust;
	};
}

#endif
