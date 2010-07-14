#ifndef STO_CLIENT_PLAYERENTITYHOLDER_H
#define STO_CLIENT_PLAYERENTITYHOLDER_H

#include <STO/shared/entity/EntityContainer.h>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>

namespace sto {
	struct FlightInput;
	class PositionComponent;
	class FlightInputComponent;
	class SerializeComponent;
	class EntityBuilder;
	class Entity;

	class PlayerEntityHolder {
		public:
			PlayerEntityHolder();
			~PlayerEntityHolder();
		
			void makePlayer(const EntityBuilder &builder, EntityContainer &cont);
			
			inline boost::shared_ptr<PositionComponent> getPosition() const { return pos.lock(); }
			inline boost::shared_ptr<FlightInputComponent> getInput() const { return input.lock(); }
			inline boost::shared_ptr<SerializeComponent> getSerialize() const { return serial.lock(); }
		
		private:
			boost::weak_ptr<PositionComponent> pos;
			boost::weak_ptr<FlightInputComponent> input;
			boost::weak_ptr<SerializeComponent> serial;
	};
}

#endif
