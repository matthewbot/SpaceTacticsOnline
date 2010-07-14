#ifndef STOEDIT_VIEWPROPERTIES_H
#define STOEDIT_VIEWPROPERTIES_H

#include <map>
#include <string>

namespace stoedit {
	class ViewData;

	class ViewProperties {
		public:
			ViewProperties();
			~ViewProperties();
			
			bool checkData(const std::string &name) const;
			void addData(const std::string &name, ViewData *data);
			ViewData &getData(const std::string &name) const;
			template <class ViewDataT> ViewDataT &getData(const std::string &name) const {
				return (ViewDataT &)getData(name);
			}
	
		private:
			typedef std::map<std::string, ViewData *> PropertyMap;
			PropertyMap props;
	};
}

#endif
