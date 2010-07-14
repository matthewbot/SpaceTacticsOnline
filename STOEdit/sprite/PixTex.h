#ifndef STOEDIT_PIXTEX_H
#define STOEDIT_PIXTEX_H

#include <MGE/gfx/texture/PixMap.h>
#include <boost/shared_ptr.hpp>
#include <string>

namespace mge {
	class Texture;
	class TextureManager;
}

namespace stoedit {
	class PixTex {
		public:
			PixTex(mge::TextureManager &texman);
			~PixTex();
		
			void open(const std::string &name);
			void save(const std::string &name);
			void clear();
			void clear(int width, int height);
			
			inline int getWidth() { return pix.getWidth(); }
			inline int getHeight() { return pix.getHeight(); }
			inline mge::PixMap &getPix() { return pix; }
			inline const mge::PixMap &getPix() const { return pix; }
			inline const boost::shared_ptr<mge::Texture> &getTex() const { return tex; }
			const boost::shared_ptr<mge::Texture> &getSmoothTex() const;
			void regenTex();
			
		private:
			mge::TextureManager &texman;
		
			boost::shared_ptr<mge::Texture> tex;
			mutable boost::shared_ptr<mge::Texture> smoothtex;
			mge::PixMap pix;
	};
}

#endif
