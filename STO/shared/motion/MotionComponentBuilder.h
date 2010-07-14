#ifndef STO_SHARED_MOTIONCOMPONENTBUILDER_H
#define STO_SHARED_MOTIONCOMPONENTBUILDER_H

#include <STO/shared/entitybuilder/EntityComponentBuilder.h>
#include <string>

namespace sto {
	class MotionComponentBuilder : public EntityComponentBuilder {
		public:
			MotionComponentBuilder(const std::string &name, const std::string &posname, const std::string &tickname, float hs=0, float vs=0, float rots=0);
			virtual ~MotionComponentBuilder();
			
			virtual NamedComponent makeComponent(const ComponentMap &components, const ComponentSystemMap &compsystems);
			
		private:
			std::string name;
			std::string posname;
			std::string tickname;
			float hs, vs, rots;
	};
}

#endif
