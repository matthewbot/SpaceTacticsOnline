#include "PlayerLeftPacket.h"
#include <MGE/util/Blob.h>

using namespace sto;
using namespace mge;
using namespace std;

PlayerLeftPacket::PlayerLeftPacket() { }
PlayerLeftPacket::PlayerLeftPacket(Player::ID id) : id(id) { }
PlayerLeftPacket::~PlayerLeftPacket() { }

void PlayerLeftPacket::pack(Blob &blob) const {
	blob.put<short>((short)id);
}

void PlayerLeftPacket::unpack(Blob &blob) {
	id = blob.get<short>();
}

