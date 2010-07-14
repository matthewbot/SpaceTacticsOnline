#ifndef STO_SERVER_PLAYER_H
#define STO_SERVER_PLAYER_H

#include <boost/noncopyable.hpp>
#include <memory>
#include <string>

namespace sto {
	class PlayerController;

	class Player : boost::noncopyable {
		public:
			typedef int ID;
			Player(ID id, const std::string &name, PlayerController *controller);
			~Player();
			
			inline ID getID() const { return id; }
			inline const std::string &getName() const { return name; }
			inline PlayerController &getController() const { return *controller; }
			
		private:
			const ID id;
			std::string name;
			PlayerController *controller;
	};
}

#endif
