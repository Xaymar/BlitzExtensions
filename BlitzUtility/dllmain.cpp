#pragma once
#include "dllmain.h"

#include <list>
#include "Containers\BlitzList.h"
//#include "Database\SQLite\SQLite.h"
#include "Math\Vector2.h"
#include "Math\Vector3.h"
#include "Math\Matrix3.h"
#include "Utility\Display.h"
#include "Utility\Indexer.h"
#include "Utility\WindowMessageHandler.h"

bool WINAPI DllMain(HINSTANCE hinstDLL, DWORD fdwReason, LPVOID lpvReserved) {
	switch (fdwReason) {
		case DLL_PROCESS_ATTACH:
			// Containers
			BlitzList_OnProcessAttach();

			// Math

			// Database
			//SQLite3_OnProcessAttach();

			// Utility
			Display_OnProcessAttach();
			WindowMessageHandler_OnProcessAttach();

			break;
		case DLL_PROCESS_DETACH:
			// Containers
			BlitzList_OnProcessDetach();

			// Math

			// Database
			//SQLite3_OnProcessDetach();

			// Utility
			Display_OnProcessDetach();
			WindowMessageHandler_OnProcessDetach();

			break;
	}
	return TRUE;
}