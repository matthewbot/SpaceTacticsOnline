#ifndef STOEDIT_STOEDITSYSTEM_H
#define STOEDIT_STOEDITSYSTEM_H

#include "FPSOverlay.h"
#include <MGE/kernel/KernelSystem.h>
#include <STOEdit/core/WorkSpace.h>
#include <STOEdit/input/InputEventProducer.h>
#include <boost/shared_ptr.hpp>
#include <memory>

namespace mge {
	class GraphicsSystem;
	class ResourceSystem;
	class Font;
}

namespace stoedit {
	class InputEventProducer;
	class EditController;

	class STOEditSystem : public mge::KernelSystem {
		public:
			STOEditSystem(mge::GraphicsSystem &gfx, mge::ResourceSystem &res);
			~STOEditSystem();
			
			void setController(EditController *controller);
			
			virtual mge::SystemUpdateValue update();
			virtual const char *getName() const;
			
		private:
			mge::GraphicsSystem &gfx;
			mge::ResourceSystem &res;
			
			WorkSpace workspace;
			InputEventProducer eventprod;
			
			std::auto_ptr<EditController> controller;
			
			FPSOverlay fpsoverlay;
			
			void setStandardWorkSpaceLayout(int sidecount);
	};
}

#endif
