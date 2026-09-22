#ifndef PLAYER_SLOT_H
#define PLAYER_SLOT_H

/* Connection/player table row with `data` at 0x264204 (SIZE 0x264264).
 * Shared by cm_ExAllocRaum.c and cm_ExCreateGeb.c. Do not include from
 * command_internal.h: cm_ExSetSyncFlags.c uses a different layout
 * (`flags` at offset 0). Do not merge with game_structs.h PlayerSlot
 * (data at offset 8). */
// SIZE 0x264264
typedef struct player_slot {
	char gap_0000[0x264204];
	int data;
	char gap_264208[0x5c];
} player_slot;

#endif /* PLAYER_SLOT_H */
