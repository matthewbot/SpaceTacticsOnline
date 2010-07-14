#ifndef STOEDIT_SPRITEDATA_H
#define STOEDIT_SPRITEDATA_H

#include "PixTex.h"
#include "FloatPixTex.h"

namespace mge {
	class Texture;
	class TextureManager;
}

namespace stoedit {
	class SpriteData {
		public:
			SpriteData(mge::TextureManager &texman);
			~SpriteData();
			
			inline PixTex &getColor() { return color; }
			inline const PixTex &getColor() const { return color; }
			
			inline FloatPixTex &getNormal() { return normal; }
			inline const FloatPixTex &getNormal() const { return normal; }
			
			void openSet(const std::string &colorname);
			void saveSet(const std::string &colorname);
			
		private:
			static std::string makeNormalName(const std::string &colorname);
		
			PixTex color;
			FloatPixTex normal;
	};
}

#endif
