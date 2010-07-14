#include "PlayerEntityHolder.h"
#include <STO/shared/entitybuilder/EntityBuilder.h>
#include <STO/shared/position/PositionComponent.h>
#include <STO/shared/input/FlightInput.h>
#include <STO/shared/input/FlightInputComponent.h>
#include <STO/shared/serial/SerializeComponent.h>

using namespace sto;

PlayerEntityHolder::PlayerEntityHolder() { }
PlayerEntityHolder::~PlayerEntityHolder() { }

void PlayerEntityHolder::makePlayer(const EntityBuilder &builder, EntityContainer &cont) {
	std::pair<Entity *, ComponentMap> result = builder.makeEntity(cont.getSystemMap());
	ComponentMap &components = result.second;
	
	pos = lookup_ptr<PositionComponent>("pos_main", components);
	input = lookup_ptr<FlightInputComponent>("input_main", components);
	serial = lookup_ptr<SerializeComponent>("serial_main", components);
	
	cont.addEntity(result.first);
}
