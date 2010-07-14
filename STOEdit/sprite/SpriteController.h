#ifndef STOEDIT_SPRITECONTROLLER_H
#define STOEDIT_SPRITECONTROLLER_H

#include <STOEdit/input/InputEventListener.h>
#include <STOEdit/system/EditController.h>
#include "SpriteData.h"
#include "SpriteControllerRes.h"

namespace mge {
	class TextureManager;
	class ResourceSystem;
}

namespace stoedit {
	class WorkSpace;
	class ViewFactory;

	class SpriteController : public EditController {
		public:
			SpriteController(mge::TextureManager &texman, WorkSpace &workspace);
			virtual ~SpriteController();

			inline SpriteControllerRes &getRes() { return spriteres; }
			inline const SpriteControllerRes &getRes() const { return spriteres; }

			// --- InputEventListener ---

			virtual bool gotEvent(const InputEvent &event);

		private:
			ViewFactory *getViewFactory(int num);
		
			SpriteData data;
			SpriteControllerRes spriteres;
			WorkSpace &workspace;
			
			struct OpenSaveTextViewCallback;
	};
}

#endif
