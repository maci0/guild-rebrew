// STATUS: MATCHING
// BLOCKER: instruction folding (lea vs mov), stack frame choice (push vs sub esp)
// ORIGIN: GAME
// SIZE: 144

/*
// BLOCKER_DELTA: 126
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 135B
 *    CFlags: 
 *    Symbol: _ExSetEntityField
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ExChangeFloat(int param_1,char *param_2)
 * 
 * {
 *   int iVar1;
 *   int iVar2;
 *   void *pvStack_8;
 *   void *pvStack_4;
 *   
 *   iVar1 = param_1;
 *   iVar2 = gm_GetFieldByType((char *)param_1,*(int *)(param_1 + 0x10));
 *   *(int *)(iVar1 + 0x10) = iVar2;
 *   iVar2 = gm_ResolveEntityById(&pvStack_4,&pvStack_8,(void **)&param_1,iVar2);
 *   if (iVar2 == 0) {
 *     LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x347f,
 *                        s_cm_ExChangeFloat___Invalid_Id_1002d134,1);
 *     return 1;
 *   }
 *   if ((param_1 == 0) && (param_1 = (int)pvStack_8, pvStack_8 == (void *)0x0)) {
 *     param_1 = (int)pvStack_4;
 *   }
 *   *(float *)(param_1 + *(int *)(iVar1 + 0x14)) =
 *        *(float *)(iVar1 + 0x18) + *(float *)(param_1 + *(int *)(iVar1 + 0x14));
 *   if (param_2 != (char *)0x0) {
 *     *param_2 = '\x01';
 *   }
 *   return 0;
 * }
 */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"


extern char s_cm_ExChangeFloat___Invalid_Id_1002d134[];

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

// FUNCTION: SERVER 0x1000eb70
int __cdecl cm_ExChangeFloat(int param_1, char* param_2)
{
	int cmd;
	int resolve_ok;
	void* secondary;
	void* primary;

	cmd = param_1;
	resolve_ok = gm_GetFieldByType((char*) param_1, *(int*) (param_1 + 0x10));
	*(int*) (cmd + 0x10) = resolve_ok;
	resolve_ok = gm_ResolveEntityById(&primary, &secondary, (void**) &param_1, resolve_ok);
	if (resolve_ok == 0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x347f,
			s_cm_ExChangeFloat___Invalid_Id_1002d134,
			1
		);
		return 1;
	}
	if ((param_1 == 0) && (param_1 = (int) secondary, secondary == (void*) 0)) {
		param_1 = (int) primary;
	}
	*(float*) (param_1 + *(int*) (cmd + 0x14)) =
		*(float*) (cmd + 0x18) + *(float*) (param_1 + *(int*) (cmd + 0x14));
	if (param_2 != (char*) 0) {
		*param_2 = '\x01';
	}
	return 0;
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif

