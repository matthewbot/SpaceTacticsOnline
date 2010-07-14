#include "EntityCreatePacket.h"
#include <MGE/util/Blob.h>

using namespace sto;
using namespace mge;
using namespace std;

EntityCreatePacket::EntityCreatePacket() { }
EntityCreatePacket::EntityCreatePacket(int id, const string &entityname, const Blob &newupdate) 
: id(id), entityname(entityname), update(newupdate.getRemaining()) {
	update.copyFrom(newupdate);
	update.flip();
}
EntityCreatePacket::~EntityCreatePacket() { }

void EntityCreatePacket::pack(mge::Blob &blob) const {
	blob.put(id);
	blob.putString(entityname);
	blob.put((char)update.getRemaining());
	blob.copyFrom(update);
}

void EntityCreatePacket::unpack(mge::Blob &blob) {
	id = blob.get<int>();
	entityname = blob.getString();
	
	int updatesize = blob.get<char>();
	update.resize(updatesize);
	
	update.clear();
	update.copyFrom(blob);
	update.flip();
}


