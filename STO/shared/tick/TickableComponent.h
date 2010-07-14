#ifndef STO_SHARED_TICKABLECOMPONENT_H
#define STO_SHARED_TICKABLECOMPONENT_H

namespace sto {
	class TickableComponent {
		public:
			inline virtual ~TickableComponent() { }
			
			virtual void tick(float tdelta) = 0;
	};
}

#endif
