#ifndef STO_SHARED_ENTITYCOMPONENTSYSTEM_H
#define STO_SHARED_ENTITYCOMPONENTSYSTEM_H

#include <boost/noncopyable.hpp>

namespace sto {
	class EntityComponentSystem : boost::noncopyable {
		public:
			inline virtual ~EntityComponentSystem() { }
			
			virtual void update() = 0;
	};
}

#endif
