
#include "../command_internal.h"
#include "../../../Units/Error/error.h"


extern char s_cm_ExClearLagerslot___Invalid__L_1002d088[];
extern char s_cm_ExClearLagerslot___Lager_has_n_1002d054[];
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
int __cdecl gm_RemoveObjectByType(void**, unsigned int);

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 191B
 *    CFlags: 
 *    Symbol: _cm_ExClearLagerslot
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ExClearLagerslot(short *param_1,uchar *param_2)
 * 
 * {
 *   short *psVar1;
 *   int iVar2;
 *   ushort *puVar3;
 *   uint line;
 *   char *msg;
 *   
 *   psVar1 = param_1;
 *   iVar2 = gm_GetFieldByType((char *)param_1,*(int *)(param_1 + 8));
 *   *(int *)(psVar1 + 8) = iVar2;
 *   iVar2 = gm_ResolveEntityById((void **)0x0,&param_1,(void **)0x0,iVar2);
 *   if (iVar2 == 0) {
 *     msg = s_cm_ExClearLagerslot___Invalid__L_1002d088;
 *     line = 0x314b;
 *   }
 *   else {
 *     if ((*param_1 == 0x2a) || (*param_1 == 0x116)) {
 *       puVar3 = gm_StartEntityQuery(*(int *)(param_1 + 10),1,0,(uint)(ushort)psVar1[10]);
 *       if (puVar3 == (ushort *)0x0) {
 *         return 1;
 *       }
 *       if (*(int *)(puVar3 + 7) != 1) {
 *         return 1;
 *       }
 *       gm_RemoveObjectByType((char **)(param_1 + 10),(uint)(ushort)psVar1[10]);
 *       if (param_2 != (uchar *)0x0) {
 *         *param_2 = '\x01';
 *       }
 *       return 0;
 *     }
 *     msg = s_cm_ExClearLagerslot___Lager_has_n_1002d054;
 *     line = 0x3155;
 *   }
 *   LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,line,msg,1);
 *   return 1;
 * }
 */

// FUNCTION: SERVER 0x1000e690
int __cdecl cm_ExClearLagerslot(short* param_1, uchar* param_2)
{
	short* cmd;
	int field;
	ushort* query;

	cmd = param_1;
	field = gm_GetFieldByType((char*) param_1, *(int*) (param_1 + 8));
	*(int*) (cmd + 8) = field;
	if (gm_ResolveEntityById((void**) 0x0, (void**) &param_1, (void**) 0x0, field) == 0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x314b,
			s_cm_ExClearLagerslot___Invalid__L_1002d088,
			1
		);
		return 1;
	}

	if ((*param_1 != 0x2a) && (*param_1 != 0x116)) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x3155,
			s_cm_ExClearLagerslot___Lager_has_n_1002d054,
			1
		);
		return 1;
	}

	query = gm_StartEntityQuery(*(int*) (param_1 + 10), 1, 0, (uint) (ushort) cmd[10]);
	if (query == (ushort*) 0x0) {
		return 1;
	}
	if (*(int*) (query + 7) != 1) {
		return 1;
	}

	gm_RemoveObjectByType((char**) (param_1 + 10), (uint) (ushort) cmd[10]);
	if (param_2 != (uchar*) 0x0) {
		*param_2 = '\x01';
	}
	return 0;
}
