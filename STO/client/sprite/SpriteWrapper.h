#ifndef STO_CLIENT_SPRITEWRAPPER_H
#define STO_CLIENT_SPRITEWRAPPER_H

namespace mge {
	class Viewport;
}

namespace sto {
	class SpriteWrapper {
		public:
			inline virtual ~SpriteWrapper() { }
			
			virtual void renderRotated(const mge::Viewport &view, float x, float y, float rot, float lightdir)=0;
	};
}

#endif
