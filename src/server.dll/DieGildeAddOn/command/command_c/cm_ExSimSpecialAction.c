// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 262
// BLOCKER_DELTA: 205

#include "../command_internal.h"

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
 * int __cdecl cm_ExSimSpecialAction(int param_1,char *param_2)
 * 
 * {
 *   SRC *src;
 *   uint uVar1;
 *   char *p;
 *   int iVar2;
 *   
 *   p = (char *)gm_LookupEntityRecordById(*(int *)(param_1 + 0x14));
 *   if (p == (char *)0x0) {
 *     return -1;
 *   }
 *   iVar2 = ahm_CheckFlag(p);
 *   if (iVar2 == 0) {
 *     return -2;
 *   }
 *   uVar1 = *(uint *)(param_1 + 0x10);
 *   src = (SRC *)(param_1 + 0x10);
 *   if (uVar1 < 0x61536d54) {
 *     if (uVar1 == 0x61536d53) {
 *       ahm_ClampFloatValue((int)src,*(int *)(*(int *)(p + 0x16c) + 0x65));
 *       return 0;
 *     }
 *     if (uVar1 == 0x46697245) {
 *       ahm_FireEntityAndCleanup((int)src,*(int **)(*(int *)(p + 0x16c) + 0x65),*(int *)(p + 0x16c));
 *       return 0;
 *     }
 *     if (uVar1 == 0x61437353) {
 *       ahm_ApplyColorComponent((char *)src,*(char **)(*(int *)(p + 0x16c) + 0x65));
 *       return 0;
 *     }
 *     if (uVar1 == 0x61535263) {
 *       ahm_SearchAndSet(src,*(TGT **)(*(int *)(p + 0x16c) + 0x65));
 *       return 0;
 *     }
 *   }
 *   else {
 *     if (uVar1 == 0x61616452) {
 *       ahm_AllocateEntitySlot((int)src,*(int *)(*(int *)(p + 0x16c) + 0x65),*(int *)(p + 0x16c));
 *       return 0;
 *     }
 *     if (uVar1 == 0x61736452) {
 */

int __cdecl ahm_CheckFlag(void*);
void __cdecl ahm_SearchAndSet(void*, void*);
void __cdecl ahm_ApplyColorComponent(void*, void*);
void __cdecl ahm_FireEntityAndCleanup(void*, void*, void*);
void __cdecl ahm_ClampFloatValue(void*, void*);
void __cdecl ahm_SlotClearMatch(void*, void*, void*);
void __cdecl ahm_AllocateEntitySlot(void*, void*, void*);

// FUNCTION: SERVER 0x10010390
int __cdecl cm_ExSimSpecialAction(int param_1, char* param_2)
{
	char* p;
	uint action_type;
	char* src;
	int flag_ok;

	(void) param_2;
	p = (char*) gm_LookupEntityRecordById(*(int*) (param_1 + 0x14));
	if (p == (char*) 0) {
		return -1;
	}
	flag_ok = ahm_CheckFlag(p);
	if (flag_ok == 0) {
		return -2;
	}
	action_type = *(uint*) (param_1 + 0x10);
	src = (char*) (param_1 + 0x10);
	switch (action_type) {
	case 0x61535263:
		ahm_SearchAndSet(src, *(char**) (*(int*) (p + 0x16c) + 0x65));
		return 0;
	case 0x61536d53:
		ahm_ClampFloatValue(src, *(char**) (*(int*) (p + 0x16c) + 0x65));
		return 0;
	case 0x46697245:
		ahm_FireEntityAndCleanup(src, *(char**) (*(int*) (p + 0x16c) + 0x65), *(char**) (p + 0x16c));
		return 0;
	case 0x61437353:
		ahm_ApplyColorComponent(src, *(char**) (*(int*) (p + 0x16c) + 0x65));
		return 0;
	case 0x61616452:
		ahm_AllocateEntitySlot(src, *(char**) (*(int*) (p + 0x16c) + 0x65), *(char**) (p + 0x16c));
		return 0;
	case 0x61736452:
		ahm_SlotClearMatch(src, *(char**) (*(int*) (p + 0x16c) + 0x65), *(char**) (p + 0x16c));
		return 0;
	default:
		return -3;
	}
}
