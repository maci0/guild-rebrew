// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 153

/*
// BLOCKER_DELTA: 125
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 153B
 *    CFlags: 
 *    Symbol: _CmdCreateBuilding
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ExCreateGeb(int param_1,char *param_2)
 * 
 * {
 *   undefined2 *puVar1;
 *   undefined2 extraout_var;
 *   uint line;
 *   char *pcVar2;
 *   
 *   puVar1 = (undefined2 *)LookupEntityRecordById(*(int *)(param_1 + 0x10));
 *   if (puVar1 == (undefined2 *)0x0) {
 *     pcVar2 = s_cm_ExCreateGeb____Could_not_find_1002d41c;
 *     line = 0x5386;
 *   }
 *   else {
 *     *(undefined4 *)(param_1 + 0x14) = g_timestamp_0b6c;
 *     pcVar2 = AllocGebaeude(CONCAT31((int3)((uint)puVar1 >> 8),*(undefined1 *)(param_1 + 0x18)),
 *                            CONCAT22(extraout_var,*puVar1));
 *     if (pcVar2 != (char *)0x0) {
 *       *(undefined4 *)(g_player_slot_0[*(byte *)(param_1 + 3)].data + 0x2641fc) =
 *            *(undefined4 *)(pcVar2 + 1);
 *       if (param_2 != (char *)0x0) {
 *         *param_2 = '\x01';
 *         param_2[1] = '\x02';
 *         *(char **)(param_2 + 6) = pcVar2;
 *       }
 *       return 0;
 *     }
 *     pcVar2 = s_cm_ExCreateGeb____failed_1002d400;
 *     line = 0x539e;
 *   }
 *   LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,line,pcVar2,1);
 *   return 1;
 * }
 */

#include "../command_internal.h"

typedef struct player_slot {
	char gap_0000[0x2641fc];
	int data;
	char gap_264200[0x64];
} player_slot;

extern char* __cdecl AllocGebaeude(unsigned char, unsigned short);
extern void __cdecl LogMessageInternal(char*, int, char*, int);
extern player_slot g_player_slot_0[];

extern char s_cm_ExCreateGeb____Could_not_find_1002d41c[];
extern char s_cm_ExCreateGeb____failed_1002d400[];

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#endif

// FUNCTION: SERVER 0x1000fb30
int __cdecl cm_ExCreateGeb(int param_1, char* param_2)
{
	unsigned short* puVar1;
	char* pcVar2;

	puVar1 = (unsigned short*) LookupEntityRecordById(*(int*) (param_1 + 0x10));
	if (puVar1 == (unsigned short*) 0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x5386,
			s_cm_ExCreateGeb____Could_not_find_1002d41c,
			1
		);
		return 1;
	}

	*(int*) (param_1 + 0x14) = g_timestamp_0b6c;
	pcVar2 = AllocGebaeude(*(unsigned char*) (param_1 + 0x18), *puVar1);
	if (pcVar2 == (char*) 0) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x539e, s_cm_ExCreateGeb____failed_1002d400, 1);
		return 1;
	}

	g_player_slot_0[(unsigned int) *(unsigned char*) (param_1 + 3)].data = *(int*) (pcVar2 + 1);
	if (param_2 != (char*) 0) {
		*param_2 = '\x01';
		param_2[1] = '\x02';
		*(char**) (param_2 + 6) = pcVar2;
	}

	return 0;
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif
