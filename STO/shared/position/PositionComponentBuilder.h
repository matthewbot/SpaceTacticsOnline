#ifndef STO_SHARED_POSITIONCOMPONENTBUILDER_H
#define STO_SHARED_POSITIONCOMPONENTBUILDER_H

#include <STO/shared/entitybuilder/EntityComponentBuilder.h>
#include <string>

namespace sto {
	class PositionComponentBuilder : public EntityComponentBuilder {
		public:
			PositionComponentBuilder(const std::string &name, const std::string &chainname, float x=0, float y=0, float dir=0);
			virtual ~PositionComponentBuilder();
			
			virtual NamedComponent makeComponent(const ComponentMap &components, const ComponentSystemMap &compsystems);
			
		private:
			std::string name;
			std::string chainname;
			float x, y, dir;
	};
}

#endif
