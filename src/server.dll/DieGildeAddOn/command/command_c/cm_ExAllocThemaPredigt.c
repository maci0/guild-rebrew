// STATUS: MATCHING
// BLOCKER: register base adjustment (target uses add edi,0x18 and lea ecx,[esi+0x1c] for shorter addressing; MSVC6 folds to base+offset)
// ORIGIN: GAME
// SIZE: 172

/*
 * BLOCKER_DELTA: 4
 * Ghidra decompilation reference (sizeInBytes=1 BROKEN, use rebrew asm):
 *
 * Target uses add edi,0x18 to adjust param_1 base for 7-byte copy
 * (saves 1 byte per source read) and lea ecx,[esi+0x1c] to create
 * dst pointer (saves 1 byte per dest write). MSVC6 /O2 folds these
 * optimizations back to base+offset addressing, producing 168B vs
 * 172B. Adding param_1 += 0x18 generates the add instruction but
 * causes esi/edi register allocation swap. Dead store preserved via
 * dst pointer alias hiding (dst[6] vs pcVar2[0x22]).
 *
 * int __cdecl cm_ExAllocThemaPredigt(int param_1,char *param_2)
 *
 * {
 *   int iVar1;
 *   char *pcVar2;
 *
 *   *(undefined4 *)(param_1 + 0x10) = g_timestamp_0b6c;
 *   iVar1 = gm_GetFieldByType((char *)param_1,*(int *)(param_1 + 0x14));
 *   *(int *)(param_1 + 0x14) = iVar1;
 *   pcVar2 = gm_AllocObjekt(iVar1,0x1b5,1);
 *   if (pcVar2 == (char *)0x0) {
 *     return 1;
 *   }
 *   *(undefined4 *)(g_player_slot_0[*(byte *)(param_1 + 3)].data + 0x264200) =
 *        *(undefined4 *)(pcVar2 + 2);
 *   pcVar2[0x12] = '@';
 *   *(undefined4 *)(pcVar2 + 0x1c) = *(undefined4 *)(param_1 + 0x18);
 *   *(undefined2 *)(pcVar2 + 0x20) = *(undefined2 *)(param_1 + 0x1c);
 *   pcVar2[0x22] = *(char *)(param_1 + 0x1e);
 *   pcVar2[0x22] = '\0';
 *   LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x40db,
 *                      s_cm_ExAllocThemaPredigt____Execut_1002d184,1);
 *   if (param_2 != (char *)0x0) {
 *     *param_2 = '\x01';
 *     param_2[1] = '\x03';
 *     *(char **)(param_2 + 6) = pcVar2;
 *   }
 *   return 0;
 * }
*/

#include "../command_internal.h"
#include "../../../Units/Error/error.h"


extern char g_player_slot_0[];
extern char s_cm_ExAllocThemaPredigt____Execut_1002d184[];
char* __cdecl gm_AllocObjekt(int, int, int);

// FUNCTION: SERVER 0x1000f2f0
int __cdecl cm_ExAllocThemaPredigt(int param_1, char* param_2)
{
	int field_id;
	char* obj;
	char* dst;

	*(int*) (param_1 + 0x10) = g_timestamp_0b6c;
	field_id = gm_GetFieldByType((char*) param_1, *(int*) (param_1 + 0x14));
	*(int*) (param_1 + 0x14) = field_id;
	obj = gm_AllocObjekt(field_id, 0x1b5, 1);
	if (obj == (char*) 0) {
		return 1;
	}
	*(int*) (g_player_slot_0 + (unsigned int) *(unsigned char*) (param_1 + 3) * 0x264264 + 0x264200) =
		*(int*) (obj + 2);
	obj[0x12] = '@';
	dst = obj + 0x1c;
	*(int*) dst = *(int*) (param_1 + 0x18);
	*(unsigned short*) (dst + 4) = *(unsigned short*) (param_1 + 0x1c);
	dst[6] = *(char*) (param_1 + 0x1e);
	obj[0x22] = '\0';
	LogMessageInternal(
		s_D__Develop_DieGildeAddOn_command_1002c748,
		0x40db,
		s_cm_ExAllocThemaPredigt____Execut_1002d184,
		1
	);
	if (param_2 != (char*) 0) {
		*param_2 = '\x01';
		param_2[1] = '\x03';
		*(char**) (param_2 + 6) = obj;
	}
	return 0;
}
