#include "Display.h"

std::list<Display>* Display_List = NULL;

void Display_OnProcessAttach() {
	Display_List = new std::list<Display>();
}

void Display_OnProcessDetach() {
	Display_List->clear();
	delete Display_List;
}

DLL_EXPORT void Display_Enumerate() {
	if (Display_List == NULL)
		return;

	Display_List->clear();

	EnumDisplayMonitors(NULL, NULL, Display_EnumerateProcedure, 0);
}

BOOL CALLBACK Display_EnumerateProcedure(HMONITOR hMonitor, HDC hdcMonitor, LPRECT lprcMonitor, LPARAM dwData) {
	Display *thisDisplay = new Display;

	thisDisplay->left = lprcMonitor->left;
	thisDisplay->top = lprcMonitor->top;
	thisDisplay->right = lprcMonitor->right;
	thisDisplay->bottom = lprcMonitor->bottom;

	Display_List->push_back(*thisDisplay);

	return TRUE;
}

DLL_EXPORT int Display_Count() {
	return Display_List->size();
}

DLL_EXPORT void Display_Get(int displayId, LPRECT display) {
	if (Display_List->size() > (unsigned)displayId) {
		auto iterator = Display_List->begin();

		std::advance(iterator, displayId);

		if (display != NULL) {
			display->left = iterator->left;
			display->top = iterator->top;
			display->right = iterator->right;
			display->bottom = iterator->bottom;
		}
	}
}

