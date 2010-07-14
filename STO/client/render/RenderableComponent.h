#ifndef STO_CLIENT_RENDERABLECOMPONENT_H
#define STO_CLIENT_RENDERABLECOMPONENT_H

namespace mge {
	class Viewport;
}

namespace sto {
	class RenderableComponent {
		public:
			inline virtual ~RenderableComponent() { }
			
			virtual void render(const mge::Viewport &view, float lightdir)=0;
	};
}

#endif
