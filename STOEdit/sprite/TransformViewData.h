#ifndef STOEDIT_TRANSFORMVIEWDATA_H
#define STOEDIT_TRANSFORMVEIWDATA_H

#include <STOEdit/core/ViewData.h>
#include <MGE/gfx/Transform.h>

namespace stoedit {
	class InputEvent;
	class ViewProperties;

	class TransformViewData : public ViewData {
		public:
			TransformViewData();
			virtual ~TransformViewData();
			
			void reset();
			
			mge::Transform getTransform();
			
			inline float getZoom() const { return zoom; }
			inline void setZoom(float zoom) { this->zoom = zoom; }
			inline float getTranslateX() const { return translatex; }
			inline void setTranslateX(float translatex) { this->translatex = translatex; }
			inline float getTranslateY() const { return translatey; }
			inline void setTranslateY(float translatey) { this->translatey = translatey; }
			
			static TransformViewData &makeFromProperties(ViewProperties &props);
			
		private:
			float translatex, translatey;
			float zoom;
	};
}

#endif
