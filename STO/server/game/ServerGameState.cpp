#include "ServerGameState.h"
#include <STO/shared/tick/TickComponentSystem.h>
#include <MGE/util/FrameRateLimiter.h>
#include <MGE/state/GameStateStatus.h>
#include <MGE/net/NetworkSystem.h>

using namespace sto;
using namespace mge;
using namespace boost;

ServerGameState::ServerGameState(const ServerStateSystems &systems) 
: systems(systems), players(), connections(players, systems.net, systems.log) {
	players.newTeam("Red", Color::RED);
	players.newTeam("Blue", Color::BLUE);
	
	entities.addSystem("motion", shared_ptr<EntityComponentSystem>(new TickComponentSystem(*systems.fps)));

	systems.net->start(8723, 20, 0, 0, 30);
}

GameStateStatus ServerGameState::update() {
	connections.update();
	entities.update();
	
	return GameStateStatus::CONTINUE;
} 
