#ifndef STO_SHARED_PACKETCONNECTION_H
#define STO_SHARED_PACKETCONNECTION_H

#include "PacketManager.h"
#include "Packet.h"
#include <MGE/net/Connection.h>
#include <MGE/net/Message.h>
#include <boost/shared_ptr.hpp>

namespace sto {
	class PacketConnection {
		public:
			PacketConnection(const boost::shared_ptr<mge::Connection> &conn);
			
			inline mge::Connection::State getState() const { return conn->getState(); }
			
			Packet *receive();
			void send(const Packet &packet, int chan, mge::Message::Type type);
			
			inline void disconnect() { conn->disconnect(); }
			
		private:
			boost::shared_ptr<mge::Connection> conn;
			
			struct AssembledPacketManager : public PacketManager {
				AssembledPacketManager(); // static initializer that fills out the PacketManager
			};
			
			static const AssembledPacketManager pman;
	};
}

#endif
