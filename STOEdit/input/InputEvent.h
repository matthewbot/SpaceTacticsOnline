#ifndef STOEDIT_INPUTEVENT_H
#define STOEDIT_INPUTEVENT_H

#include <MGE/util/input/KeyCodes.h>
#include <ostream>
#include <set>

namespace mge {
	class ViewSection;
}

namespace stoedit {
	class InputEvent {	
		typedef std::set<mge::KeyCode> KeyCodeSet;
	
		public:
			enum Type {
				NONE,
				CLICK_SINGLE,
				CLICK_DOUBLE,
				CLICK_HOVER,
				CLICK_DRAG,
				CLICK_RELEASE,
				KEY_PRESSED,
				KEY_RELEASED
			};
			
			inline InputEvent() : type(NONE) { }
			InputEvent(const InputEvent &event, const mge::ViewSection &oldsection, const mge::ViewSection &newsection);
			template <typename InputIterator> InputEvent(Type type, int mousex, int mousey, InputIterator keysdownbeg, InputIterator keysdownend, mge::KeyCode key=0, char ch=0, mge::MouseButton button=0)
			: type(type), mousex(mousex), mousey(mousey), keysdown(keysdownbeg, keysdownend), key(key), ch(ch), button(button) { }
			
			inline Type getType() const { return type; }
			inline int getMouseX() const { return mousex; }
			inline int getMouseY() const { return mousey; }
			inline mge::KeyCode getKey() const { return key; }
			inline mge::MouseButton getButton() const { return button; }
			inline char getChar() const { return ch; }
			
			typedef KeyCodeSet::const_iterator key_iterator;
			inline key_iterator beginKeys() const { return keysdown.begin(); }
			inline key_iterator endKeys() const { return keysdown.end(); }
			
			bool isKeyHeld(mge::KeyCode key) const;
					
		private:
			Type type;
			int mousex, mousey;
			KeyCodeSet keysdown;
			mge::KeyCode key; char ch;
			mge::MouseButton button;
	};
	
	std::ostream &operator<<(std::ostream &stream, const InputEvent &event);
}

#endif
