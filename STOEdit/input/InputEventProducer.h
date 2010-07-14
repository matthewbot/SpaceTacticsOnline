#ifndef STOEDIT_INPUTEVENTPRODUCER_H
#define STOEDIT_INPUTEVENTPRODUCER_H

#include "InputEvent.h"
#include <MGE/util/input/InputListener.h>
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <boost/noncopyable.hpp>
#include <set>
#include <vector>

namespace stoedit {
	class InputEventListener;

	class InputEventProducer : public mge::InputListener, boost::noncopyable {
		public:
			InputEventProducer();
			virtual ~InputEventProducer();
		
			void addListener(InputEventListener &listener);
			void removeListener(InputEventListener &listener);
			
			void update(float tdelta);
		
			inline bool getExit() const { return wantexit; }
		
			// InputListener
			
			virtual void mouseMoved(int x, int y);
			virtual void mouseDown(mge::MouseButton button);
			virtual void mouseUp(mge::MouseButton button);
			
			virtual void keyDown(mge::KeyCode key, char ch);
			virtual void keyUp(mge::KeyCode key);
			
			virtual void exitEvent();
		
		private:
			typedef std::vector<InputEventListener *> ListenerList;
			ListenerList listeners;
			
			int curmousex, curmousey;
			
			struct DoubleClickState {
				mge::MouseButton button;
				int initx, inity;
				float timectr;
			} doublestate;
			
			struct DraggingState {
				mge::MouseButton button;
				int initx, inity;
				float timectr;
			} dragstate;
			
			std::set<mge::KeyCode> keysdown;
			
			bool wantexit;
			
			void dispatchEvent(InputEvent::Type type, int mousex, int mousey, mge::KeyCode key, char ch, mge::MouseButton button);
			void dispatchEvent(InputEvent::Type type, int mousex, int mousey, mge::KeyCode key, char ch=0);
			void dispatchEvent(InputEvent::Type type, int mousex, int mousey, mge::MouseButton button);
			void dispatchEvent(InputEvent::Type type, int mousex, int mousey);
			
			void clearListeners();
	};
}

#endif
