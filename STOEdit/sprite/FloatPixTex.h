#ifndef STOEDIT_FLOATPIXTEX_H
#define STOEDIT_FLOATPIXTEX_H

#include <MGE/gfx/texture/PixMap.h>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <string>

namespace mge {
	class Texture;
	class TextureManager;
}

namespace stoedit {
	struct FloatPixel {
		float nx, ny;
		float em;
		float sh;
	};
	
	typedef mge::ImageMap<FloatPixel> FloatMap;

	class FloatPixTex {
		public:
			FloatPixTex(mge::TextureManager &texman);
			~FloatPixTex();
		
			void open(const std::string &name);
			void save(const std::string &name);
			void clear();
			void clear(int width, int height);
			
			inline int getWidth() const { return pix.getWidth(); }
			inline int getHeight() const { return pix.getHeight(); }
			
			inline FloatMap &getFloats() { return floatpix; }
			inline const FloatMap &getFloats() const { return floatpix; }
			
			inline const mge::PixMap &getPix() const { return pix; }
			void regenPix();
			
			inline const boost::shared_ptr<mge::Texture> &getTex() const { return tex; }
			const boost::shared_ptr<mge::Texture> &getSmoothTex() const;
			void regenTex();
			
		private:
			mge::TextureManager &texman;
		
			boost::shared_ptr<mge::Texture> tex;
			mutable boost::shared_ptr<mge::Texture> smoothtex;
			mge::PixMap pix;
			FloatMap floatpix;
			
			void regenFloatFromPix();
			void regenTexFromPix();
	};
}

#endif
