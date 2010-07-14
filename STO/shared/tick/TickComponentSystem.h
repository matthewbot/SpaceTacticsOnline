#ifndef STO_SHARED_TICKCOMPONENTSYSTEM_H
#define STO_SHARED_TICKCOMPONENTSYSTEM_H

#include <STO/shared/entity/EntityComponentSystemBase.h>
#include <MGE/util/FPSTimer.h>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <list>

namespace sto {
	class TickableComponent;

	class TickComponentSystem : public EntityComponentSystemBase<TickableComponent> {
		public:
			TickComponentSystem(const mge::FPSTimer &timer);
			
		protected:
			virtual void updateComponent(const boost::shared_ptr<TickableComponent> &comp);
			
		private:
			const mge::FPSTimer &timer;
	};
}

#endif
