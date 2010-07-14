#include "PixTex.h"
#include <MGE/gfx/texture/png.h>
#include <MGE/gfx/texture/TextureManager.h>
#include <MGE/util/Exception.h>
#include <fstream>

using namespace stoedit;
using namespace mge;
using namespace boost;
using namespace std;

PixTex::PixTex(TextureManager &texman) : texman(texman) { }
PixTex::~PixTex() { }

void PixTex::open(const string &name) {
	ifstream file(name.c_str(), ios_base::binary);
	if (!file.is_open())
		throw Exception(string("Failed to open ") + name);
		
	pix = loadPNG(file);
	regenTex();
}

void PixTex::save(const string &name) {
	ofstream file(name.c_str(), ios_base::binary);
	if (!file.is_open())
		throw Exception(string("Failed to open ") + name);
	savePNG(pix, file);
}

void PixTex::regenTex() {
	tex = texman.createTexture(pix);
	smoothtex.reset();
}

void PixTex::clear() {
	pix = PixMap();
	tex.reset();
}

void PixTex::clear(int width, int height) {
	PixMap::pixel_t blackpix;
	blackpix.val = 0;
	
	pix = PixMap(width, height, blackpix); // fill with 0 (black)
	regenTex();
}

const shared_ptr<Texture> &PixTex::getSmoothTex() const {
	if (!smoothtex) 
		smoothtex = texman.createTexture(pix, TF_SUBPIXEL);
		
	return smoothtex;
}
