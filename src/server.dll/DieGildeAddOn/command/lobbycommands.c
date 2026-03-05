#include <stdio.h>
#include <string.h>
#include "command.h"
#include "../../Units/Error/error.h"

/* Module-specific external strings and data */
extern char s_D__Develop_DieGildeAddOn_command_1002d70c[];
extern char s_invalid_client_state_1002d740[];
extern char s_Got_lb_ExPlayerlist_1002d6f8[];
extern char s_lb_ExLobbyServerCommand___i_1002d858[];

/* Module-specific globals with complex types */
extern PlayerSlot g_player_slots_base[8];
extern void* g_player_slots;
extern short g_record_table[];
extern unsigned char g_entity_sync_data[];

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 304
// GHIDRA: SendLobbyPlayerList
// FUNCTION: SERVER 0x100145e0
// lb_ExPlayerlist

int __cdecl lb_ExPlayerlist(unsigned int* param_1, unsigned char* param_2)
{
        int counter;
        unsigned int* src_ptr;
        unsigned int* dst_ptr;
        unsigned int player_list[9];

        if ((*param_1 & 0x6000) != 0) {
                LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002d70c, 0x244, s_invalid_client_state_1002d740, 1);
                *param_2 = 2;
                if (QueuePlayerCommand(param_1, param_2) == -1) {
                        return -1;
                }
                return 0;
        }
        src_ptr = player_list;
        for (counter = 9; counter != 0; counter = counter + -1) {
                *src_ptr = 0;
                src_ptr = src_ptr + 1;
        }
        player_list[0] = 0;
        src_ptr = (unsigned int*)g_player_slots_base;
        do {
                if (((*src_ptr & 1) != 0) && ((*src_ptr & 0x200) != 0)) {
                        player_list[player_list[0] + 1] = src_ptr[1];
                        player_list[0] = player_list[0] + 1;
                }
                src_ptr = src_ptr + 0x99099;
        } while (src_ptr < (unsigned int*)g_player_slots);
        src_ptr = player_list;
        dst_ptr = (unsigned int*) (param_2 + 0x14);
        for (counter = 9; counter != 0; counter = counter + -1) {
                *dst_ptr = *src_ptr;
                src_ptr = src_ptr + 1;
                dst_ptr = dst_ptr + 1;
        }
        counter = QueuePlayerCommand(param_1, param_2);
        if (counter == -1) {
                return -1;
        }
        LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002d70c, 600, s_Got_lb_ExPlayerlist_1002d6f8, 1);
        return 0;
}

// ORIGIN: GAME
// STATUS: MATCHING
// BLOCKER: jump condition swap
// SIZE: 236
// BLOCKER_DELTA: 77
// FUNCTION: SERVER 0x100146c0
// lb_SendLobbyConfig

int __cdecl lb_SendLobbyConfig(unsigned int* param_1, unsigned char* param_2)
{
        PlayerSlot* slot_ptr;
        unsigned int value;
        unsigned int slot_flags;

        if (*param_1 & 0x6000) {
                LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command", 0x264, "invalid client state", 1);
                *param_2 = 2;
                if (QueuePlayerCommand(param_1, param_2) == -1) {
                        return -1;
                }
                return 0;
        }

        if (param_1[1] != *(unsigned int*) (param_2 + 0x14)) {
                *param_2 = 2;
                if (QueuePlayerCommand(param_1, param_2) == -1) {
                        return -1;
                }
                return 0;
        }

        value = *(unsigned int*) (param_2 + 0x18);
        if (value > 1) {
                LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command", 0x279, "value too large", 1);
                *param_2 = 2;
                if (QueuePlayerCommand(param_1, param_2) == -1) {
                        return -1;
                }
                return 0;
        }

        *(unsigned int*) ((char*) param_1 + 0x264210) = value;
        if (value != 0) {
                *param_1 |= 0x800;
        }
        else {
                *param_1 &= ~0x800;
        }

        slot_ptr = g_player_slots_base;
        do {
                slot_flags = slot_ptr->flags;
                if ((slot_flags & 1) && (slot_flags & 0x200)) {
                        if (QueuePlayerCommand((unsigned int*)slot_ptr, param_2) == -1) {
                                return -1;
                        }
                }
                slot_ptr++;
        } while (slot_ptr < (PlayerSlot*)g_player_slots);

        LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command", 0x28c, "broadcast complete", 1);
        return 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: instruction folding (lea vs mov), zero-extend pattern (xor vs mov)
// SIZE: 670
// FUNCTION: SERVER 0x100147b0
// HandleLobbyCommands

/* Game function - handles player join request (lobbycommands.c) */
// BLOCKER_DELTA: 552

int __cdecl HandleLobbyCommands(char* player, char* msg)
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
        result = QueuePlayerCommand((unsigned int*)player, (unsigned char*)msg);
        return (result != -1) - 1;

main_logic:
        /* Count active players */
        count = 0;
        p = (char*) g_player_slots_base;
        do {
                flags = *(int*) p;
                if ((flags & 1) && (flags & 0x200) && !(flags & 0x2000)) {
                        count++;
                }
                p += 0x264264;
        } while (p < (char*)g_player_slots);

        if (count >= *(int*) 0x11764084) {
                LogMessageInternal((char*) 0x1002d70c, 0x2b1, (char*) 0x1002d848, 1);
                *msg = 2;
                if (QueuePlayerCommand((unsigned int*)player, (unsigned char*)msg) == -1) {
                        return -1;
                }
                ClosePlayerConnection(player);
                return 0;
        }

        /* Find matching player by game ID */
        p = (char*) g_player_slots_base;
        *(int*) (msg + 0x18) = 0;
        do {
                flags = *(int*) p;
                if ((flags & 1) && (flags & 0x200) && p != player && *(int*) (p + 0x264218) == *(int*) (msg + 0x20)) {
                        goto found_match;
                }
                p += 0x264264;
        } while (p < (char*)g_player_slots);
        goto do_join;

found_match:
        /* Zero slot availability array */
        memset(slots, 0, sizeof(slots));

        /* Mark used slots */
        {
                p = (char*) g_player_slots_base;
                do {
                        flags = *(int*) p;
                        if ((flags & 1) && (flags & 0x200) && p != player) {
                                int slot_id = *(int*) (p + 0x264218);
                                if (slot_id >= 0 && slot_id < 8) {
                                        slots[slot_id] = 1;
                                }
                        }
                        p += 0x264264;
                } while (p < (char*)g_player_slots);
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
                        if (QueuePlayerCommand((unsigned int*)p, (unsigned char*)msg) == -1) {
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

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 157
// BLOCKER_DELTA: 37
// FUNCTION: SERVER 0x10014a50
// lb_BroadcastStateChange

int __cdecl lb_BroadcastStateChange(unsigned int* param_1, unsigned char* param_2)
{
        int queue_result;
        unsigned int* player_slot;

        if ((*param_1 & 0x6000) != 0) {
                LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command", 0x2fc, "invalid client state", 1);
                *param_2 = 2;
                queue_result = QueuePlayerCommand(param_1, param_2);
                if (queue_result == -1) {
                        return -1;
                }
                return 0;
        }
        *param_1 = *param_1 | 0x3000;
        *(unsigned int*) (param_2 + 0x14) = param_1[1];
        if ((*param_1 & 0x400) != 0) {
                *(int*) (param_2 + 0x18) = 1;
        }
        else {
                *(int*) (param_2 + 0x18) = 0;
        }
        player_slot = (unsigned int*)g_player_slots_base;
        do {
                if ((*player_slot & 1) != 0 && (*player_slot & 0x200) != 0) {
                        if (QueuePlayerCommand(player_slot, param_2) == -1) {
                                return -1;
                        }
                }
                player_slot = (unsigned int*)((char*)player_slot + 0x264264);
        } while (player_slot < (unsigned int*)g_player_slots);
        return 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 247
// BLOCKER_DELTA: 49
// FUNCTION: SERVER 0x10014af0
// lb_HandleDataTransfer

int __cdecl lb_HandleDataTransfer(unsigned int* param_1, unsigned char* param_2)
{
        int queue_result;
        unsigned int* slot_iter;
        unsigned int* transfer_data;

        if ((*param_1 & 0x6000) != 0) {
                LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002d70c, 0x31d, s_invalid_client_state_1002d740, 1);
                *param_2 = 2;
                if (QueuePlayerCommand(param_1, param_2) == -1) {
                        return -1;
                }
                return 0;
        }
        if (param_1[1] != *(unsigned int*) (param_2 + 0x14)) {
                *param_2 = 2;
                if (QueuePlayerCommand(param_1, param_2) == -1) {
                        return -1;
                }
                return 0;
        }
        {
                transfer_data = (unsigned int*) (param_2 + 0x14);
                slot_iter = (unsigned int*)g_player_slots_base;
                while (((*slot_iter & 1) == 0 || ((*slot_iter & 0x200) == 0)) || (slot_iter == param_1) ||
                           (slot_iter[0x99086] != transfer_data[3])) {
                        slot_iter = (unsigned int*)((char*)slot_iter + 0x264264);
                        if (slot_iter >= (unsigned int*)g_player_slots) {
                                goto do_transfer;
                        }
                }
                transfer_data[3] = param_1[0x99086];
        do_transfer:
                transfer_data[1] = param_1[0x99084];
                memcpy((char*)param_1 + 0x26420c, transfer_data, 0x57);
        }
        slot_iter = (unsigned int*)g_player_slots_base;
        do {
                if (((*slot_iter & 1) != 0) && ((*slot_iter & 0x200) != 0)) {
                        queue_result = QueuePlayerCommand(slot_iter, param_2);
                        if (queue_result == -1) {
                                return -1;
                        }
                }
                slot_iter = (unsigned int*)((char*)slot_iter + 0x264264);
        } while (slot_iter < (unsigned int*)g_player_slots);
        return 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 163
// FUNCTION: SERVER 0x10014bf0
// lb_HandleEntitySync

int __cdecl lb_HandleEntitySync(unsigned int* param_1, unsigned char* param_2)
{
        unsigned int* slot_ptr;
        unsigned int target_id;
        int i;
        int result;

        if (*param_1 & 0x6000) {
                LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command", 0x354, "invalid client state", 1);
                *param_2 = 2;
                result = QueuePlayerCommand(param_1, param_2);
                return (result != -1) - 1;
        }

        target_id = *(unsigned int*) (param_2 + 0x14);
        slot_ptr = &g_player_slots_base[0].id;
        i = 0;
        while (*slot_ptr != target_id) {
                slot_ptr = (unsigned int*) ((char*) slot_ptr + 0x264264);
                i++;
                if (slot_ptr >= (unsigned int*)((char*)g_player_slots + 4)) {
                        *param_2 = 2;
                        result = QueuePlayerCommand(param_1, param_2);
                        return (result != -1) - 1;
                }
        }

        {
                int off;
                off = (i << 4) + i;
                off = (off << 8) + i;
                off = (off << 4) + i;
                off = off * 9;
                memcpy(param_2 + 0x14, &g_entity_sync_data[off * 4], 0x57);
        }

        result = QueuePlayerCommand(param_1, param_2);
        return (result != -1) - 1;
}

// STATUS: MATCHING
// ORIGIN: GAME
// BLOCKER: comparison direction swap, jump condition swap, zero-extend pattern (xor vs mov)
// SIZE: 265
// BLOCKER_DELTA: 202
// NOTE: obj includes 28B jump table after code (296B obj vs 267B PE). Code matches byte-for-byte.
// FUNCTION: SERVER 0x10014ca0
// cm_RouteCommand

int __cdecl cm_RouteCommand(unsigned int* param_1, unsigned char* param_2)
{
        int slot_index;
        int* id_ptr;
        int queue_result;
        unsigned int* player_slot;

        if ((*param_1 & 0x6000) != 0) {
                LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002d70c, 0x37b, s_invalid_client_state_1002d740, 1);
                *param_2 = 2;
                slot_index = QueuePlayerCommand(param_1, param_2);
                if (slot_index == -1) {
                        return -1;
                }
                return 0;
        }
        if (*(int*) (param_2 + 0x18) != 0) {
                slot_index = 0;
                id_ptr = (int*)&g_player_slots_base[0].id;
                while (*id_ptr != *(int*) (param_2 + 0x18)) {
                        id_ptr = (int*)((char*)id_ptr + 0x264264);
                        slot_index = slot_index + 1;
                        if (id_ptr > (int*)((char*)g_player_slots + 4)) {
                                *param_2 = 2;
                                queue_result = QueuePlayerCommand(param_1, param_2);
                                if (queue_result == -1) {
                                        return -1;
                                }
                                return 0;
                        }
                }
                queue_result = QueuePlayerCommand((unsigned int*)&g_player_slots_base[slot_index], param_2);
                if (queue_result == -1) {
                        return -1;
                }
                if (g_player_slots_base[slot_index].id != param_1[1]) {
                        slot_index = QueuePlayerCommand(param_1, param_2);
                        if (slot_index == -1) {
                                return -1;
                        }
                }
        }
        else {
                player_slot = (unsigned int*)g_player_slots_base;
                do {
                        if (((*player_slot & 1) != 0) && ((*player_slot & 0x200) != 0)) {
                                slot_index = QueuePlayerCommand(player_slot, param_2);
                                if (slot_index == -1) {
                                        return -1;
                                }
                        }
                        player_slot = (unsigned int*)((char*)player_slot + 0x264264);
                } while (player_slot < (unsigned int*)g_player_slots);
        }
        return 0;
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 267
// BLOCKER_DELTA: 75
// ANALYSIS: obj includes 28B jump table after code (296B obj vs 267B PE). Code matches byte-for-byte.
// FUNCTION: SERVER 0x10014db0
// lb_ExLobbyServerCommand

int __cdecl lb_ExLobbyServerCommand(unsigned int* param_1, int param_2)
{
        int cmd_result;
        char log_buf[128];

        sprintf(log_buf, s_lb_ExLobbyServerCommand___i_1002d858, (unsigned int) *(unsigned char*) (param_2 + 0x10));
        LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002d70c, 0x3a5, log_buf, 1);
        switch (*(unsigned int*) (param_2 + 0x10)) {
        case 0:
                cmd_result = lb_ExPlayerlist(param_1, (unsigned char*) param_2);
                return cmd_result;
        case 1:
                cmd_result = lb_SendLobbyConfig(param_1, (unsigned char*) param_2);
                return cmd_result;
        case 2:
                cmd_result = HandleLobbyCommands((char*)param_1, (char*) param_2);
                return cmd_result;
        case 3:
                cmd_result = lb_BroadcastStateChange(param_1, (unsigned char*) param_2);
                return cmd_result;
        case 4:
                cmd_result = lb_HandleDataTransfer(param_1, (unsigned char*) param_2);
                return cmd_result;
        case 5:
                cmd_result = lb_HandleEntitySync(param_1, (unsigned char*) param_2);
                return cmd_result;
        case 6:
                cmd_result = cm_RouteCommand(param_1, (unsigned char*) param_2);
                return cmd_result;
        default:
                return 1;
        }
}

// STATUS: RELOC
// ORIGIN: GAME
// SIZE: 69
// FUNCTION: SERVER 0x10014EE0
// lb_SearchRecordTable

char* __cdecl lb_SearchRecordTable(int record_id)
{
        unsigned int val;
        int idx;
        char* ptr;

        val = (unsigned short) g_record_table[0];
        idx = 0;
        if ((short) val == 0) {
                return 0;
        }
        ptr = (char*) g_record_table;
        do {
                if (val == (unsigned int) record_id) {
                        return (char*) g_record_table + idx * 70;
                }
                val = *(unsigned short*) (ptr + 70);
                ptr += 70;
                idx++;
        } while ((short) val != 0);
        return 0;
}
