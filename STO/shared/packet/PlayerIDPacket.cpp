#include "PlayerIDPacket.h"
#include <MGE/util/Blob.h>

using namespace sto;
using namespace mge;
using namespace std;

PlayerIDPacket::PlayerIDPacket() { }
PlayerIDPacket::PlayerIDPacket(int playerid) : playerid(playerid) { }
PlayerIDPacket::~PlayerIDPacket() { }

void PlayerIDPacket::pack(Blob &blob) const {
	blob.put<short>((short)playerid);
}

void PlayerIDPacket::unpack(Blob &blob) {
	playerid = blob.get<short>();
}


