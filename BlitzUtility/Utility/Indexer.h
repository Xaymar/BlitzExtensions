#pragma once
#include <cstdlib>
#include <list>
#include "dllmain.h"

// 67108864 = 2 ^ 32 / 64
#define INDEXER_INDEXES 67108864

/** Indexer structure helps with getting unique, unused Indexes (Ids).
  * Doing this natively would be too slow, so I'm using a DLL for this.
  */
struct Indexer {
	uint64_t indexes[67108864];
	uint32_t lastAssignedIndex;

	unsigned int GetFreeIndex();
	void MarkFreeIndex(int index);
};

extern "C" {
	DLL_EXPORT void* Indexer_Create();
	DLL_EXPORT int Indexer_GetFreeIndex(void* index);
	DLL_EXPORT void Indexer_MarkFreeIndex(void* index, int Index);
	DLL_EXPORT void Indexer_Destroy(void* index);
}