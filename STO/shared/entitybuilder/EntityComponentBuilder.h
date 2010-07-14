#ifndef STO_SHARED_ENTITYCOMPONENTBUILDER_H
#define STO_SHARED_ENTITYCOMPONENTBUILDER_H

#include <STO/shared/entity/EntityContainer.h>
#include <MGE/util/Exception.h>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <map>
#include <string>
#include <utility>

namespace sto {
	class EntityComponent;

	typedef std::map<std::string, boost::shared_ptr<EntityComponent> > ComponentMap;
	typedef std::pair<std::string, boost::shared_ptr<EntityComponent> > NamedComponent;
	
	// TODO: Seperate header?
	template <typename T, typename MapT> boost::shared_ptr<T> lookup_ptr(const std::string &val, const MapT &map) {
		typename MapT::const_iterator i = map.find(val);
		if (i == map.end())
			throw mge::Exception(std::string("Couldn't lookup name ") + val);
		else
			return boost::static_pointer_cast<T>(i->second);
	}
	
	template <typename T, typename MapT> T &lookup_ref(const std::string &val, const MapT &map) { return *lookup_ptr<T>(val, map); }

	class EntityComponentBuilder : boost::noncopyable {
		public:
			inline virtual ~EntityComponentBuilder() { }
			
			virtual NamedComponent makeComponent(const ComponentMap &components, const ComponentSystemMap &compsystems) = 0;
	};
}

#endif

