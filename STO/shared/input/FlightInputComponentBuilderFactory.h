#ifndef STO_SHARED_FLIGHTINPUTCOMPONENTBUILDERFACTORY_H
#define STO_SHARED_FLIGHTINPUTCOMPONENTBUILDERFACTORY_H

#include <STO/shared/entitybuilder/EntityComponentBuilderFactory.h>

namespace sto {
	class FlightInputComponentBuilderFactory : public EntityComponentBuilderFactory {
		public:
			FlightInputComponentBuilderFactory();
			~FlightInputComponentBuilderFactory();
			
			virtual EntityComponentBuilder *makeComponentBuilder(const std::string &name, const mge::ResourceNode &node, const mge::ResourceSystem &res);
	};
}

#endif
