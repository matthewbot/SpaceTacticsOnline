#include "PacketManager.h"
#include "PacketFactory.h"
#include "Packet.h"
#include <MGE/util/Blob.h>
#include <MGE/util/Exception.h>
#include <boost/bind.hpp>
#include <algorithm>
#include <functional>
#include <sstream>
#include <memory>

using namespace sto;
using namespace mge;
using namespace boost;
using namespace std;

PacketManager::PacketManager() { }
PacketManager::~PacketManager() { }

void PacketManager::addFactory(PacketFactory *factory) {
	factories.push_back(factory);
}

#include <iostream>

void PacketManager::encode(const Packet &packet, Blob &blob) const {
	const type_info &packettype = typeid(packet);
	FactoryList::const_iterator pos = find_if(factories.begin(), factories.end(), bind(&PacketFactory::isMatch, _1, ref(packet), cref(packettype)));
	
	if (pos == factories.end())
		throw Exception("No packet factory could encode packet!");
		
	blob.put((unsigned char)(*pos)->getID());
	packet.pack(blob);
	
	cout << "Encoded blob:" << endl << blob << endl;
}

static bool check_id(PacketFactory *factory, int id) { return factory->getID() == id; }

Packet *PacketManager::decode(Blob &blob) const {
	int id = blob.get<unsigned char>();
	
	FactoryList::const_iterator pos = find_if(factories.begin(), factories.end(), bind(&check_id, _1, id));
	
	if (pos == factories.end()) {
		stringstream buf;
		buf << "No packet factory could decode packet (" << id << ")";
		throw Exception(buf.str());
	}
		
	auto_ptr<Packet> packet((*pos)->makePacket());
	packet->unpack(blob);
	return packet.release();
}

