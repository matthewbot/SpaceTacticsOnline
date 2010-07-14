#include "EntityUpdatePacket.h"
#include <MGE/util/Blob.h>

using namespace sto;
using namespace mge;
using namespace std;

EntityUpdatePacket::EntityUpdatePacket() { }
EntityUpdatePacket::EntityUpdatePacket(int id, bool full, bool remove, const Blob &newupdate) 
: id(id), full(full), remove(remove), update(newupdate.getRemaining()) {
	update.copyFrom(newupdate);
	update.flip();
}
EntityUpdatePacket::~EntityUpdatePacket() { }

void EntityUpdatePacket::pack(mge::Blob &blob) const {
	blob.put(id);
	blob.put((char)(full ? 1 : 0));
	blob.put((char)(remove ? 1 : 0));
	blob.copyFrom(update);
}

void EntityUpdatePacket::unpack(mge::Blob &blob) {
	id = blob.get<int>();
	
	full = (blob.get<char>() != 0);
	remove = (blob.get<char>() != 0);
	
	int updatesize = blob.get<char>();
	update.resize(updatesize);
	
	update.clear();
	update.copyFrom(blob);
	update.flip();
}


