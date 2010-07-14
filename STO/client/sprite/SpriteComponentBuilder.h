#ifndef STO_CLIENT_SPRITE_SPRITECOMPONENTBUILDER_H
#define STO_CLIENT_SPRITE_SPRITECOMPONENTBUILDER_H

#include <STO/shared/entitybuilder/EntityComponentBuilder.h>
#include <string>

namespace mge {
	class ResourceSystem;
}

namespace sto {
	class SpriteComponentBuilder : public EntityComponentBuilder {
		public:
			enum SpriteType {
				STANDARD,
				LIGHT
			};
		
			SpriteComponentBuilder(const std::string &name, const mge::ResourceSystem &ressys, const std::string &spritename, SpriteType spritetype, const std::string &posname, const std::string &rendersystemname);
			
			virtual NamedComponent makeComponent(const ComponentMap &components, const ComponentSystemMap &compsystems);
			
		private:
			std::string name;
			const mge::ResourceSystem &ressys;
			std::string spritename; 
			SpriteType spritetype;
			std::string posname;
			std::string rendersystemname;
	};
}

#endif
