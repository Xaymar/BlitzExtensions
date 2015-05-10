#pragma once
#include "SQLite.h"

void SQLite3_OnProcessAttach() {
	sqlite3_initialize();
}

void SQLite3_OnProcessDetach() {
	sqlite3_shutdown();
}

DLL_EXPORT int sqlite3_bind_int64_ex(void* stmtPtr, uint32_t index, uint32_t low, uint32_t high) {
	return sqlite3_bind_int64((sqlite3_stmt*)stmtPtr, index, (((uint64_t)low << 32) + (uint64_t)high));
}

DLL_EXPORT int sqlite3_bind_float(void* stmtPtr, uint32_t index, float value) {
	return sqlite3_bind_double((sqlite3_stmt*)stmtPtr, index, (double)value);
}

DLL_EXPORT void sqlite3_column_int64_ex(void* stmtPtr, uint32_t index, void* outPtr) {
	sqlite3_int64 out = sqlite3_column_int64((sqlite3_stmt*)stmtPtr, index);
	int* ourPtr = (int*)outPtr;
	(*ourPtr) = (int)(out & 0xFFFFFFFF);
	(*(ourPtr + 1)) = (int)(out >> 32);
}

DLL_EXPORT float sqlite3_column_float(void* stmtPtr, uint32_t index) {
	double out = sqlite3_column_double((sqlite3_stmt*)stmtPtr, index);
	return (float)out;
}