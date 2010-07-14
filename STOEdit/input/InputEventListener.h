#ifndef STOEDIT_INPUTEVENTLISTENER_H
#define STOEDIT_INPUTEVENTLISTENER_H

namespace stoedit {
	class InputEvent;

	class InputEventListener {
		public:
			inline virtual ~InputEventListener() { }
			
			virtual bool gotEvent(const InputEvent &event) = 0;
	};
}

#endif
