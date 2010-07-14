#include "STOEditSystem.h"
#include "EditController.h"
#include <STOEdit/sprite/SpriteController.h>
#include <STOEdit/core/PaneLayout.h>
#include <MGE/gfx/system/GraphicsSystem.h>
#include <MGE/gfx/Viewport.h>
#include <MGE/res/system/ResourceSystem.h>
#include <MGE/res/Font.h>
#include <MGE/res/Shader.h>
#include <sstream>

using namespace mge;
using namespace stoedit;
using namespace boost;
using namespace std;

STOEditSystem::STOEditSystem(GraphicsSystem &gfx, ResourceSystem &res) 
: gfx(gfx), res(res), 
  workspace(gfx.getDisplay().getWidth(), gfx.getDisplay().getHeight()), // create workspace from displays width and height
  fpsoverlay(res.get<Font>("fnt_titles"))
{ 
	gfx.getWindowInput().addInputListener(eventprod); // register InputEventProducer with the graphic system's window input

  workspace.getProps().frame.titlefont = res.get<Font>("fnt_titles"); // load the resources needed by the workspace
	setStandardWorkSpaceLayout(3);
  
  eventprod.addListener(fpsoverlay); // register the FPS overlay with the event producer
  eventprod.addListener(workspace); // register workspace with the event producer

	// TODO: Seperate this into a factory system
	SpriteController *sprcon = new SpriteController(gfx.getTextureManager(), workspace); // create the spritemodel
	sprcon->getRes().gameshader = res.get<Shader>("shd_game"); // Load its resources
	sprcon->getRes().valuefont = res.get<Font>("fnt_value"); 
	sprcon->getRes().dialogfont = res.get<Font>("fnt_titles");
	
	setController(sprcon);
}

void STOEditSystem::setController(EditController *newcon) {
	if (controller.get()) {
		eventprod.removeListener(*controller);
	}

	controller = auto_ptr<EditController>(newcon);
	eventprod.addListener(*controller);
}

STOEditSystem::~STOEditSystem() {
	gfx.getWindowInput().removeInputListener(eventprod);
	eventprod.removeListener(workspace);
}

void STOEditSystem::setStandardWorkSpaceLayout(int sidecount) {
	Display &disp = gfx.getDisplay();
	PaneLayout layout; 
	
	int horizdivide = (int)(disp.getWidth()*.75f);
	int sideheight = disp.getHeight()/sidecount;
	
	layout.append(0, 0, horizdivide, disp.getHeight());
	for (int y=0; y < disp.getHeight(); y += sideheight) {
		layout.append(horizdivide, y, disp.getWidth()-horizdivide, sideheight);
	}
	
	workspace.getPanes().setLayout(layout);
}

SystemUpdateValue STOEditSystem::update() {
	eventprod.update(gfx.getTimer().getTDelta());

	Display &disp = gfx.getDisplay();
	Viewport view(disp);
	
	disp.clear();
	workspace.render(view);
	fpsoverlay.render(view, gfx);

	if (eventprod.getExit())
		return STOP;
	else
		return NONE;
}

const char *STOEditSystem::getName() const { return "STOEditSystem"; }
