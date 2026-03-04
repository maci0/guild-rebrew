#ifndef GAME_STRUCTS_H
#define GAME_STRUCTS_H

#include "game_common.h"

/* --- Core Game Structures --- */

/* Command Packet used for network synchronization */
typedef struct CommandPacket {
    unsigned int total_length;
    unsigned int player_slot_id;
    unsigned char command_id;
    unsigned char payload[82];
} CommandPacket;

/* Player Slot structure - handles player state and data */
typedef struct PlayerSlot {
    unsigned int flags;
    unsigned int id;
    unsigned char data[0x26425C]; /* Total size 0x264264 */
} PlayerSlot;

#endif /* GAME_STRUCTS_H */
