#include "LightSpriteFactory.h"
#include "LightSprite.h"
#include <MGE/gfx/texture/TextureManager.h>
#include <MGE/res/system/ResourceSystem.h>
#include <MGE/res/system/ResourceNode.h>
#include <MGE/res/Shader.h>

using namespace sto;
using namespace mge;
using namespace boost;
using namespace std;

LightSpriteFactory::LightSpriteFactory(ResourceSystem &res, TextureManager &texman)
: res(res), texman(texman) { }

Resource *LightSpriteFactory::makeResource(const string &name, const ResourceNode &resnode) {
	if (resnode.getString("type") != "lightsprite")
		return NULL;

	string filename = resnode.getString("filename");
	string normalname = makeNormalName(filename);
	string subpixel = resnode.getString("subpixel", "on");
	string shadername = resnode.getString("shader", "shd_light");

	TexFlags tf = (subpixel == "on") ? TF_SUBPIXEL : TF_NONE;

	shared_ptr<Texture> colortex = texman.loadTexture(filename, tf);
	shared_ptr<Texture> normaltex = texman.loadTexture(normalname, tf);
	shared_ptr<Shader> shader = res.get<Shader>(shadername);

	LightSpriteProps props;
	props.tx = resnode.getFloat("tx", 0);
	props.ty = resnode.getFloat("ty", 0);
	props.tw = resnode.getFloat("tw", (float)colortex->getWidth());
	props.th = resnode.getFloat("th", (float)colortex->getHeight());
	props.rotoffset = resnode.getFloat("rotoffset", 0)/180*3.14159265;

	if (resnode.getString("origin", "") == "centered") {
		props.ox = props.tw/2;
		props.oy = props.th/2;
	} else {
		props.ox = resnode.getFloat("ox", 0);
		props.oy = resnode.getFloat("oy", 0);
	}

	return new LightSprite(name, props, colortex, normaltex, shader);
}

string LightSpriteFactory::makeNormalName(const std::string &filename) {
	size_t pos = filename.find_last_of('.');
	if (pos == string::npos)
		return filename + "_n";
	else
		return filename.substr(0, pos) + "_n" + filename.substr(pos);
}
