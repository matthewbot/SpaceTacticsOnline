#ifndef STO_SHARED_SERIALIZECOMPONENTBUILDER_H
#define STO_SHARED_SERIALIZECOMPONENTBUILDER_H

#include <STO/shared/entitybuilder/EntityComponentBuilder.h>
#include <string>
#include <vector>

namespace sto {
	class SerializeComponent;

	class SerializeComponentBuilder : public EntityComponentBuilder {
		public:
			SerializeComponentBuilder(const std::string &name);
			virtual ~SerializeComponentBuilder();
			
			void addComponentName(const std::string &name, bool full);
			
			virtual NamedComponent makeComponent(const ComponentMap &components, const ComponentSystemMap &compsystems);
		
		private:
			std::string name;
			
			typedef std::vector<std::string> ComponentNameList;
			ComponentNameList partialcomponentnames;
			ComponentNameList fullcomponentnames;
			
			void doRegister(SerializeComponent &sercomp, const ComponentMap &components, bool fullonly, const std::string &name);
	};
}

#endif
