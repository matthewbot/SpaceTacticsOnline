#ifndef STO_CLIENT_SERVERCONNECTIONCALLBACKS_H
#define STO_CLIENT_SERVERCONNECTIONCALLBACKS_H

#include <STO/shared/net/BaseConnectionCallbacks.h>
#include <STO/shared/packet/Packet.h>
#include <MGE/util/Blob.h>
#include <boost/shared_ptr.hpp>
#include <string>

namespace sto {
    class ServerConnectionCallbacks : public BaseConnectionCallbacks {
        public:
            inline virtual ~ServerConnectionCallbacks() { }
            
            virtual void onConnect() = 0;
            
            virtual void onCreateEntity(int id, const std::string &name, const mge::Blob &update) = 0;
            virtual void onUpdateEntity(int id, const mge::Blob &update, bool isfullupdate) = 0;
    };
}

#endif
