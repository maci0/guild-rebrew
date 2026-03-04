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
// SYMBOL: _lb_ExPlayerlist
// GHIDRA: SendLobbyPlayerList
// FUNCTION: SERVER 0x100145e0
// lb_ExPlayerlist

int __cdecl lb_ExPlayerlist(unsigned int* param_1, unsigned char* param_2)
{
        int iVar1;
        unsigned int* puVar2;
        unsigned int* puVar3;
        unsigned int local_24[9];

        if ((*param_1 & 0x6000) != 0) {
                LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002d70c, 0x244, s_invalid_client_state_1002d740, 1);
                *param_2 = 2;
                if (QueuePlayerCommand(param_1, param_2) == -1) {
                        return -1;
                }
                return 0;
        }
        puVar2 = local_24;
        for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
                *puVar2 = 0;
                puVar2 = puVar2 + 1;
        }
        local_24[0] = 0;
        puVar2 = (unsigned int*)g_player_slots_base;
        do {
                if (((*puVar2 & 1) != 0) && ((*puVar2 & 0x200) != 0)) {
                        local_24[local_24[0] + 1] = puVar2[1];
                        local_24[0] = local_24[0] + 1;
                }
                puVar2 = puVar2 + 0x99099;
        } while (puVar2 < (unsigned int*)g_player_slots);
        puVar2 = local_24;
        puVar3 = (unsigned int*) (param_2 + 0x14);
        for (iVar1 = 9; iVar1 != 0; iVar1 = iVar1 + -1) {
                *puVar3 = *puVar2;
                puVar2 = puVar2 + 1;
                puVar3 = puVar3 + 1;
        }
        iVar1 = QueuePlayerCommand(param_1, param_2);
        if (iVar1 == -1) {
                return -1;
        }
        LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002d70c, 600, s_Got_lb_ExPlayerlist_1002d6f8, 1);
        return 0;
}

// ORIGIN: GAME
// STATUS: MATCHING
// BLOCKER: jump condition swap
// SIZE: 236
// SYMBOL: _SendLobbyConfig
// BLOCKER_DELTA: 77
// FUNCTION: SERVER 0x100146c0
// SendLobbyConfig

int __cdecl SendLobbyConfig(unsigned int* param_1, unsigned char* param_2)
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
// SYMBOL: _HandleLobbyCommands
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
// SYMBOL: _broadcast_state_change
// BLOCKER_DELTA: 37
// FUNCTION: SERVER 0x10014a50
// broadcast_state_change

int __cdecl broadcast_state_change(unsigned int* param_1, unsigned char* param_2)
{
        int iVar1;
        unsigned int* player_slot;

        if ((*param_1 & 0x6000) != 0) {
                LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command", 0x2fc, "invalid client state", 1);
                *param_2 = 2;
                iVar1 = QueuePlayerCommand(param_1, param_2);
                if (iVar1 == -1) {
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
// SYMBOL: _HandleDataTransferCommand
// BLOCKER_DELTA: 49
// FUNCTION: SERVER 0x10014af0
// HandleDataTransferCommand

int __cdecl HandleDataTransferCommand(unsigned int* param_1, unsigned char* param_2)
{
        int iVar1;
        unsigned int* puVar2;
        unsigned int* pSrc;

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
                pSrc = (unsigned int*) (param_2 + 0x14);
                puVar2 = (unsigned int*)g_player_slots_base;
                while (((*puVar2 & 1) == 0 || ((*puVar2 & 0x200) == 0)) || (puVar2 == param_1) ||
                           (puVar2[0x99086] != pSrc[3])) {
                        puVar2 = (unsigned int*)((char*)puVar2 + 0x264264);
                        if (puVar2 >= (unsigned int*)g_player_slots) {
                                goto do_transfer;
                        }
                }
                pSrc[3] = param_1[0x99086];
        do_transfer:
                pSrc[1] = param_1[0x99084];
                memcpy((char*)param_1 + 0x26420c, pSrc, 0x57);
        }
        puVar2 = (unsigned int*)g_player_slots_base;
        do {
                if (((*puVar2 & 1) != 0) && ((*puVar2 & 0x200) != 0)) {
                        iVar1 = QueuePlayerCommand(puVar2, param_2);
                        if (iVar1 == -1) {
                                return -1;
                        }
                }
                puVar2 = (unsigned int*)((char*)puVar2 + 0x264264);
        } while (puVar2 < (unsigned int*)g_player_slots);
        return 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 163
// SYMBOL: _HandleEntitySync
// FUNCTION: SERVER 0x10014bf0
// HandleEntitySync

int __cdecl HandleEntitySync(unsigned int* param_1, unsigned char* param_2)
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
// SYMBOL: _cm_RouteCommand
// BLOCKER_DELTA: 202
// NOTE: obj includes 28B jump table after code (296B obj vs 267B PE). Code matches byte-for-byte.
// FUNCTION: SERVER 0x10014ca0
// cm_RouteCommand

int __cdecl cm_RouteCommand(unsigned int* param_1, unsigned char* param_2)
{
        int iVar1;
        int* piVar2;
        int iVar3;
        unsigned int* player_slot;

        if ((*param_1 & 0x6000) != 0) {
                LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002d70c, 0x37b, s_invalid_client_state_1002d740, 1);
                *param_2 = 2;
                iVar1 = QueuePlayerCommand(param_1, param_2);
                if (iVar1 == -1) {
                        return -1;
                }
                return 0;
        }
        if (*(int*) (param_2 + 0x18) != 0) {
                iVar1 = 0;
                piVar2 = (int*)&g_player_slots_base[0].id;
                while (*piVar2 != *(int*) (param_2 + 0x18)) {
                        piVar2 = (int*)((char*)piVar2 + 0x264264);
                        iVar1 = iVar1 + 1;
                        if (piVar2 > (int*)((char*)g_player_slots + 4)) {
                                *param_2 = 2;
                                iVar3 = QueuePlayerCommand(param_1, param_2);
                                if (iVar3 == -1) {
                                        return -1;
                                }
                                return 0;
                        }
                }
                iVar3 = QueuePlayerCommand((unsigned int*)&g_player_slots_base[iVar1], param_2);
                if (iVar3 == -1) {
                        return -1;
                }
                if (g_player_slots_base[iVar1].id != param_1[1]) {
                        iVar1 = QueuePlayerCommand(param_1, param_2);
                        if (iVar1 == -1) {
                                return -1;
                        }
                }
        }
        else {
                player_slot = (unsigned int*)g_player_slots_base;
                do {
                        if (((*player_slot & 1) != 0) && ((*player_slot & 0x200) != 0)) {
                                iVar1 = QueuePlayerCommand(player_slot, param_2);
                                if (iVar1 == -1) {
                                        return -1;
                                }
                        }
                        player_slot = (unsigned int*)((char*)player_slot + 0x264264);
                } while (player_slot < (unsigned int*)g_player_slots);
        }
        return 0;
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 267
// SYMBOL: _lb_ExLobbyServerCommand
// BLOCKER_DELTA: 75
// ANALYSIS: obj includes 28B jump table after code (296B obj vs 267B PE). Code matches byte-for-byte.
// FUNCTION: SERVER 0x10014db0
// lb_ExLobbyServerCommand

int __cdecl lb_ExLobbyServerCommand(unsigned int* param_1, int param_2)
{
        int uVar1;
        char local_80[128];

        sprintf(local_80, s_lb_ExLobbyServerCommand___i_1002d858, (unsigned int) *(unsigned char*) (param_2 + 0x10));
        LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002d70c, 0x3a5, local_80, 1);
        switch (*(unsigned int*) (param_2 + 0x10)) {
        case 0:
                uVar1 = lb_ExPlayerlist(param_1, (unsigned char*) param_2);
                return uVar1;
        case 1:
                uVar1 = SendLobbyConfig(param_1, (unsigned char*) param_2);
                return uVar1;
        case 2:
                uVar1 = HandleLobbyCommands((char*)param_1, (char*) param_2);
                return uVar1;
        case 3:
                uVar1 = broadcast_state_change(param_1, (unsigned char*) param_2);
                return uVar1;
        case 4:
                uVar1 = HandleDataTransferCommand(param_1, (unsigned char*) param_2);
                return uVar1;
        case 5:
                uVar1 = HandleEntitySync(param_1, (unsigned char*) param_2);
                return uVar1;
        case 6:
                uVar1 = cm_RouteCommand(param_1, (unsigned char*) param_2);
                return uVar1;
        default:
                return 1;
        }
}

// STATUS: MATCHING
// ORIGIN: GAME
// SIZE: 69
// SYMBOL: _SearchRecordTable
// FUNCTION: SERVER 0x10014EE0
// SearchRecordTable

char* __cdecl SearchRecordTable(int record_id)
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
