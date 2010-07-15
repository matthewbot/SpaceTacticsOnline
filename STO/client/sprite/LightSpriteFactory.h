#ifndef MGE_RES_LIGHTSPRITEFACTORY_H
#define MGE_RES_LIGHTSPRITEFACTORY_H

#include <MGE/res/system/ResourceFactory.h>

namespace mge {
	class TextureManager;
	class ResourceSystem;
}

namespace sto {
	class LightSpriteFactory : public mge::ResourceFactory {
		public:
			LightSpriteFactory(mge::ResourceSystem &res, mge::TextureManager &tm);
			virtual mge::Resource *makeResource(const std::string &name, const mge::ResourceNode &resnode);

		private:
			static std::string makeNormalName(const std::string &filename);
		
			mge::ResourceSystem &res;
			mge::TextureManager &texman;
	};
}

#endif
