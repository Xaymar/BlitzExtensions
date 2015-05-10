#include "dllmain.h"
#include <list>
#include "sqlite3.h"

void SQLite3_OnProcessAttach();
void SQLite3_OnProcessDetach();

extern "C" {
	DLL_EXPORT int sqlite3_bind_int64_ex(void* stmtPtr, uint32_t index, uint32_t low, uint32_t high);
	DLL_EXPORT int sqlite3_bind_float(void* stmtPtr, uint32_t index, float value);

	DLL_EXPORT void sqlite3_column_int64_ex(void* stmtPtr, uint32_t index, void* outPtr);
	DLL_EXPORT float sqlite3_column_float(void* stmtPtr, uint32_t index);
}