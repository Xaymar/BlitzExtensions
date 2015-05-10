#pragma once
#include "Indexer.h"

#define INDEX_OFF_0 0x00000000
#define INDEX_OFF_1 0x10000000
#define INDEX_OFF_2 0x20000000
#define INDEX_OFF_3 0x30000000
#define INDEX_OFF_4 0x40000000
#define INDEX_OFF_5 0x50000000
#define INDEX_OFF_6 0x60000000
#define INDEX_OFF_7 0x70000000
#define INDEX_OFF_8 0x80000000
#define INDEX_OFF_9 0x90000000
#define INDEX_OFF_A 0xA0000000
#define INDEX_OFF_B 0xB0000000
#define INDEX_OFF_C 0xC0000000
#define INDEX_OFF_D 0xD0000000
#define INDEX_OFF_E 0xE0000000
#define INDEX_OFF_F 0xF0000000

unsigned int Indexer::GetFreeIndex()
{
	unsigned int index = lastAssignedIndex + 1;

	bool foundIndex = false;
	char indexBitOffset = 0;

	// We use 16 offsets here to speed up the search for a free index.
	while (foundIndex == false) {
		index = index + 64;

		uint64_t toCheck = this->indexes[index >> 6];
		for (indexBitOffset = 0; indexBitOffset < 64; indexBitOffset++) {
			if ((toCheck & (1ULL << indexBitOffset)) == false) {
				foundIndex = true;
				break;
			}
		}
	}
	index = index + indexBitOffset;

	// Mark Index as in use.
	this->indexes[index >> 6] |= 1ULL << indexBitOffset;
	lastAssignedIndex = index;

	return lastAssignedIndex;
}

void Indexer::MarkFreeIndex(int index)
{
	unsigned short bitFlip = index % 64;

	// Mark index as unused.
	this->indexes[index >> 6] &= ~(1ULL << bitFlip);
}

DLL_EXPORT void* Indexer_Create() {
	Indexer* indexer = new Indexer();
	return indexer;
}

DLL_EXPORT int Indexer_GetFreeIndex(void* indexerPtr) {
	Indexer* indexer = (Indexer*)indexerPtr;
	return indexer->GetFreeIndex();
}

DLL_EXPORT void Indexer_MarkFreeIndex(void* indexerPtr, int Index) {
	Indexer* indexer = (Indexer*)indexerPtr;
	indexer->MarkFreeIndex(Index);
}

DLL_EXPORT void Indexer_Destroy(void* indexerPtr) {
	Indexer* indexer = (Indexer*)indexerPtr;
	delete indexer;
}