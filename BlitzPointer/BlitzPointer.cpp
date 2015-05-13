// Original Code by Noodoby<http://www.blitzforum.de/forum/viewtopic.php?t=31651>
// Modified Code by Xaymar<http://project-kube.de>

#include "BlitzPointer.h"

DLL_EXPORT int32_t BlitzPointer_GetReturnAddress() {
	int32_t StackPointer, ReturnAddress;

	__asm { //ASM. Do touch if suicidal.
		mov StackPointer, esp;		// Store current Stack Pointer
		mov esp, ebp;				// On X86, EBP[0] is our own function and EBP[1] is the return address.
		add esp, 4;					// Which means that we can just take it from there into our own variable.
		pop ReturnAddress;			// Just like this.
		mov esp, [StackPointer];		// And then reset the Stack Pointer.
	}

	return ReturnAddress;
}
DLL_EXPORT int32_t BlitzPointer_GetFunctionPointer() {
	int32_t StackPointer, ReturnAddress;

	__asm { //ASM. Do touch if suicidal.
		mov StackPointer, esp;		// Store current Stack Pointer
		mov esp, ebp;				// On X86, EBP[0] is our own function and EBP[1] is the return address.
		add esp, 4;					// Which means that we can just take it from there into our own variable.
		pop ReturnAddress;			// Just like this.
		mov esp, [StackPointer];		// And then reset the Stack Pointer.
	}

	// Let's look backwards in memory for the function signature (0x53 0x56 0x57 0x55 0x89 0xE5) for at most one megabyte.
	uint8_t* startPtr = (uint8_t*)ReturnAddress;
	uint8_t* endPtr = (uint8_t*)(ReturnAddress - 1048576);
	for (uint8_t* curPtr = startPtr; curPtr != endPtr; curPtr--) {
		if (*(curPtr) == 0x53)												// push ebx
			if (*(curPtr + 1) == 0x56)										// push esi
				if (*(curPtr + 2) == 0x57)									// push edi
					if (*(curPtr + 3) == 0x55)								// push ebp
						if (*(curPtr + 4) == 0x89 && *(curPtr + 5) == 0xE5)	// mov ebp,esp
							return (int32_t)curPtr;
	}

	return 0;
}

// Defines for easier function generation.
#define CALLFUNCTION_DECL_BEGIN(NAME)					DLL_EXPORT int32_t BlitzPointer_CallFunction##NAME(intptr_t ipFunctionPointer
#define CALLFUNCTION_DECL_PARAMETER(TYPE, NAME)			, TYPE NAME
#define CALLFUNCTION_DECL_END()							)
#define CALLFUNCTION_DECL_IMPLEMENT()					) { int32_t result; 
#define CALLFUNCTION_IMPL_SAFEGUARD()					if (!ipFunctionPointer) return NULL;
#define CALLFUNCTION_IMPL_PREPARE(COUNT)				__asm { sub esp, COUNT * 4; }
#define CALLFUNCTION_IMPL_PARAMETER(INDEX, NAME)		__asm { mov eax, [ NAME ]; mov [esp - INDEX * 4], eax; }
#define CALLFUNCTION_IMPL_CALL()						__asm { call dword ptr[ipFunctionPointer]; }
#define CALLFUNCTION_IMPL_RETURN()						__asm { mov [result], eax }; return result; }

// Call Function with 0 parameter.
CALLFUNCTION_DECL_BEGIN(I0)
CALLFUNCTION_DECL_IMPLEMENT()
CALLFUNCTION_IMPL_SAFEGUARD()
CALLFUNCTION_IMPL_CALL()
CALLFUNCTION_IMPL_RETURN()

// Call Function with 1 parameter.
/*CALLFUNCTION_DECL_BEGIN(I1)
CALLFUNCTION_DECL_PARAMETER(int32_t, p1)
CALLFUNCTION_DECL_IMPLEMENT()
CALLFUNCTION_IMPL_SAFEGUARD()
//CALLFUNCTION_IMPL_PREPARE(1)
//CALLFUNCTION_IMPL_PARAMETER(0, p1)
CALLFUNCTION_IMPL_CALL()
CALLFUNCTION_IMPL_RETURN()*/


/*
DLL_EXPORT uint32_t BlitzPointer_CallFunction0(intptr_t fpFunctionPointer) {
	if (!fpFunctionPointer)
		return NULL;

	__asm {
		call dword ptr[fpFunctionPointer];
	}
	uint32_t rv;
	__asm {
		mov[rv], eax;
	}
	return rv;
}
DLL_EXPORT uint32_t BlitzPointer_CallFunction1(uint32_t fpFunctionPointer, uint32_t p1) {
	if (!fpFunctionPointer)
		return NULL;

	__asm {
		sub esp, 0x4;
		mov eax, [p1];
		mov[esp], eax;
		call dword ptr[fpFunctionPointer];
	}
	uint32_t rv;
	__asm {
		mov[rv], eax;
	}
	return rv;
}
DLL_EXPORT uint32_t BlitzPointer_CallFunction2(uint32_t fpFunctionPointer, uint32_t p1, uint32_t p2) {
	if (!fpFunctionPointer)
		return 0;

	__asm {
		sub esp, 0x8;
		mov eax, [p2];
		mov[esp + 4], eax;
		mov eax, [p1];
		mov[esp], eax;
		call dword ptr[fpFunctionPointer];
	}
	uint32_t rv;
	__asm {
		mov[rv], eax;
	}
	return rv;
}
DLL_EXPORT uint32_t BlitzPointer_CallFunction3(uint32_t fpFunctionPointer, uint32_t p1, uint32_t p2, uint32_t p3) {
	if (!fpFunctionPointer)
		return 0;

	__asm {
		sub esp, 0xC;
		mov eax, [p3];
		mov[esp + 8], eax;
		mov eax, [p2];
		mov[esp + 4], eax;
		mov eax, [p1];
		mov[esp], eax;
		call dword ptr[fpFunctionPointer];
	}
	uint32_t rv;
	__asm {
		mov[rv], eax;
	}
	return rv;
}
DLL_EXPORT uint32_t BlitzPointer_CallFunction4(uint32_t fpFunctionPointer, uint32_t p1, uint32_t p2, uint32_t p3, uint32_t p4) {
	if (!fpFunctionPointer)
		return 0;

	__asm {
		sub esp, 0x10;
		mov eax, [p4];
		mov[esp + 12], eax;
		mov eax, [p3];
		mov[esp + 8], eax;
		mov eax, [p2];
		mov[esp + 4], eax;
		mov eax, [p1];
		mov[esp], eax;
		call dword ptr[fpFunctionPointer];
	}
	uint32_t rv;
	__asm {
		mov[rv], eax;
	}
	return rv;
}

DLL_EXPORT uint32_t BlitzPointer_CallFunctionS0(uint32_t fpFunctionPointer) {
	uint32_t returnvalue;
	__asm {
		call dword ptr[fpFunctionPointer];
		mov[returnvalue], eax;
	}
	return *((uint32_t*)(returnvalue + 4));
}
DLL_EXPORT uint32_t BlitzPointer_CallFunctionS1(uint32_t fpFunctionPointer, uint32_t p1) {
	uint32_t returnvalue;
	__asm {
		sub esp, 0x4;
		mov eax, [p1];
		mov[esp], eax;
		call dword ptr[fpFunctionPointer];
		mov[returnvalue], eax;
	}
	return *((uint32_t*)(returnvalue + 4));
}
DLL_EXPORT uint32_t BlitzPointer_CallFunctionS2(uint32_t fpFunctionPointer, uint32_t p1, uint32_t p2) {
	uint32_t returnvalue;
	__asm {
		sub esp, 0x8;
		mov eax, [p2];
		mov[esp + 4], eax;
		mov eax, [p1];
		mov[esp], eax;
		call dword ptr[fpFunctionPointer];
		mov[returnvalue], eax;
	}
	return *((uint32_t*)(returnvalue + 4));
}
DLL_EXPORT uint32_t BlitzPointer_CallFunctionS3(uint32_t fpFunctionPointer, uint32_t p1, uint32_t p2, uint32_t p3) {
	uint32_t returnvalue;
	__asm {
		sub esp, 0xC;
		mov eax, [p3];
		mov[esp + 8], eax;
		mov eax, [p2];
		mov[esp + 4], eax;
		mov eax, [p1];
		mov[esp], eax;
		call dword ptr[fpFunctionPointer];
		mov[returnvalue], eax;
	}
	return *((uint32_t*)(returnvalue + 4));
}
DLL_EXPORT uint32_t BlitzPointer_CallFunctionS4(uint32_t fpFunctionPointer, uint32_t p1, uint32_t p2, uint32_t p3, uint32_t p4) {
	uint32_t returnvalue;
	__asm {
		sub esp, 0x10;
		mov eax, [p4];
		mov[esp + 12], eax;
		mov eax, [p3];
		mov[esp + 8], eax;
		mov eax, [p2];
		mov[esp + 4], eax;
		mov eax, [p1];
		mov[esp], eax;
		call dword ptr[fpFunctionPointer];
		mov[returnvalue], eax;
	}
	return *((uint32_t*)(returnvalue + 4));
}
*/