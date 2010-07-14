#ifndef STOEDIT_SPRITECONTROLLERRES_H
#define STOEDIT_SPRITECONTROLLERRES_H

#include <boost/shared_ptr.hpp>

namespace mge {
	class Font;
	class Shader;
}

namespace stoedit {
	struct SpriteControllerRes {
		boost::shared_ptr<mge::Font> valuefont;
		boost::shared_ptr<mge::Font> dialogfont;
		boost::shared_ptr<mge::Shader> gameshader;
	};
}


#endif
