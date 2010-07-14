#include "ConnectRefusedPacket.h"
#include <MGE/util/Blob.h>

using namespace sto;
using namespace mge;
using namespace std;

ConnectRefusedPacket::ConnectRefusedPacket() { }
ConnectRefusedPacket::ConnectRefusedPacket(const string &msg) : msg(msg) { }
ConnectRefusedPacket::~ConnectRefusedPacket() { }

void ConnectRefusedPacket::unpack(Blob &blob) {
	msg = blob.getString();
}

void ConnectRefusedPacket::pack(Blob &blob) const {
	blob.putString(msg);
}
