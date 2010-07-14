#include "ConnectPacket.h"
#include <MGE/util/Blob.h>

using namespace sto;
using namespace mge;
using namespace std;

ConnectPacket::ConnectPacket() { }
ConnectPacket::ConnectPacket(const string &version, const string &username, const string &authmsg)
: version(version), username(username), authmsg(authmsg) { }
ConnectPacket::~ConnectPacket() { }

void ConnectPacket::pack(Blob &blob) const {
	blob.putString(version);
	blob.putString(username);
	blob.putString(authmsg);
}

void ConnectPacket::unpack(Blob &blob) {
	version = blob.getString();
	username = blob.getString();
	authmsg = blob.getString();
}


