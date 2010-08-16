#ifndef STO_SHARED_FLIGHTINPUTCOMPONENTBUILDER_H
#define STO_SHARED_FLIGHTINPUTCOMPONENTBUILDER_H

#include <STO/shared/entitybuilder/EntityComponentBuilder.h>
#include <string>

namespace sto {
	class FlightInputComponentBuilder : public EntityComponentBuilder {
		public:
			FlightInputComponentBuilder(const std::string &name, const std::string &thrustname, const std::string &centerposname);
			~FlightInputComponentBuilder();
			
			virtual NamedComponent makeComponent(const ComponentMap &components, const ComponentSystemMap &compsystems);
			
		private:
			std::string name;
			std::string thrustname;
			std::string centerposname;
	
	};
}

#endif
