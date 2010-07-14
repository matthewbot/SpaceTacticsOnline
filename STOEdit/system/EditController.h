#ifndef STOEDIT_EDITCONTROLLER_H
#define STOEDIT_EDITCONTROLLER_H

#include <STOEdit/input/InputEventListener.h>

namespace stoedit {
	class EditController : public InputEventListener {
		public:
			inline virtual ~EditController() { }
	};
}

#endif
