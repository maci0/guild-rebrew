// FUNCTION: SERVER 0x10010390
// STATUS: STUB
// BLOCKER: comparison direction swap, jump condition swap, zero-extend pattern (xor vs mov)
// ORIGIN: GAME
// SIZE: 262
// CFLAGS: /O2 /Gd
// SYMBOL: _SimSpecialAction
// BLOCKER_DELTA: 205

#ifdef __clang__
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wint-to-void-pointer-cast"
#endif

/*
// BLOCKER_DELTA: 215
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 262B
 *    CFlags: 
 *    Symbol: _SimSpecialAction
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl SimSpecialAction(int param_1,char *param_2)
 * 
 * {
 *   SRC *src;
 *   uint uVar1;
 *   char *p;
 *   int iVar2;
 *   
 *   p = (char *)LookupEntityRecordById(*(int *)(param_1 + 0x14));
 *   if (p == (char *)0x0) {
 *     return -1;
 *   }
 *   iVar2 = check_flag(p);
 *   if (iVar2 == 0) {
 *     return -2;
 *   }
 *   uVar1 = *(uint *)(param_1 + 0x10);
 *   src = (SRC *)(param_1 + 0x10);
 *   if (uVar1 < 0x61536d54) {
 *     if (uVar1 == 0x61536d53) {
 *       ClampFloatValue((int)src,*(int *)(*(int *)(p + 0x16c) + 0x65));
 *       return 0;
 *     }
 *     if (uVar1 == 0x46697245) {
 *       FireEntityAndCleanup((int)src,*(int **)(*(int *)(p + 0x16c) + 0x65),*(int *)(p + 0x16c));
 *       return 0;
 *     }
 *     if (uVar1 == 0x61437353) {
 *       ApplyColorComponent((char *)src,*(char **)(*(int *)(p + 0x16c) + 0x65));
 *       return 0;
 *     }
 *     if (uVar1 == 0x61535263) {
 *       search_and_set(src,*(TGT **)(*(int *)(p + 0x16c) + 0x65));
 *       return 0;
 *     }
 *   }
 *   else {
 *     if (uVar1 == 0x61616452) {
 *       AllocateEntitySlot((int)src,*(int *)(*(int *)(p + 0x16c) + 0x65),*(int *)(p + 0x16c));
 *       return 0;
 *     }
 *     if (uVar1 == 0x61736452) {
 */

typedef unsigned int uint;

extern void* __cdecl LookupEntityRecordById(int);
extern int __cdecl func_1000bda0(void*);
extern void __cdecl func_1000c380(void*, void*);
extern void __cdecl func_1000c1e0(void*, void*);
extern void __cdecl func_1000c420(void*, void*, void*);
extern void __cdecl func_1000c3c0(void*, void*);
extern void __cdecl func_1000c310(void*, void*, void*);
extern void __cdecl func_1000c280(void*, void*, void*);

int __cdecl SimSpecialAction(int param_1, char* param_2)
{
	char* p;
	uint uVar1;
	char* src;
	int iVar2;

	(void) param_2;
	p = (char*) LookupEntityRecordById(*(int*) (param_1 + 0x14));
	if (p == (char*) 0) {
		return -1;
	}
	iVar2 = func_1000bda0(p);
	if (iVar2 == 0) {
		return -2;
	}
	uVar1 = *(uint*) (param_1 + 0x10);
	src = (char*) (param_1 + 0x10);
	if (uVar1 < 0x61536d54) {
		if (uVar1 == 0x61536d53) {
			func_1000c3c0(src, *(char**) (*(int*) (p + 0x16c) + 0x65));
			return 0;
		}
		if (uVar1 == 0x46697245) {
			func_1000c420(src, *(char**) (*(int*) (p + 0x16c) + 0x65), *(char**) (p + 0x16c));
			return 0;
		}
		if (uVar1 == 0x61437353) {
			func_1000c1e0(src, *(char**) (*(int*) (p + 0x16c) + 0x65));
			return 0;
		}
		if (uVar1 == 0x61535263) {
			func_1000c380(src, *(char**) (*(int*) (p + 0x16c) + 0x65));
			return 0;
		}
	}
	else {
		if (uVar1 == 0x61616452) {
			func_1000c280(src, *(char**) (*(int*) (p + 0x16c) + 0x65), *(char**) (p + 0x16c));
			return 0;
		}
		if (uVar1 == 0x61736452) {
			func_1000c310(src, *(char**) (*(int*) (p + 0x16c) + 0x65), *(char**) (p + 0x16c));
			return 0;
		}
	}
	return -3;
}
