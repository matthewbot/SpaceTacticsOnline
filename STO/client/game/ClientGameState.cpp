#include "ClientGameState.h"
#include <STO/shared/entitybuilder/EntityBuilder.h>
#include <STO/shared/tick/TickComponentSystem.h>
#include <STO/client/render/RenderComponentSystem.h>
#include <STO/shared/input/FlightInput.h>
#include <STO/shared/input/FlightInputComponent.h>
#include <STO/shared/position/PositionComponent.h>
#include <MGE/state/GameStateStatus.h>
#include <MGE/gfx/system/GraphicsSystem.h>
#include <MGE/gfx/Viewport.h>
#include <MGE/res/system/ResourceSystem.h>
#include <MGE/res/Font.h>
#include <MGE/res/Sprite.h>
#include <MGE/net/NetworkSystem.h>
#include <MGE/util/Logger.h>
#include <cmath>
#include <sstream>

using namespace sto;
using namespace boost;
using namespace mge;
using namespace std;

ClientGameState::ClientGameState(const ClientStateSystems &systems) : systems(systems), serverconn(*this) {
	systems.gfx->getWindowInput().addInputListener(input);
	
	Viewport vp(systems.gfx->getDisplay());
	rendersys = shared_ptr<RenderComponentSystem>(new RenderComponentSystem(vp, player, systems.res->get<Sprite>("spr_bg")));
	entities.addSystem("ships", rendersys);

	entities.addSystem("motion", shared_ptr<EntityComponentSystem>(new TickComponentSystem(systems.gfx->getTimer())));
	
	player.makePlayer(*systems.res->get<EntityBuilder>("ent_scout"), entities);
	
	debugfont = systems.res->get<Font>("fnt_debug");
	
	systems.net->start(-1, 1, 0, 0, 32);
	serverconn.connect(systems.net->connect("localhost", 8723), "matthewbot");
}

ClientGameState::~ClientGameState() {
	systems.gfx->getWindowInput().removeInputListener(input);
}

GameStateStatus ClientGameState::update() {
	serverconn.update();

	FlightInput finput = getInput();	
	player.getInput()->gotInput(finput);
	//serverconn.sendFlightInput(finput);
	
	Display &disp = systems.gfx->getDisplay();
	disp.clear();
	
	entities.update();
	
	{
		stringstream buf;
		buf << "FPS: " << systems.gfx->getTimer().getFPS() << " ";
		buf << systems.gfx->getStats() << " ";
		buf << "State: " << ServerConnection::stateToString(serverconn.getState());
		
		debugfont->render(disp, 0, disp.getHeight()-debugfont->getLineHeight(), buf.str());
	}

	if (!input.getExit())
		return GameStateStatus::CONTINUE;
	else
		return GameStateStatus::TERMINATE;
}

FlightInput ClientGameState::getInput() {
	Display &disp = systems.gfx->getDisplay();

	FlightInput finput;
	finput.mousedir = atan2(input.getMouseY() - disp.getHeight()/2, input.getMouseX() - disp.getWidth()/2);
	
	if (input.isKeyDown('s'))
		finput.speed = ThrusterStats::ACCEL;
	else if (input.isKeyDown('x'))
		finput.speed = ThrusterStats::BRAKE;
	else
		finput.speed = ThrusterStats::CRUISE;
		
	return finput;
}

void ClientGameState::onConnect() {
	systems.log->log("main", INFO) << "Connected to server" << endl;
}

void ClientGameState::onError(BaseConnection *conn, const string &error) {
	systems.log->log("main", INFO) << "Connection error: " << error << endl;
}

void ClientGameState::onDisconnect(BaseConnection *conn) {
	systems.log->log("main", INFO) << "Disconnected from server" << endl;
}

void ClientGameState::onCreateEntity(int id, const string &name, const Blob &data) {
	std::pair<Entity *, ComponentMap> result = systems.res->get<EntityBuilder>(name)->makeEntity(entities.getSystemMap());
	
	shared_ptr<SerializeComponent> serial = lookup_ptr<SerializeComponent>("serial_main", result.second);
	
	Blob data_copy = data;
	serial->deserialize(data_copy, true);
	
	entities.addEntity(result.first);
	serialize_entities.insert(make_pair(id, serial));
}

void ClientGameState::onUpdateEntity(int id, const mge::Blob &data, bool isfull) {
	SerializeEntityMap::const_iterator i = serialize_entities.find(id);
	
	boost::shared_ptr<SerializeComponent> serial = i->second.lock();
	
	Blob data_copy = data;
	serial->deserialize(data_copy, isfull);
}

void ClientGameState::onPlayerJoined(int id, int teamid, const std::string &username) {
	players.newPlayer(id, username, players.getTeamById(teamid));
}

void ClientGameState::onPlayerLeft(int id) {
	players.removePlayer(players.getPlayerById(id));
}

