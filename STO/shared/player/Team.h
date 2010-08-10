#ifndef STO_SERVER_TEAM_H
#define STO_SERVER_TEAM_H

#include <MGE/gfx/util/Color.h>
#include <boost/noncopyable.hpp>
#include <string>

namespace sto {
	class Team : boost::noncopyable {
		public:
			typedef int ID;
			Team(ID id, const std::string &name, const mge::Color &color);
			
			inline ID getID() const { return id; }
			inline const mge::Color &getColor() const { return color; }
			inline const std::string &getName() const { return name; }
			
		private:
			const ID id;
			std::string name;
			mge::Color color;
	};
	

}

#endif
