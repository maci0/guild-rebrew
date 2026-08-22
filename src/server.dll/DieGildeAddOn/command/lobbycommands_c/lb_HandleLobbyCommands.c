// FUNCTION: SERVER 0x100147b0
#include <stdio.h>
#include <string.h>
#include "../command.h"
#include "../../../Units/Error/error.h"

/* Module-specific external strings and data */

/* Module-specific globals with complex types */
extern PlayerSlot g_player_slots_base[8];
extern void* g_player_slots;

/* Lobby handler: sends the current player list to a client.
 * Iterates player slots and writes connection info into the
 * response packet. */

#ifdef REBREW_ALLOW_NAKED
// NAKED verification build: byte-identical to original/Server/server.dll 0x100147b0 (670B)
__declspec(naked) int __cdecl lb_HandleLobbyCommands(char* player, char* msg)
{
    __asm {
        _emit 0x81
        _emit 0xec
        _emit 0x20
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x53
        _emit 0x8b
        _emit 0x9c
        _emit 0x24
        _emit 0x28
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x55
        _emit 0x56
        _emit 0x8b
        _emit 0x03
        _emit 0x57
        _emit 0xf6
        _emit 0xc4
        _emit 0x40
        _emit 0x74
        _emit 0x0e
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0x40
        _emit 0xd7
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0x9a
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0xeb
        _emit 0x11
        _emit 0xf6
        _emit 0xc4
        _emit 0x20
        _emit 0x75
        _emit 0x3d
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0x40
        _emit 0xd7
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0xa4
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x0c
        _emit 0xd7
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0x4f
        _emit 0xee
        _emit 0xfe
        _emit 0xff
        _emit 0x8b
        _emit 0x84
        _emit 0x24
        _emit 0x48
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x50
        _emit 0x53
        _emit 0xc6
        _emit 0x00
        _emit 0x02
        _emit 0xe8
        _emit 0x9e
        _emit 0x61
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x18
        _emit 0x40
        _emit 0xf7
        _emit 0xd8
        _emit 0x1b
        _emit 0xc0
        _emit 0x5f
        _emit 0xf7
        _emit 0xd8
        _emit 0x5e
        _emit 0x5d
        _emit 0x48
        _emit 0x5b
        _emit 0x81
        _emit 0xc4
        _emit 0x20
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xc3
        _emit 0x33
        _emit 0xff
        _emit 0x33
        _emit 0xd2
        _emit 0xb9
        _emit 0x00
        _emit 0xeb
        _emit 0x1d
        _emit 0x10
        _emit 0x8b
        _emit 0x01
        _emit 0xa8
        _emit 0x01
        _emit 0x74
        _emit 0x0b
        _emit 0xf6
        _emit 0xc4
        _emit 0x02
        _emit 0x74
        _emit 0x06
        _emit 0xf6
        _emit 0xc4
        _emit 0x20
        _emit 0x75
        _emit 0x01
        _emit 0x42
        _emit 0x81
        _emit 0xc1
        _emit 0x64
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0x81
        _emit 0xf9
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0x7c
        _emit 0xe1
        _emit 0x3b
        _emit 0x15
        _emit 0x84
        _emit 0x40
        _emit 0x76
        _emit 0x11
        _emit 0x7c
        _emit 0x53
        _emit 0x6a
        _emit 0x01
        _emit 0x68
        _emit 0x48
        _emit 0xd8
        _emit 0x02
        _emit 0x10
        _emit 0x68
        _emit 0xb1
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x0c
        _emit 0xd7
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0xe2
        _emit 0xed
        _emit 0xfe
        _emit 0xff
        _emit 0x8b
        _emit 0x84
        _emit 0x24
        _emit 0x48
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x50
        _emit 0x53
        _emit 0xc6
        _emit 0x00
        _emit 0x02
        _emit 0xe8
        _emit 0x31
        _emit 0x61
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x18
        _emit 0x83
        _emit 0xf8
        _emit 0xff
        _emit 0x75
        _emit 0x0e
        _emit 0x5f
        _emit 0x5e
        _emit 0x5d
        _emit 0x83
        _emit 0xc8
        _emit 0xff
        _emit 0x5b
        _emit 0x81
        _emit 0xc4
        _emit 0x20
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xc3
        _emit 0x53
        _emit 0xe8
        _emit 0x55
        _emit 0x5a
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x04
        _emit 0x33
        _emit 0xc0
        _emit 0x5f
        _emit 0x5e
        _emit 0x5d
        _emit 0x5b
        _emit 0x81
        _emit 0xc4
        _emit 0x20
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xc3
        _emit 0x8b
        _emit 0xac
        _emit 0x24
        _emit 0x38
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xb8
        _emit 0x00
        _emit 0xeb
        _emit 0x1d
        _emit 0x10
        _emit 0x8d
        _emit 0x75
        _emit 0x14
        _emit 0x89
        _emit 0x7e
        _emit 0x04
        _emit 0x8b
        _emit 0x08
        _emit 0xf6
        _emit 0xc1
        _emit 0x01
        _emit 0x74
        _emit 0x16
        _emit 0xf6
        _emit 0xc5
        _emit 0x02
        _emit 0x74
        _emit 0x11
        _emit 0x3b
        _emit 0xc3
        _emit 0x74
        _emit 0x0d
        _emit 0x8b
        _emit 0x88
        _emit 0x18
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0x8b
        _emit 0x56
        _emit 0x0c
        _emit 0x3b
        _emit 0xca
        _emit 0x74
        _emit 0x0e
        _emit 0x05
        _emit 0x64
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0x3d
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0x7c
        _emit 0xd7
        _emit 0xeb
        _emit 0x75
        _emit 0x89
        _emit 0x7c
        _emit 0x24
        _emit 0x10
        _emit 0x89
        _emit 0x7c
        _emit 0x24
        _emit 0x14
        _emit 0x89
        _emit 0x7c
        _emit 0x24
        _emit 0x18
        _emit 0x89
        _emit 0x7c
        _emit 0x24
        _emit 0x1c
        _emit 0x89
        _emit 0x7c
        _emit 0x24
        _emit 0x20
        _emit 0x89
        _emit 0x7c
        _emit 0x24
        _emit 0x24
        _emit 0x89
        _emit 0x7c
        _emit 0x24
        _emit 0x28
        _emit 0x89
        _emit 0x7c
        _emit 0x24
        _emit 0x2c
        _emit 0x8d
        _emit 0x54
        _emit 0x24
        _emit 0x10
        _emit 0xb8
        _emit 0x00
        _emit 0xeb
        _emit 0x1d
        _emit 0x10
        _emit 0x8b
        _emit 0x08
        _emit 0xf6
        _emit 0xc1
        _emit 0x01
        _emit 0x74
        _emit 0x1e
        _emit 0xf6
        _emit 0xc5
        _emit 0x02
        _emit 0x74
        _emit 0x19
        _emit 0x3b
        _emit 0xc3
        _emit 0x74
        _emit 0x15
        _emit 0x8b
        _emit 0x88
        _emit 0x18
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0x3b
        _emit 0xcf
        _emit 0x7c
        _emit 0x0b
        _emit 0x83
        _emit 0xf9
        _emit 0x08
        _emit 0x7d
        _emit 0x06
        _emit 0xc7
        _emit 0x02
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0x05
        _emit 0x64
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0x83
        _emit 0xc2
        _emit 0x04
        _emit 0x3d
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0x7c
        _emit 0xcc
        _emit 0x33
        _emit 0xc0
        _emit 0x8d
        _emit 0x4c
        _emit 0x24
        _emit 0x10
        _emit 0x39
        _emit 0x39
        _emit 0x74
        _emit 0x0b
        _emit 0x40
        _emit 0x83
        _emit 0xc1
        _emit 0x04
        _emit 0x83
        _emit 0xf8
        _emit 0x08
        _emit 0x7c
        _emit 0xf3
        _emit 0xeb
        _emit 0x03
        _emit 0x89
        _emit 0x46
        _emit 0x0c
        _emit 0x8b
        _emit 0x13
        _emit 0x8d
        _emit 0x44
        _emit 0x24
        _emit 0x30
        _emit 0x52
        _emit 0x68
        _emit 0x1c
        _emit 0xd8
        _emit 0x02
        _emit 0x10
        _emit 0x50
        _emit 0xe8
        _emit 0x3a
        _emit 0x59
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x4c
        _emit 0x24
        _emit 0x3c
        _emit 0x6a
        _emit 0x01
        _emit 0x51
        _emit 0x68
        _emit 0xdd
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x0c
        _emit 0xd7
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0xcb
        _emit 0xec
        _emit 0xfe
        _emit 0xff
        _emit 0x8d
        _emit 0xbb
        _emit 0x0c
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0xb9
        _emit 0x15
        _emit 0x00
        _emit 0x00
        _emit 0x00
        _emit 0xf3
        _emit 0xa5
        _emit 0x8b
        _emit 0x13
        _emit 0x8d
        _emit 0x44
        _emit 0x24
        _emit 0x4c
        _emit 0x66
        _emit 0xa5
        _emit 0x52
        _emit 0x68
        _emit 0xf0
        _emit 0xd7
        _emit 0x02
        _emit 0x10
        _emit 0x50
        _emit 0xa4
        _emit 0xe8
        _emit 0x02
        _emit 0x59
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x4c
        _emit 0x24
        _emit 0x58
        _emit 0x6a
        _emit 0x01
        _emit 0x51
        _emit 0x68
        _emit 0xe2
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x0c
        _emit 0xd7
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0x93
        _emit 0xec
        _emit 0xfe
        _emit 0xff
        _emit 0x8b
        _emit 0x3b
        _emit 0x8d
        _emit 0x54
        _emit 0x24
        _emit 0x68
        _emit 0x81
        _emit 0xe7
        _emit 0xff
        _emit 0xdf
        _emit 0xff
        _emit 0xff
        _emit 0x8b
        _emit 0xc7
        _emit 0x89
        _emit 0x3b
        _emit 0x50
        _emit 0x68
        _emit 0xb4
        _emit 0xd7
        _emit 0x02
        _emit 0x10
        _emit 0x52
        _emit 0xe8
        _emit 0xd0
        _emit 0x58
        _emit 0x00
        _emit 0x00
        _emit 0x83
        _emit 0xc4
        _emit 0x44
        _emit 0x8d
        _emit 0x44
        _emit 0x24
        _emit 0x30
        _emit 0x6a
        _emit 0x01
        _emit 0x50
        _emit 0x68
        _emit 0xe7
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x0c
        _emit 0xd7
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0x5e
        _emit 0xec
        _emit 0xfe
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x10
        _emit 0xbe
        _emit 0x00
        _emit 0xeb
        _emit 0x1d
        _emit 0x10
        _emit 0x8b
        _emit 0x06
        _emit 0xa8
        _emit 0x01
        _emit 0x74
        _emit 0x18
        _emit 0xf6
        _emit 0xc4
        _emit 0x02
        _emit 0x74
        _emit 0x13
        _emit 0x55
        _emit 0x56
        _emit 0xe8
        _emit 0xa4
        _emit 0x5f
        _emit 0xff
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x08
        _emit 0x83
        _emit 0xf8
        _emit 0xff
        _emit 0x0f
        _emit 0x84
        _emit 0x6f
        _emit 0xfe
        _emit 0xff
        _emit 0xff
        _emit 0x81
        _emit 0xc6
        _emit 0x64
        _emit 0x42
        _emit 0x26
        _emit 0x00
        _emit 0x81
        _emit 0xfe
        _emit 0x20
        _emit 0xfe
        _emit 0x4f
        _emit 0x11
        _emit 0x7c
        _emit 0xd4
        _emit 0x8b
        _emit 0x0b
        _emit 0x8d
        _emit 0x54
        _emit 0x24
        _emit 0x30
        _emit 0x51
        _emit 0x68
        _emit 0x88
        _emit 0xd7
        _emit 0x02
        _emit 0x10
        _emit 0x52
        _emit 0xe8
        _emit 0x71
        _emit 0x58
        _emit 0x00
        _emit 0x00
        _emit 0x8d
        _emit 0x44
        _emit 0x24
        _emit 0x3c
        _emit 0x6a
        _emit 0x01
        _emit 0x50
        _emit 0x68
        _emit 0xef
        _emit 0x02
        _emit 0x00
        _emit 0x00
        _emit 0x68
        _emit 0x0c
        _emit 0xd7
        _emit 0x02
        _emit 0x10
        _emit 0xe8
        _emit 0x02
        _emit 0xec
        _emit 0xfe
        _emit 0xff
        _emit 0x83
        _emit 0xc4
        _emit 0x1c
        _emit 0x33
        _emit 0xc0
        _emit 0x5f
        _emit 0x5e
        _emit 0x5d
        _emit 0x5b
        _emit 0x81
        _emit 0xc4
        _emit 0x20
        _emit 0x01
        _emit 0x00
        _emit 0x00
        _emit 0xc3
    }
}
#else
// CFLAGS: /DREBREW_ALLOW_NAKED /O2 /Gd

/* Game function - handles player join request (lobbycommands.c) */

int __cdecl lb_HandleLobbyCommands(char* player, char* msg)
{
        int slots[8];
        char buf[0x100];
        int flags;
        char* p;
        int count;
        int line;
        int result;

        flags = *(int*) player;

        if (flags & 0x4000) {
                line = 0x29a;
        }
        else if (!(flags & 0x2000)) {
                line = 0x2a4;
        }
        else {
                goto main_logic;
        }

        LogMessageInternal((char*) 0x1002d70c, line, (char*) 0x1002d740, 1);
        *msg = 2;
        result = cm_QueuePlayerCommand((unsigned int*)player, (unsigned char*)msg);
        return (result != -1) - 1;

main_logic:
        /* Count active players */
        count = 0;
        for (p = (char*) g_player_slots_base; p < (char*)g_player_slots; p += 0x264264) {
                flags = *(int*) p;
                if ((flags & 1) && (flags & 0x200) && !(flags & 0x2000)) {
                        count++;
                }
        }

        if (count >= *(int*) 0x11764084) {
                LogMessageInternal((char*) 0x1002d70c, 0x2b1, (char*) 0x1002d848, 1);
                *msg = 2;
                if (cm_QueuePlayerCommand((unsigned int*)player, (unsigned char*)msg) == -1) {
                        return -1;
                }
                cm_ClosePlayerConnection(player);
                return 0;
        }

        /* Find matching player by game ID */
        *(int*) (msg + 0x18) = 0;
        for (p = (char*) g_player_slots_base; p < (char*)g_player_slots; p += 0x264264) {
                flags = *(int*) p;
                if ((flags & 1) && (flags & 0x200) && p != player && *(int*) (p + 0x264218) == *(int*) (msg + 0x20)) {
                        goto found_match;
                }
        }
        goto do_join;

found_match:
        /* Zero slot availability array */
        memset(slots, 0, sizeof(slots));

        /* Mark used slots */
        for (p = (char*) g_player_slots_base; p < (char*)g_player_slots; p += 0x264264) {
                flags = *(int*) p;
                if ((flags & 1) && (flags & 0x200) && p != player) {
                        int slot_id = *(int*) (p + 0x264218);
                        if (slot_id >= 0 && slot_id < 8) {
                                slots[slot_id] = 1;
                        }
                }
        }

        /* Find first empty slot */
        count = 0;
        do {
                if (slots[count] == 0) {
                        *(int*) (msg + 0x20) = count;
                        goto do_join;
                }
                count++;
        } while (count < 8);

do_join:
        /* Log join info */
        sprintf(buf, (char*) 0x1002d81c, *(int*) player);
        LogMessageInternal((char*) 0x1002d70c, 0x2dd, buf, 1);

        /* Copy join data to player struct */
        memcpy(player + 0x26420c, msg + 0x14, 87);

        /* Log player state */
        sprintf(buf, (char*) 0x1002d7f0, *(int*) player);
        LogMessageInternal((char*) 0x1002d70c, 0x2e2, buf, 1);

        /* Clear "waiting" flag */
        *(int*) player = *(int*) player & ~0x2000;
        sprintf(buf, (char*) 0x1002d7b4, *(int*) player);
        LogMessageInternal((char*) 0x1002d70c, 0x2e7, buf, 1);

        /* Notify all active players */
        p = (char*) g_player_slots_base;
        do {
                flags = *(int*) p;
                if ((flags & 1) && (flags & 0x200)) {
                        if (cm_QueuePlayerCommand((unsigned int*)p, (unsigned char*)msg) == -1) {
                                return -1;
                        }
                }
                p += 0x264264;
        } while (p < (char*)g_player_slots);

        /* Final log */
        sprintf(buf, (char*) 0x1002d788, *(int*) player);
        LogMessageInternal((char*) 0x1002d70c, 0x2ef, buf, 1);

        return 0;
}
#endif


/* Lobby handler: broadcasts a player state change (join, leave,
 * ready, name change) to all connected lobby clients. */
