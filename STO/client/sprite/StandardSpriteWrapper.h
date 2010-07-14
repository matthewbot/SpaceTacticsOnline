#ifndef STO_CLIENT_STANDARDSPRITEWRAPPER_H
#define STO_CLIENT_STANDARDSPRITEWRAPPER_H

#include "SpriteWrapper.h"
#include <boost/shared_ptr.hpp>

namespace mge {
	class Sprite;
}

namespace sto {
	class StandardSpriteWrapper : public SpriteWrapper {
		public:
			StandardSpriteWrapper(const boost::shared_ptr<mge::Sprite> &spr);
			virtual ~StandardSpriteWrapper();
			
			virtual void renderRotated(const mge::Viewport &view, float x, float y, float rot, float lightdir);
			
		private:
			boost::shared_ptr<mge::Sprite> spr;
	};
}

#endif
