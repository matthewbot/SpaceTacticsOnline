#include "PlayerJoinedPacket.h"
#include <MGE/util/Blob.h>

using namespace sto;
using namespace mge;
using namespace std;

PlayerJoinedPacket::PlayerJoinedPacket() { }
PlayerJoinedPacket::PlayerJoinedPacket(int id, int teamid, const std::string &username)
: id(id), teamid(teamid), username(username) { }
PlayerJoinedPacket::~PlayerJoinedPacket() { }

void PlayerJoinedPacket::pack(Blob &blob) const {
	blob.put((short)id);
	blob.put((char)teamid);
	blob.putString(username);
}

void PlayerJoinedPacket::unpack(Blob &blob) {
	id = blob.get<short>();
	teamid = blob.get<char>();
	username = blob.getString();
}

