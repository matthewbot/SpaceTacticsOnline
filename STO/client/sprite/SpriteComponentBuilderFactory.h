#ifndef STO_CLIENT_SPRITECOMPONENTBUILDER_H
#define STO_CLIENT_SPRITECOMPONENTBUILDER_H

#include <STO/shared/entitybuilder/EntityComponentBuilderFactory.h>

namespace mge {
	class ResourceSystem;
}

namespace sto {
	class SpriteComponentBuilderFactory : public EntityComponentBuilderFactory {
		public:
			SpriteComponentBuilderFactory();
			virtual ~SpriteComponentBuilderFactory();
			
			virtual EntityComponentBuilder *makeComponentBuilder(const std::string &name, const mge::ResourceNode &node, const mge::ResourceSystem &res);
	};
}

#endif
