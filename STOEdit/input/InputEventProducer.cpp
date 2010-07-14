#include "InputEventProducer.h"
#include "InputEventListener.h"
#include "InputEvent.h"
#include <cassert>
#include <cmath>
#include <algorithm>
#include <functional>

using namespace stoedit;
using namespace mge;
using namespace std;

namespace {
	static const float DOUBLECLICK_INTERVAL = 0.2f; // must double click faster than this
	static const int DOUBLECLICK_DIST = 3; // must double click closer to original point than this
	
	static const float DRAG_INTERVAL = 0.15f; // drag initiates after this long
	static const int DRAG_DIST = 5; // or this far
}

InputEventProducer::InputEventProducer() 
: curmousex(0), curmousey(0), wantexit(0) {
	doublestate.button = 0;
	dragstate.button = 0;
}
InputEventProducer::~InputEventProducer() { }

void InputEventProducer::addListener(InputEventListener &listener) {
	listeners.push_back(&listener);
}

void InputEventProducer::removeListener(InputEventListener &listener) {
	remove_if(listeners.begin(), listeners.end(), bind1st(equal_to<InputEventListener *>(), &listener));
}

void InputEventProducer::update(float tdelta) {
	if (doublestate.button) { // if theres a double click pending
		doublestate.timectr += tdelta; // increase its timer
		if (doublestate.timectr > DOUBLECLICK_INTERVAL) // too long
			doublestate.button = 0; // no more double pending
	}
	
	if (dragstate.button) { // if we have dragging state available
		if (dragstate.timectr > 0)  // if there's time left on the drag counter
			dragstate.timectr -= tdelta; // decrease it timer
	}
}

void InputEventProducer::mouseMoved(int x, int y) {
	curmousex = x; curmousey = y;
	if (dragstate.button) { // if we've got a dragstate
		if (dragstate.timectr > 0) {
			int dist = abs(curmousex - dragstate.initx) + abs(curmousey - dragstate.inity);
			if (dist >= DRAG_DIST)
				dragstate.timectr = 0;
		}
	
		if (dragstate.timectr <= 0) // if we're currently dragging
			dispatchEvent(InputEvent::CLICK_DRAG, x, y, dragstate.button); // send a drag event
		return;
	}
	
	dispatchEvent(InputEvent::CLICK_HOVER, x, y);
}

void InputEventProducer::mouseDown(MouseButton button) {
	if (doublestate.button == button) {
	  int dist = abs(curmousex - doublestate.initx) + abs(curmousey - doublestate.inity);
		if (dist < DOUBLECLICK_DIST) {
			doublestate.button = 0;
			dispatchEvent(InputEvent::CLICK_DOUBLE, curmousex, curmousey, button);
			return;
		}
	}

	if (!(button == mousebtns::wheeldown || button == mousebtns::wheelup)) { // mouse wheel doesn't get double click or drag
		doublestate.button = button;
		doublestate.timectr = 0;
		doublestate.initx = curmousex;
		doublestate.inity = curmousey;
	
		if (!dragstate.button) {
			dragstate.button = button;
			dragstate.timectr = DRAG_INTERVAL;
		}
	}
	
	dispatchEvent(InputEvent::CLICK_SINGLE, curmousex, curmousey, button);
}

void InputEventProducer::mouseUp(MouseButton button) {
	if (dragstate.button == button) {
		dragstate.button = 0;
		dispatchEvent(InputEvent::CLICK_RELEASE, curmousex, curmousey, button);
	}
}

void InputEventProducer::keyDown(KeyCode key, char ch) {
	keysdown.insert(key);
	dispatchEvent(InputEvent::KEY_PRESSED, curmousex, curmousey, key, ch);
}

void InputEventProducer::keyUp(KeyCode key) {
	keysdown.erase(key);
	dispatchEvent(InputEvent::KEY_RELEASED, curmousex, curmousey, key);
} 

void InputEventProducer::exitEvent() {
	wantexit = true;
}

void InputEventProducer::dispatchEvent(InputEvent::Type type, int mousex, int mousey, mge::KeyCode key, char ch) {
	dispatchEvent(type, mousex, mousey, key, ch, 0);
}

void InputEventProducer::dispatchEvent(InputEvent::Type type, int mousex, int mousey, mge::MouseButton button) {
	dispatchEvent(type, mousex, mousey, 0, 0, button);
}

void InputEventProducer::dispatchEvent(InputEvent::Type type, int mousex, int mousey) {
	dispatchEvent(type, mousex, mousey, 0, 0, 0);
}

void InputEventProducer::dispatchEvent(InputEvent::Type type, int mousex, int mousey, mge::KeyCode key, char ch, mge::MouseButton button) {
	InputEvent event(type, mousex, mousey, keysdown.begin(), keysdown.end(), key, ch, button);

	for (ListenerList::iterator i = listeners.begin(); i != listeners.end(); ++i) {
		if ((*i)->gotEvent(event))
			return;
	}
}


