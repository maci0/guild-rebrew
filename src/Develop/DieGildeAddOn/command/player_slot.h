#ifndef PLAYER_SLOT_H
#define PLAYER_SLOT_H

/* Connection/player table row (SIZE 0x264264): `flags` at offset 0 and
 * `data` at 0x264204.  Do not merge with game_structs.h PlayerSlot
 * (data at offset 8). */
// SIZE 0x264264
typedef struct player_slot {
	int flags;
	char gap_0004[0x264200];
	int data;
	char gap_264208[0x5c];
} player_slot;

#endif /* PLAYER_SLOT_H */
