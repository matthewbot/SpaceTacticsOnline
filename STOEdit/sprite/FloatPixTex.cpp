#include "FloatPixTex.h"
#include <MGE/gfx/texture/png.h>
#include <MGE/gfx/texture/Texture.h>
#include <MGE/gfx/texture/TextureManager.h>
#include <MGE/util/Exception.h>
#include <fstream>

using namespace stoedit;
using namespace mge;
using namespace boost;
using namespace std;

FloatPixTex::FloatPixTex(TextureManager &texman) : texman(texman) { }
FloatPixTex::~FloatPixTex() { }

void FloatPixTex::open(const string &name) {
	ifstream file(name.c_str(), ios_base::binary);
	if (!file.is_open())
		throw Exception(string("Failed to open ") + name);
	pix = loadPNG(file); // read the PNG
	
	regenTexFromPix(); // make texture
	regenFloatFromPix(); // make floats
}

void FloatPixTex::regenTexFromPix() {
	tex = texman.createTexture(pix);
	smoothtex.reset();
}

void FloatPixTex::regenFloatFromPix() {
	floatpix = FloatMap(pix.getWidth(), pix.getHeight());

	FloatMap::pixel_t *f = floatpix.getData();
	for (PixMap::pixel_t *p = pix.getData(); p != pix.getEnd(); p++, f++) { // convert to floating point
		f->nx = (float)(p->col.r-128)/127.0f; // first two are a vector from (-1 .. 1)
		f->ny = (float)(p->col.g-128)/127.0f;
		f->em = (float)(p->col.b)/255.0f; // team emblem is a float from (0 .. 1)
		f->sh = (float)(p->col.a)/255.0f; // shinyness factor is a float from (0 .. 1)
	}
}

void FloatPixTex::save(const string &name) {
	regenPix(); // generate pixels
	
	ofstream file(name.c_str(), ios_base::binary);
	if (!file.is_open())
		throw Exception(string("Failed to open ") + name);
		
	savePNG(pix, file); // save then
}

void FloatPixTex::clear() {
	pix = PixMap();
	tex.reset();
}

void FloatPixTex::clear(int width, int height) {
	PixMap::pixel_t emptypix; FloatMap::pixel_t emptyfloatpix;
	emptypix.val = 0;
	emptyfloatpix.nx = emptyfloatpix.ny = emptyfloatpix.sh = emptyfloatpix.em = 0;
	
	pix = PixMap(width, height, emptypix);
	floatpix = FloatMap(width, height, emptyfloatpix);
	
	regenTexFromPix();
}

void FloatPixTex::regenTex() {
	regenPix();
	regenTexFromPix();
}

void FloatPixTex::regenPix() {
 	FloatMap::pixel_t *f = floatpix.getData();
	for (PixMap::pixel_t *p = pix.getData(); p != pix.getEnd(); p++, f++) {
		p->col.r = (int)(f->nx * 127) + 128;
		p->col.g = (int)(f->ny * 127) + 128;
		p->col.b = (int)(f->em * 255);
		p->col.a = (int)(f->sh * 255);
	}
}

const shared_ptr<Texture> &FloatPixTex::getSmoothTex() const {
	if (!smoothtex) 
		smoothtex = texman.createTexture(pix, TF_SUBPIXEL);
		
	return smoothtex;
}
