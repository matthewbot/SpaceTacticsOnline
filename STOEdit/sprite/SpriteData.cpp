#include "SpriteData.h"
#include <MGE/util/Exception.h>

using namespace stoedit;
using namespace mge;
using namespace std;
using namespace boost;

SpriteData::SpriteData(TextureManager &texman) : color(texman), normal(texman) { }
SpriteData::~SpriteData() { }

void SpriteData::openSet(const string &colorname) {
	string fullpath = "../../STO/res/client/spr/" + colorname;
	color.open(fullpath);
	try {
		normal.open(makeNormalName(fullpath));
	} catch (Exception &ex) {
		normal.clear(color.getWidth(), color.getHeight());
	}
}

void SpriteData::saveSet(const string &colorname) {
	string fullpath = "../../STO/res/client/spr/" + colorname;
	color.save(fullpath);
	normal.save(makeNormalName(fullpath));
}

string SpriteData::makeNormalName(const string &colorname) {
	size_t pos = colorname.find_last_of('.');
	if (pos == string::npos)
		return colorname + "_n";
	else
		return colorname.substr(0, pos) + "_n" + colorname.substr(pos);
}
