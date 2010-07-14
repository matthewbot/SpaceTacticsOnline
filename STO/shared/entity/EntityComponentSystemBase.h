#ifndef STO_SHARED_ENTITYCOMPONENTSYSTEMBASE_H
#define STO_SHARED_ENTITYCOMPONENTSYSTEMBASE_H

#include "EntityComponentSystem.h"
#include <boost/shared_ptr.hpp>
#include <boost/weak_ptr.hpp>
#include <list>

namespace sto {
	template <typename CompT> class EntityComponentSystemBase : public EntityComponentSystem {
		public:
			EntityComponentSystemBase() { }
			virtual ~EntityComponentSystemBase() { }
			
			void registerComponent(const boost::shared_ptr<CompT> &comp) { components.push_back(comp); }
			
			virtual void update() {
				for (typename ComponentList::iterator i = components.begin(); i != components.end(); ) {
					boost::shared_ptr<CompT> comp(i->lock());
					if (comp) {
						updateComponent(comp);
						++i;
					} else {
						i = components.erase(i);
					}
				}
			}
			
		protected:
			virtual void updateComponent(const boost::shared_ptr<CompT> &comp)=0;
			
		private:
			typedef std::list<boost::weak_ptr<CompT> > ComponentList;
			ComponentList components;
	};
}

#endif
