#include "InputEvent.h"
#include <MGE/gfx/ViewSection.h>

using namespace stoedit;
using namespace std;

InputEvent::InputEvent(const InputEvent &event, const mge::ViewSection &oldsection, const mge::ViewSection &newsection) 
: type(event.type), keysdown(event.keysdown), key(event.key), ch(event.ch), button(event.button) {
	mousex = (int)( (event.getMouseX() - oldsection.x) / (float)oldsection.w * newsection.w ) + newsection.x;
	mousey = (int)( (event.getMouseY() - oldsection.y) / (float)oldsection.h * newsection.h ) + newsection.y;
}

bool InputEvent::isKeyHeld(mge::KeyCode key) const { return keysdown.find(key) != keysdown.end(); }

ostream &stoedit::operator<<(ostream &stream, const InputEvent &event) {
	switch (event.getType()) {
		case InputEvent::NONE:
			stream << "NONE";
			break;
			
		case InputEvent::CLICK_SINGLE:
			stream << "Single click at " << event.getMouseX() << "," << event.getMouseY() << " with button " << (int)event.getButton();
			break;
			
		case InputEvent::CLICK_DOUBLE:
			stream << "Double click at " << event.getMouseX() << "," << event.getMouseY() << " with button " << (int)event.getButton();
			break;
			
		case InputEvent::CLICK_HOVER:
			stream << "Hover at " << event.getMouseX() << "," << event.getMouseY() << " with button " << (int)event.getButton();
			break;
			
		case InputEvent::CLICK_DRAG:
			stream << "Drag at " << event.getMouseX() << "," << event.getMouseY() << " with button " << (int)event.getButton();
			break;
			
		case InputEvent::CLICK_RELEASE:
			stream << "Release at " << event.getMouseX() << "," << event.getMouseY() << " with button " << (int)event.getButton();
			break;
			
		case InputEvent::KEY_PRESSED:
			stream << "Key pressed " << event.getKey() << " char " << event.getChar();
			break;
			
		case InputEvent::KEY_RELEASED:
			stream << "Key released " << (char)event.getKey();
			break;
	}
	
	return stream;
}


