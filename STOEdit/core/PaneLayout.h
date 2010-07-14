#ifndef STOEDIT_PANELAYOUT_H
#define STOEDIT_PANELAYOUT_H

#include <vector>
#include <MGE/gfx/ViewSection.h>

namespace stoedit {
	class PaneLayout {
		private:
			typedef std::vector<mge::ViewSection> LayoutList;
			
		public:
			PaneLayout();
			
			void append(int x, int y, int w, int h);
			void append(const mge::ViewSection &entry);
			
			typedef LayoutList::const_iterator const_iterator;
			
			inline const_iterator begin() const { return entries.begin(); }
			inline const_iterator end() const { return entries.end(); }
	
		private:
			LayoutList entries;
			
	};
}

#endif
