#ifndef STO_CLIENT_SERVERCALLBACKS_H
#define STO_CLIENT_SERVERCALLBACKS_H

#include <STO/shared/net/BaseClientServerCallbacks.h>
#include <STO/shared/packet/Packet.h>
#include <MGE/util/Blob.h>
#include <boost/shared_ptr.hpp>
#include <string>

namespace sto {
    class ServerCallbacks : public BaseClientServerCallbacks {
        public:
            inline virtual ~ServerCallbacks() { }
            
            virtual void onConnect() = 0;
            
            virtual void onCreateEntity(int id, const std::string &name, const mge::Blob &update) = 0;
            virtual void onUpdateEntity(int id, const mge::Blob &update, bool isfullupdate) = 0;
            virtual void onPlayerJoined(int id, int teamid, const std::string &username) = 0;
            virtual void onPlayerLeft(int id) = 0;
    };
}

#endif
