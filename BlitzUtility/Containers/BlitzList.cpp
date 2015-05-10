#pragma once
#include "BlitzList.h"

std::list<BlitzTypeInfo*>* BlitzUtility_Lists;

void BlitzList_OnProcessAttach() {
	BlitzUtility_Lists = new std::list<BlitzTypeInfo*>();
}

void BlitzList_OnProcessDetach() {
	BlitzUtility_Lists->clear();
	delete BlitzUtility_Lists;
}

DLL_EXPORT void* BlitzList_New(void* elementPtr) {
	BBVarElement* element = (BBVarElement*)(((int*)elementPtr) - 5);
	BBVarType* type = (BBVarType*)(*(((int*)elementPtr) - 2));

	// Create and initialize structure to hold information about this change.
	BlitzTypeInfo* bti = new BlitzTypeInfo();
	bti->type = type;

	// Store list pointers.
	bti->ourNextPtr = element;
	bti->ourPrevPtr = element;

	// Remove passed object from the flow of the old list.
	element->prevPtr->nextPtr = element->nextPtr;
	element->nextPtr->prevPtr = element->prevPtr;

	// Correct element next/prev pointers to no longer be inside the old list.
	element->prevPtr = (BBVarElement*)((int*)type + 1);
	element->nextPtr = (BBVarElement*)((int*)type + 1);

	BlitzUtility_Lists->push_back(bti);
	return bti;
}

DLL_EXPORT void BlitzList_Activate(void* list) {
	BlitzTypeInfo* bti = (BlitzTypeInfo*)list;

	// Store current pointers
	bti->lastNextPtr = bti->type->used.nextPtr;
	bti->lastPrevPtr = bti->type->used.prevPtr;

	// ... and replace them.
	bti->type->used.nextPtr = bti->ourNextPtr;
	bti->type->used.prevPtr = bti->ourPrevPtr;
}

DLL_EXPORT void BlitzList_Deactivate(void* list) {
	BlitzTypeInfo* bti = (BlitzTypeInfo*)list;

	// Store current pointers
	bti->ourNextPtr = bti->type->used.nextPtr;
	bti->ourPrevPtr = bti->type->used.prevPtr;

	// ... and replace them.
	bti->type->used.nextPtr = bti->lastNextPtr;
	bti->type->used.prevPtr = bti->lastPrevPtr;
}

DLL_EXPORT void BlitzList_Delete(void* list) {
	BlitzTypeInfo* bti = (BlitzTypeInfo*)list;
	BlitzUtility_Lists->remove(bti);
	delete bti;
}
