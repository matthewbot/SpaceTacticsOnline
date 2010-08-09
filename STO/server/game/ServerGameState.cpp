#include "ServerGameState.h"
#include <STO/shared/tick/TickComponentSystem.h>
#include <STO/shared/entitybuilder/EntityBuilder.h>
#include <STO/shared/input/FlightInput.h>
#include <STO/shared/input/FlightInputComponent.h>
#include <STO/shared/serial/SerializeComponent.h>
#include <MGE/util/FrameRateLimiter.h>
#include <MGE/util/Blob.h>
#include <MGE/state/GameStateStatus.h>
#include <MGE/net/NetworkSystem.h>
#include <MGE/res/system/ResourceSystem.h>

using namespace sto;
using namespace mge;
using namespace boost;
using namespace std;

ServerGameState::ServerGameState(const ServerStateSystems &systems) 
: systems(systems), players(*this), connections(players, systems.net, systems.log), nextid(1) {
	players.newTeam(1, "Red", Color::RED);
	players.newTeam(2, "Blue", Color::BLUE);
	
	entities.addSystem("motion", shared_ptr<EntityComponentSystem>(new TickComponentSystem(*systems.fps)));

	systems.net->start(8723, 20, 0, 0, 30);
}

void ServerGameState::spawnPlayerEntity(const string &entityname, const boost::shared_ptr<Player> &player) {
	shared_ptr<EntityBuilder> builder = systems.res->get<EntityBuilder>(entityname);
	std::pair<Entity *, ComponentMap> result = builder->makeEntity(entities.getSystemMap());
	
	ComponentMap &components = result.second;
	shared_ptr<SerializeComponent> serialcomp = lookup_ptr<SerializeComponent>("serial_main", components);
	shared_ptr<FlightInputComponent> flightcomp = lookup_ptr<FlightInputComponent>("input_main", components);
	
	int id = nextid++;
	serialize_entities.insert(make_pair(id, serialcomp));
	flightinput_entities.insert(make_pair(player->getID(), flightcomp));
	entities.addEntity(result.first);
	
	Blob update;
	serialcomp->serialize(update, true);
	update.flip();
	connections.broadcastEntityCreate(id, entityname, update);
}

void ServerGameState::playerJoined(const boost::shared_ptr<Player> &player) {
	spawnPlayerEntity("ent_scout", player);
}

void ServerGameState::playerLeft(const boost::shared_ptr<Player> &player) {

}

GameStateStatus ServerGameState::update() {
	connections.update();
	entities.update();
	
	return GameStateStatus::CONTINUE;
} 


