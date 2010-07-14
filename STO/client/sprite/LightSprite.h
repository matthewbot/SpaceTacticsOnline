#ifndef STO_CLIENT_LIGHTSPRITE_H
#define STO_CLIENT_LIGHTSPRITE_H

#include "SpriteWrapper.h"
#include <boost/shared_ptr.hpp>
#include <MGE/res/Resource.h>

namespace mge {
	class Texture;
	class Viewport;
	class Shader;
}

namespace sto {
	struct LightSpriteProps {
		float tx, ty, tw, th;
		float ox, oy;
		float rotoffset;
	};

	class LightSprite : public mge::Resource, public SpriteWrapper {
		public:
			LightSprite(const std::string &name, const LightSpriteProps &props, const boost::shared_ptr<mge::Texture> &color, const boost::shared_ptr<mge::Texture> &normal, const boost::shared_ptr<mge::Shader> &shader);
			virtual ~LightSprite();
			
			void render(const mge::Viewport &view, float x, float y, float lightdir);
			virtual void renderRotated(const mge::Viewport &view, float x, float y, float rot, float lightdir);
		
		private:
			LightSpriteProps props;
			boost::shared_ptr<mge::Texture> color, normal;
			boost::shared_ptr<mge::Shader> shader;
	};
}

#endif
