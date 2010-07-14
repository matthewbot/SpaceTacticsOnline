#include "ServerGameState.h"
#include <MGE/state/GameStateStatus.h>
#include <MGE/net/NetworkSystem.h>

using namespace sto;
using namespace mge;

ServerGameState::ServerGameState(const ServerStateSystems &systems) 
: systems(systems), players(), connections(players, systems.net) { 
	systems.net->start(8723, 20, 0, 0, 30);
}

GameStateStatus ServerGameState::update() { 
	connections.update();
	
	return GameStateStatus::CONTINUE;
} 
