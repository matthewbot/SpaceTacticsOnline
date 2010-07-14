#include "PaneLayout.h"

using namespace stoedit;
using namespace mge;

PaneLayout::PaneLayout() { }

void PaneLayout::append(int x, int y, int w, int h) {
	ViewSection entry = { x, y, w, h };
	entries.push_back(entry);
}

void PaneLayout::append(const ViewSection &entry) {
	entries.push_back(entry);
}
