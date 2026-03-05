// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 239
// BLOCKER: instruction folding (lea vs mov), jump condition swap, loop rotation / branch layout, stack frame choice (push vs sub esp), zero-extend pattern (xor vs mov)
// BLOCKER_DELTA: 226

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

#include "../command_internal.h"
#include "../../../Units/Error/error.h"


extern char s_cm_ExSetAttribute___Invalid_Id_1002d0d4[];

// FUNCTION: SERVER 0x1000e8d0
int __cdecl cm_ExSetAttribute(int param_1, char* param_2)
{
	int fieldSize;
	int cmdBase;
	int resolveResult;
	char* srcPtr;
	char* dstPtr;
	uint fieldIdx;
	void* objectEntity;
	void* dynEntity;

	cmdBase = param_1;
	resolveResult = gm_GetFieldByType((char*)param_1, *(int*)(param_1 + 0x10));
	*(int*)(cmdBase + 0x10) = resolveResult;
	resolveResult = gm_ResolveEntityById((void**)&param_1, &objectEntity, &dynEntity, resolveResult);
	if (resolveResult == 0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x32ed,
			s_cm_ExSetAttribute___Invalid_Id_1002d0d4,
			1
		);
		return 1;
	}
	if ((param_1 == 0) && (param_1 = (int)objectEntity, objectEntity == (void*)0x0)) {
		param_1 = (int)dynEntity;
	}
	fieldIdx = 0;
	srcPtr = (char*)(cmdBase + 0x15);
	if (*(uchar*)(cmdBase + 0x14) != 0) {
		do {
			fieldSize = (int)*(signed char*)srcPtr;
			resolveResult = (int)*(signed char*)(srcPtr + 1);
			srcPtr = srcPtr + 2;
			dstPtr = (char*)((uint)*(ushort*)srcPtr + (uint)param_1);
			srcPtr = srcPtr + 2;
			if (fieldSize == 1) {
				for (; resolveResult != 0; resolveResult--) {
					*dstPtr = *srcPtr;
					dstPtr++;
					srcPtr++;
				}
			} else if (fieldSize == 2) {
				for (; resolveResult != 0; resolveResult--) {
					*(short*)dstPtr = *(short*)srcPtr;
					srcPtr += 2;
					dstPtr += 2;
				}
			} else if (fieldSize == 4) {
				for (; resolveResult != 0; resolveResult--) {
					*(int*)dstPtr = *(int*)srcPtr;
					srcPtr += 4;
					dstPtr += 4;
				}
			}
			fieldIdx++;
		} while (fieldIdx < *(uchar*)(cmdBase + 0x14));
	}
	if (param_2 != (char*)0) {
		*param_2 = '\x01';
	}
	return 0;
}
