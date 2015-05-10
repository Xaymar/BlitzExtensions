#include "dllmain.h"

DLL_EXPORT uint32_t BlitzPointer_GetReturnAddress();
DLL_EXPORT uint32_t BlitzPointer_GetFunctionPointer();

DLL_EXPORT uint32_t BlitzPointer_CallFunction0(uint32_t fpFunctionPointer);
DLL_EXPORT uint32_t BlitzPointer_CallFunction1(uint32_t fpFunctionPointer, uint32_t p1);
DLL_EXPORT uint32_t BlitzPointer_CallFunction2(uint32_t fpFunctionPointer, uint32_t p1, uint32_t p2);
DLL_EXPORT uint32_t BlitzPointer_CallFunction3(uint32_t fpFunctionPointer, uint32_t p1, uint32_t p2, uint32_t p3);
DLL_EXPORT uint32_t BlitzPointer_CallFunction4(uint32_t fpFunctionPointer, uint32_t p1, uint32_t p2, uint32_t p3, uint32_t p4);
DLL_EXPORT uint32_t BlitzPointer_CallFunctionS0(uint32_t fpFunctionPointer);
DLL_EXPORT uint32_t BlitzPointer_CallFunctionS1(uint32_t fpFunctionPointer, uint32_t p1);
DLL_EXPORT uint32_t BlitzPointer_CallFunctionS2(uint32_t fpFunctionPointer, uint32_t p1, uint32_t p2);
DLL_EXPORT uint32_t BlitzPointer_CallFunctionS3(uint32_t fpFunctionPointer, uint32_t p1, uint32_t p2, uint32_t p3);
DLL_EXPORT uint32_t BlitzPointer_CallFunctionS4(uint32_t fpFunctionPointer, uint32_t p1, uint32_t p2, uint32_t p3, uint32_t p4);