#include "Common.h"
#include <memory>
#include <sstream>

// Rev-engineered from https://github.com/blitz-research/blitz3d/blob/master/compiler/declnode.cpp
#define BBVARTYPE_GLOBAL	0
#define BBVARTYPE_INT		1
#define BBVARTYPE_FLOAT		2
#define BBVARTYPE_UNUSED	3
#define BBVARTYPE_STRING	4
#define BBVARTYPE_TYPE		5
#define BBVARTYPE_ARRAY		6

struct BBVar {
	int Type = -1;
};

struct BBVarGlobal {
	int GlobalType = -1;
	int* Value;
};

struct BBVarInt : BBVar {
	int Value;
};

struct BBVarFloat : BBVar {
	float Value;
};

struct BBVarUnused : BBVar {
	// Not a Dim, as you can see here:
	// https://github.com/blitz-research/blitz3d/blob/master/compiler/stmtnode.cpp#L86
};

struct BBVarString : BBVar {
	int Length;
	char* Value;
};

struct BBVarElement;
struct BBVarType : BBVar {
	BBVarElement used, free;
	int fieldCount; // Field Info follows (Exactly <fieldCount> int pointers to variable struct)
	int* fields[];
};

struct BBVarElement {
	int* currentPtr; // Points towards fields.
	int* nextPtr, prevPtr;
	BBVarType* BBStructPtr;
	int refCount;	// Fields usually follow here, may be at another location, see currentPtr.
	//BBVar* fields[];
};

struct BBVarArray : BBVar {
	int Size; //???
	BBVar* ArrayType;
};

std::string BBVar_Serialize(void* obj) {
	std::stringstream myStream;

	BBVar* var = (BBVar*)obj;
	switch (var->Type) {
	case BBVARTYPE_GLOBAL:
		BBVarGlobal* varGlobal = (BBVarGlobal*)obj;
		myStream << "[Global] " << BBVar_Serialize(varGlobal->Value) << std::endl;
		break;
	case BBVARTYPE_INT:
		BBVarInt* varInt = (BBVarInt*)obj;
		myStream << "Int" << std::endl;
		break;
	case BBVARTYPE_FLOAT:
		BBVarFloat* varFloat = (BBVarFloat*)obj;
		myStream << "Float" << std::endl;
		break;
	case BBVARTYPE_UNUSED:
		BBVarUnused* varUnused = (BBVarUnused*)obj;
		myStream << "Unused" << std::endl;
		break;
	case BBVARTYPE_STRING:
		BBVarString* varString = (BBVarString*)obj;
		myStream << "String" << std::endl;
		break;
	case BBVARTYPE_TYPE:
		BBVarType* varType = (BBVarType*)obj;
		myStream << BBVarType_Serialize(varType);
		break;
	case BBVARTYPE_ARRAY:
		BBVarArray* varArray = (BBVarArray*)obj;
		myStream << "Array = " << std::endl;
		break;
	}

	return myStream.str();
}

std::string BBVarType_Serialize(BBVarType* obj, unsigned int indent = 0) {
	std::stringstream myStream;

	std::stringstream myPaddingSS;
	for (unsigned int pad = 0; pad < indent; pad++) {
		myPaddingSS << "  ";
	}
	std::string myPadding = myPaddingSS.str();
	
	myStream << myPadding << "Type {" << std::endl;
	for (unsigned int fld = 0; fld < obj->fieldCount; fld++) {
		myStream << myPadding << "  (" << fld << ") => " << BBVar_Serialize(obj->fields[fld]) << std::endl;
	}
	myStream << myPadding << "}" << std::endl;

	return myStream.str();
}

DLL_EXPORT(char*) SerializeObject(void* obj) {
	return strdup(BBVar_Serialize(obj).c_str());
}

// Laut Mark Sibly:
struct BBType {
	int obj_size;
	BBObj usedList, freeList;
};

struct BBObj {
	BBObj *curr;
	BBObj *next, *prev;
	int* bbtype;
	int ref_cnt;
};
