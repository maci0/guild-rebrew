
/*
 * Conversion note: the 7-byte payload copy (cmd+0x18 -> obj+0x1c) must be
 * written as memcpy(dst, src, 7).  MSVC6 /O2 expands the inline memcpy to
 * dword+word+byte stores and materializes the dst base (lea ecx,[esi+0x1c])
 * and the adjusted src base (add edi,0x18), byte-matching the reference.
 * Plain field-by-field pointer stores get folded back to base+offset
 * addressing (168B vs 172B) or flip the esi/edi allocation.
 *
 * Ghidra decompilation reference:
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

extern char s_cm_ExAllocThemaPredigt____Execut_1002d184[];
char* __cdecl gm_AllocObjekt(int, int, int);

/* Execution handler: allocates a sermon theme (Thema Predigt)
 * for a church/religious building entity. */

// CFLAGS: /O2 /Gd
// FUNCTION: SERVER 0x1000f2f0
int __cdecl cm_ExAllocThemaPredigt(int cmd, char* result)
{
	int field;
	char* obj;
	char* dst;
	uint f;

	*(int*) (cmd + 0x10) = g_timestamp_0b6c;
	field = gm_GetFieldByType((char*) cmd, *(int*) (cmd + 0x14));
	*(int*) (cmd + 0x14) = field;
	obj = gm_AllocObjekt(field, 0x1b5, 1);
	if (obj == 0) {
		return 1;
	}
	f = 0x99099 * (unsigned char) *(char*) (cmd + 3);
	cmd += 0x18;
	dst = obj + 0x1c;
	*(int*) (0x10442d08 + f * 4) = *(int*) (obj + 2);
	obj[0x12] = 0x40;
	memcpy(dst, cmd, 7);
	obj[0x22] = 0;
	LogMessageInternal((char*) 0x1002c748, 0x40db,
	                   s_cm_ExAllocThemaPredigt____Execut_1002d184, 1);
	if (result != 0) {
		*result = 1;
		result[1] = 3;
		*(char**) (result + 6) = obj;
	}
	return 0;
}
