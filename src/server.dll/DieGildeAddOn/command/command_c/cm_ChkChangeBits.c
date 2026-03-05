// STATUS: MATCHING
// BLOCKER: instruction folding (lea vs mov), jump condition swap, stack frame choice (push vs sub esp)
// ORIGIN: GAME
// SIZE: 162

/*
// BLOCKER_DELTA: 152
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 162B
 *    CFlags: 
 *    Symbol: _CheckChangeBits
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ChkChangeBits(int param_1,char *param_2)
 * 
 * {
 *   int iVar1;
 *   int iVar2;
 *   void *pvVar3;
 *   uint line;
 *   char *msg;
 *   void *local_8;
 *   void *local_4;
 *   
 *   iVar1 = param_1;
 *   iVar2 = get_field_by_type((char *)param_1,*(int *)(param_1 + 0x10));
 *   *(int *)(iVar1 + 0x10) = iVar2;
 *   iVar2 = ResolveEntityById((void **)&param_1,&local_4,&local_8,iVar2);
 *   if (iVar2 == 0) {
 *     msg = s_cm_ChkChangeBits___Invalid_Id_1002ca54;
 *     line = 0x250d;
 *   }
 *   else {
 *     pvVar3 = (void *)param_1;
 *     if ((param_1 == 0) && (pvVar3 = local_4, local_4 == (void *)0x0)) {
 *       pvVar3 = local_8;
 *     }
 *     if ((((local_8 == (void *)0x0) ||
 *          ((uint *)(*(int *)(iVar1 + 0x14) + (int)pvVar3) != (uint *)((int)local_8 + 0x1c8))) ||
 *         ((*(uint *)(iVar1 + 0x1c) & 0x800000) == 0)) ||
 *        ((*(uint *)((int)local_8 + 0x1c8) & 0x800000) == 0)) {
 *       return 0;
 *     }
 *     msg = s_cm_ChkChangeBits___Invalid_actio_1002ca04;
 *     line = 0x2533;
 *   }
 *   LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,line,msg,1);
 *   return 1;
 * }
 */

#include "../command_internal.h"

extern void __cdecl LogMessageInternal(char*, int, char*, int);

extern char s_cm_ChkChangeBits___Invalid_Id_1002ca54[];
extern char s_cm_ChkChangeBits___Invalid_actio_1002ca04[];

// FUNCTION: SERVER 0x1000cf30
int __cdecl cm_ChkChangeBits(int param_1, char* param_2)
{
	int cmd;
	int field;
	int ref;
	void* secondary;
	void* tertiary;

	cmd = param_1;
	field = get_field_by_type((char*) param_1, *(int*) (param_1 + 0x10));
	*(int*) (cmd + 0x10) = field;
	if (ResolveEntityById((void**) &param_1, &secondary, &tertiary, field) == 0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x250d,
			s_cm_ChkChangeBits___Invalid_Id_1002ca54,
			1
		);
		return 1;
	}

	ref = (int) param_2;
	if (ref == 0) {
		ref = (int) secondary;
		if (ref == 0) {
			ref = param_1;
		}
	}

	if (param_1 == 0) {
		return 0;
	}
	if (*(int*) (cmd + 0x14) + ref != param_1 + 0x1c8) {
		return 0;
	}
	if ((*(unsigned int*) (cmd + 0x1c) & 0x800000) == 0) {
		return 0;
	}
	if ((*(unsigned int*) (param_1 + 0x1c8) & 0x800000) == 0) {
		return 0;
	}

	LogMessageInternal(
		s_D__Develop_DieGildeAddOn_command_1002c748,
		0x2533,
		s_cm_ChkChangeBits___Invalid_actio_1002ca04,
		1
	);
	return 1;
}
