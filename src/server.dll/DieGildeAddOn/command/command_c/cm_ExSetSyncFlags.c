
/*
 * Ghidra decompilation reference:
 * /+ WARNING: Globals starting with '_' overlap smaller symbols at the same address * / * / * [rebrew] FUNCTION: RELOC
 *    Origin: GAME
 *    Size: 122B
 *    CFlags:
 *    Symbol: _SetSyncFlags
 *    Files: DieGildeAddOn/command/command.c * /
 *
 * int __cdecl cm_ExSetSyncFlags(int cmd,char *result)
 *
 * {
 *   if (*(char *)(cmd + 0x10) == '\x01') {
 *     g_connections[*(byte *)(cmd + 3)].flags =
 *          g_connections[*(byte *)(cmd + 3)].flags | 0x20;
 *   }
 *   if (*(char *)(cmd + 0x10) == '\x0e') {
 *     g_connections[*(byte *)(cmd + 3)].flags =
 *          g_connections[*(byte *)(cmd + 3)].flags | 0x40;
 *   }
 *   if (*(char *)(cmd + 0x10) == '\x12') {
 *     g_game_speed_index = *(int *)(cmd + 0x11);
 *     if (3 < g_game_speed_index) {
 *       g_game_speed_index = 4;
 *     }
 *     g_game_speed_value = *(undefined4 *)(&g_game_speed_table + g_game_speed_index * 4);
 *   }
 *   return 0;
 * }
 */

// SIZE 0x264264
typedef struct player_slot {
	int flags;
	char gap_0004[0x264260];
} player_slot;

extern unsigned char g_connections[];
extern int g_game_speed_index;
extern int g_game_speed_value;
extern int g_game_speed_table[];

/* Execution handler: sets synchronization flags on a player slot.
 * Handles three flag types: 0x01 (sets flag 0x20), 0x0e (sets
 * flag 0x40), 0x12 (sets game speed from g_game_speed_table). */

// FUNCTION: SERVER 0x1000efb0
int __cdecl cm_ExSetSyncFlags(int cmd, char* result)
{
	int speed_index;

	if (*(char*) (cmd + 0x10) == '\x01') {
		((player_slot*) g_connections)[*(unsigned char*) (cmd + 3)].flags =
			((player_slot*) g_connections)[*(unsigned char*) (cmd + 3)].flags | 0x20;
	}
	if (*(char*) (cmd + 0x10) == '\x0e') {
		((player_slot*) g_connections)[*(unsigned char*) (cmd + 3)].flags =
			((player_slot*) g_connections)[*(unsigned char*) (cmd + 3)].flags | 0x40;
	}
	if (*(char*) (cmd + 0x10) == '\x12') {
		speed_index = *(int*) (cmd + 0x11);
		if (4 <= speed_index) {
			speed_index = 4;
		}
		g_game_speed_value = g_game_speed_table[speed_index];
		g_game_speed_index = speed_index;
	}
	return 0;
}
