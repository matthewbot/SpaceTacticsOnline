#ifndef STO_SHARED_THRUSTERCOMPONENTBUILDER_H
#define STO_SHARED_THRUSTERCOMPONENTBUILDER_H

#include "ThrusterStats.h"
#include <STO/shared/entitybuilder/EntityComponentBuilder.h>
#include <string>

namespace sto {
	class ThrusterComponentBuilder : public EntityComponentBuilder {
		public:
			ThrusterComponentBuilder(const std::string &name, const std::string &motname, const std::string &tickname, const ThrusterStats &stats);
			virtual ~ThrusterComponentBuilder();
			
			virtual NamedComponent makeComponent(const ComponentMap &components, const ComponentSystemMap &compsystems);
			
		private:
			std::string name;
			std::string motname;
			std::string tickname;
			ThrusterStats stats;
	};
}

#endif
