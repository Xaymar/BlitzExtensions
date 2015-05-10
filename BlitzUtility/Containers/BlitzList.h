#pragma once
#include "dllmain.h"
#include <memory>
#include <sstream>
#include <iomanip>
#include <list>

// Rev-engineered from https://github.com/blitz-research/blitz3d/blob/master/compiler/declnode.cpp
#define BBVARTYPE_GLOBAL	0
#define BBVARTYPE_INT		1
#define BBVARTYPE_FLOAT		2
#define BBVARTYPE_UNUSED	3
#define BBVARTYPE_STRING	4
#define BBVARTYPE_TYPE		5
#define BBVARTYPE_ARRAY		6

struct BBVar {
	unsigned int Type;
};

struct BBVarElement {
	int* currentPtr; // Points towards fields.
	BBVarElement* nextPtr;
	BBVarElement* prevPtr;
	void* BBVarTypePtr;
	unsigned int refCount;	// Fields usually follow here, may be at another location, see currentPtr.
};

struct BBVarType : BBVar {
	BBVarElement used, free;
	unsigned int fieldCount; // Field Info follows (Exactly <fieldCount> int pointers to variable struct)
	//BBVar* fields[];
};

struct BlitzTypeInfo {
	BBVarType *type;
	BBVarElement *lastNextPtr, *lastPrevPtr;
	BBVarElement *ourNextPtr, *ourPrevPtr;
};

void BlitzList_OnProcessAttach();
void BlitzList_OnProcessDetach();

DLL_EXPORT void* BlitzList_New(void* type);
DLL_EXPORT void BlitzList_Activate(void* list);
DLL_EXPORT void BlitzList_Deactivate(void* list);
DLL_EXPORT void BlitzList_Delete(void* list);
