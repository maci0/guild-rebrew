
/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 153B
 *    CFlags: 
 *    Symbol: _CmdCreateBuilding
 *    Files: DieGildeAddOn/command/command.c * / * 
 * int __cdecl cm_ExCreateGeb(int cmd,char *result)
 * 
 * {
 *   undefined2 *puVar1;
 *   undefined2 extraout_var;
 *   uint line;
 *   char *pcVar2;
 *   
 *   puVar1 = (undefined2 *)gm_LookupEntityRecordById(*(int *)(cmd + 0x10));
 *   if (puVar1 == (undefined2 *)0x0) {
 *     pcVar2 = s_cm_ExCreateGeb____Could_not_find_1002d41c;
 *     line = 0x5386;
 *   }
 *   else {
 *     *(undefined4 *)(cmd + 0x14) = g_timestamp_0b6c;
 *     pcVar2 = gm_AllocGebaeude(CONCAT31((int3)((uint)puVar1 >> 8),*(undefined1 *)(cmd + 0x18)),
 *                            CONCAT22(extraout_var,*puVar1));
 *     if (pcVar2 != (char *)0x0) {
 *       *(undefined4 *)(g_player_slot_0[*(byte *)(cmd + 3)].data + 0x2641fc) =
 *            *(undefined4 *)(pcVar2 + 1);
 *       if (result != (char *)0x0) {
 *         *result = '\x01';
 *         result[1] = '\x02';
 *         *(char **)(result + 6) = pcVar2;
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
#include "../../../Units/Error/error.h"

// SIZE 0x264264
typedef struct player_slot {
	char gap_0000[0x2641fc];
	int data;
	char gap_264200[0x64];
} player_slot;

char* __cdecl gm_AllocGebaeude(unsigned char, unsigned short);
extern player_slot g_player_slot_0[];

extern char s_cm_ExCreateGeb____Could_not_find_1002d41c[];
extern char s_cm_ExCreateGeb____failed_1002d400[];

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#endif

/* Execution handler: creates a new building (Gebaeude) entity
 * via gm_AllocGebaeude and initializes its owner and type. */

// FUNCTION: SERVER 0x1000fb30
int __cdecl cm_ExCreateGeb(int cmd, char* result)
{
	unsigned short* owner_record;
	char* building;

	owner_record = (unsigned short*) gm_LookupEntityRecordById(*(int*) (cmd + 0x10));
	if (owner_record == (unsigned short*) 0) {
		LogMessageInternal(
			s_D__Develop_DieGildeAddOn_command_1002c748,
			0x5386,
			s_cm_ExCreateGeb____Could_not_find_1002d41c,
			1
		);
		return 1;
	}

	*(int*) (cmd + 0x14) = g_timestamp_0b6c;
	building = gm_AllocGebaeude(*(unsigned char*) (cmd + 0x18), *owner_record);
	if (building == (char*) 0) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x539e, s_cm_ExCreateGeb____failed_1002d400, 1);
		return 1;
	}

	g_player_slot_0[(unsigned int) *(unsigned char*) (cmd + 3)].data = *(int*) (building + 1);
	if (result != (char*) 0) {
		*result = '\x01';
		result[1] = '\x02';
		*(char**) (result + 6) = building;
	}

	return 0;
}

#ifdef __clang__
#pragma clang diagnostic pop
#endif
