#ifndef STO_SERVER_PLAYERCONTROLLER_H
#define STO_SERVER_PLAYERCONTROLLER_H

#include <string>
#include <STO/shared/input/FlightInput.h>

namespace sto {
	class Player;

    class PlayerController {
    	public:
		    inline virtual ~PlayerController() { }
		    
		    virtual void sendChatMessage(const Player &from, const std::string &msg) = 0;
		    virtual FlightInput getFlightInput() = 0;
    };
}

#endif
