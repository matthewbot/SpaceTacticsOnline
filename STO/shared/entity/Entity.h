#ifndef STO_SHARED_ENTITY_H
#define STO_SHARED_ENTITY_H

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <vector>

namespace sto {
	class EntityComponent;

	class Entity : boost::noncopyable {
		public:
			Entity();
			~Entity();
			
			void addComponent(const boost::shared_ptr<EntityComponent> &component);
			
			inline void setDestroyFlag() { destroyflag = true; }
			inline bool getDestroyFlag() { return destroyflag; }
			
		private:
			typedef std::vector<boost::shared_ptr<EntityComponent> > ComponentList;
			ComponentList components;
			bool destroyflag;
	};
}

#endif
