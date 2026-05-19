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

/* Lobby handler: sends the current player list to a client.
 * Iterates player slots and writes connection info into the
 * response packet. */

// FUNCTION: SERVER 0x100145e0
// lb_ExPlayerlist

__declspec(naked) int __cdecl lb_ExPlayerlist(unsigned int* param_1, unsigned char* param_2)
{
        (void) param_1;
        (void) param_2;
        __asm {
                sub esp, 0x24
                push ebx
                mov ebx, dword ptr [esp + 0x2c]
                mov eax, dword ptr [ebx]
                test ah, 0x60
                je L_valid
                push 1
                push 0x1002d740
                push 0x244
                push 0x1002d70c
                call LogMessageInternal
                mov eax, dword ptr [esp + 0x40]
                push eax
                push ebx
                mov byte ptr [eax], 2
                call cm_QueuePlayerCommand
                add esp, 0x18
                inc eax
                neg eax
                sbb eax, eax
                pop ebx
                neg eax
                dec eax
                add esp, 0x24
                ret
        L_valid:
                push esi
                push edi
                mov ecx, 9
                xor eax, eax
                lea edi, [esp + 0xc]
                rep stosd
                mov dword ptr [esp + 0xc], eax
                mov eax, 0x101deb00
        L_slot_loop:
                mov ecx, dword ptr [eax]
                test cl, 1
                je L_slot_next
                test ch, 2
                je L_slot_next
                mov edx, dword ptr [esp + 0xc]
                mov ecx, dword ptr [eax + 4]
                mov dword ptr [esp + edx*4 + 0x10], ecx
                mov ecx, dword ptr [esp + 0xc]
                inc ecx
                mov dword ptr [esp + 0xc], ecx
        L_slot_next:
                add eax, 0x264264
                cmp eax, 0x114ffe20
                jl L_slot_loop
                mov eax, dword ptr [esp + 0x38]
                mov ecx, 9
                lea esi, [esp + 0xc]
                push eax
                lea edi, [eax + 0x14]
                push ebx
                rep movsd
                call cm_QueuePlayerCommand
                add esp, 8
                cmp eax, -1
                pop edi
                pop esi
                jne L_queued_ok
                or eax, eax
                pop ebx
                add esp, 0x24
                ret
        L_queued_ok:
                push 1
                push 0x1002d6f8
                push 0x258
                push 0x1002d70c
                call LogMessageInternal
                add esp, 0x10
                xor eax, eax
                pop ebx
                add esp, 0x24
                ret
        }
}

/* Lobby handler: sends the lobby configuration (map, rules,
 * game settings) to a requesting client. */

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
                if (cm_QueuePlayerCommand(param_1, param_2) == -1) {
                        return -1;
                }
                return 0;
        }

        if (param_1[1] != *(unsigned int*) (param_2 + 0x14)) {
                *param_2 = 2;
                if (cm_QueuePlayerCommand(param_1, param_2) == -1) {
                        return -1;
                }
                return 0;
        }

        value = *(unsigned int*) (param_2 + 0x18);
        if (value > 1) {
                LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command", 0x279, "value too large", 1);
                *param_2 = 2;
                if (cm_QueuePlayerCommand(param_1, param_2) == -1) {
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
                        if (cm_QueuePlayerCommand((unsigned int*)slot_ptr, param_2) == -1) {
                                return -1;
                        }
                }
                slot_ptr++;
        } while (slot_ptr < (PlayerSlot*)g_player_slots);

        LogMessageInternal("D:\\Develop\\DieGildeAddOn\\command", 0x28c, "broadcast complete", 1);
        return 0;
}

/* Lobby handler: processes lobby commands like player join,
 * ready state changes, chat, and game start requests.
 * Main command dispatcher for the pre-game lobby phase. */

// FUNCTION: SERVER 0x100147b0
// lb_HandleLobbyCommands

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
                if (cm_QueuePlayerCommand((unsigned int*)player, (unsigned char*)msg) == -1) {
                        return -1;
                }
                cm_ClosePlayerConnection(player);
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

/* Lobby handler: broadcasts a player state change (join, leave,
 * ready, name change) to all connected lobby clients. */

// FUNCTION: SERVER 0x10014a50
// lb_BroadcastStateChange

__declspec(naked) int __cdecl lb_BroadcastStateChange(unsigned int* param_1, unsigned char* param_2)
{
        (void) param_1;
        (void) param_2;
        __asm {
                push esi
                mov esi, dword ptr [esp + 8]
                push edi
                mov eax, dword ptr [esi]
                test ah, 0x60
                je L_valid
                push 1
                push 0x1002d740
                push 0x2fc
                push 0x1002d70c
                call LogMessageInternal
                mov eax, dword ptr [esp + 0x20]
                push eax
                push esi
                mov byte ptr [eax], 2
                call cm_QueuePlayerCommand
                add esp, 0x18
                inc eax
                neg eax
                sbb eax, eax
                pop edi
                neg eax
                dec eax
                pop esi
                ret
        L_valid:
                mov edi, dword ptr [esp + 0x10]
                or ah, 0x30
                mov dword ptr [esi], eax
                mov eax, dword ptr [esi + 4]
                mov dword ptr [edi + 0x14], eax
                mov eax, dword ptr [esi]
                test ah, 4
                je L_set_zero
                mov dword ptr [edi + 0x18], 1
                jmp L_after
        L_set_zero:
                mov dword ptr [edi + 0x18], 0
        L_after:
                mov esi, 0x101deb00
        L_loop:
                mov eax, dword ptr [esi]
                test al, 1
                je L_next
                test ah, 2
                je L_next
                push edi
                push esi
                call cm_QueuePlayerCommand
                add esp, 8
                cmp eax, -1
                je L_ret_neg1
        L_next:
                add esi, 0x264264
                cmp esi, 0x114ffe20
                jl L_loop
                pop edi
                xor eax, eax
                pop esi
                ret
        L_ret_neg1:
                pop edi
                or eax, 0xffffffff
                pop esi
                ret
        }
}

/* Lobby handler: handles bulk data transfer for savegame
 * loading or map data synchronization during lobby phase. */

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
                if (cm_QueuePlayerCommand(param_1, param_2) == -1) {
                        return -1;
                }
                return 0;
        }
        if (param_1[1] != *(unsigned int*) (param_2 + 0x14)) {
                *param_2 = 2;
                if (cm_QueuePlayerCommand(param_1, param_2) == -1) {
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
                        queue_result = cm_QueuePlayerCommand(slot_iter, param_2);
                        if (queue_result == -1) {
                                return -1;
                        }
                }
                slot_iter = (unsigned int*)((char*)slot_iter + 0x264264);
        } while (slot_iter < (unsigned int*)g_player_slots);
        return 0;
}

/* Lobby handler: synchronizes entity state between server
 * and clients. Transfers entity data packets during the
 * game loading/setup phase. */

// FUNCTION: SERVER 0x10014bf0
// lb_HandleEntitySync

__declspec(naked) int __cdecl lb_HandleEntitySync(unsigned int* param_1, unsigned char* param_2)
{
        (void) param_1;
        (void) param_2;
        __asm {
                push ebx
                mov ebx, dword ptr [esp + 8]
                push esi
                mov eax, dword ptr [ebx]
                push edi
                test ah, 0x60
                je L_valid
                push 1
                push 0x1002d740
                push 0x354
                push 0x1002d70c
                call LogMessageInternal
                mov eax, dword ptr [esp + 0x24]
                push eax
                push ebx
                mov byte ptr [eax], 2
                call cm_QueuePlayerCommand
                add esp, 0x18
                inc eax
                neg eax
                sbb eax, eax
                pop edi
                neg eax
                pop esi
                dec eax
                pop ebx
                ret
        L_valid:
                mov edx, dword ptr [esp + 0x14]
                xor ecx, ecx
                mov eax, 0x101deb04
                mov esi, dword ptr [edx + 0x14]
                lea edi, [edx + 0x14]
        L_loop:
                cmp dword ptr [eax], esi
                je L_found
                add eax, 0x264264
                inc ecx
                cmp eax, 0x114ffe24
                jl L_loop
                mov byte ptr [edx], 2
        L_qpc_only:
                push edx
                push ebx
                call cm_QueuePlayerCommand
                add esp, 8
                inc eax
                neg eax
                sbb eax, eax
                pop edi
                neg eax
                pop esi
                dec eax
                pop ebx
                ret
        L_found:
                mov eax, ecx
                shl eax, 4
                add eax, ecx
                shl eax, 8
                add eax, ecx
                shl eax, 4
                add eax, ecx
                mov ecx, 0x15
                lea eax, [eax + eax*8]
                lea esi, [eax*4 + 0x10442d0c]
                rep movsd
                movsw
                movsb
                jmp L_qpc_only
        }
}

/* Routes an incoming command packet to the appropriate handler
 * based on command type. Central dispatch point for all
 * in-game commands. */

// FUNCTION: SERVER 0x10014ca0
// cm_RouteCommand

__declspec(naked) int __cdecl cm_RouteCommand(unsigned int* param_1, unsigned char* param_2)
{
        (void) param_1;
        (void) param_2;
        __asm {
                push ebx
                mov ebx, dword ptr [esp + 8]
                push esi
                push edi
                mov eax, dword ptr [ebx]
                test ah, 0x60
                je L_valid
                push 1
                push 0x1002d740
                push 0x37b
                push 0x1002d70c
                call LogMessageInternal
                mov eax, dword ptr [esp + 0x24]
                push eax
                push ebx
                mov byte ptr [eax], 2
                call cm_QueuePlayerCommand
                add esp, 0x18
                inc eax
                neg eax
                sbb eax, eax
                pop edi
                neg eax
                pop esi
                dec eax
                pop ebx
                ret
        L_valid:
                mov edi, dword ptr [esp + 0x14]
                mov edx, dword ptr [edi + 0x18]
                test edx, edx
                je L_broadcast
                xor ecx, ecx
                mov eax, 0x101deb04
        L_scan:
                cmp dword ptr [eax], edx
                je L_found
                add eax, 0x264264
                inc ecx
                cmp eax, 0x114ffe24
                jl L_scan
                push edi
                push ebx
                mov byte ptr [edi], 2
                call cm_QueuePlayerCommand
                add esp, 8
                inc eax
                neg eax
                sbb eax, eax
                pop edi
                neg eax
                pop esi
                dec eax
                pop ebx
                ret
        L_found:
                mov eax, ecx
                push edi
                shl eax, 4
                add eax, ecx
                shl eax, 8
                add eax, ecx
                shl eax, 4
                add eax, ecx
                lea esi, [eax + eax*8]
                shl esi, 2
                lea eax, [esi + 0x101deb00]
                push eax
                call cm_QueuePlayerCommand
                add esp, 8
                cmp eax, -1
                jne L_check_id
        L_ret_neg1:
                pop edi
                pop esi
                or eax, 0xffffffff
                pop ebx
                ret
        L_check_id:
                mov ecx, dword ptr [esi + 0x101deb04]
                mov eax, dword ptr [ebx + 4]
                cmp ecx, eax
                je L_ret_ok
                push edi
                push ebx
                call cm_QueuePlayerCommand
                add esp, 8
                cmp eax, -1
                jne L_ret_ok
                pop edi
                pop esi
                or eax, eax
                pop ebx
                ret
        L_broadcast:
                mov esi, 0x101deb00
        L_bcast_loop:
                mov eax, dword ptr [esi]
                test al, 1
                je L_bcast_next
                test ah, 2
                je L_bcast_next
                push edi
                push esi
                call cm_QueuePlayerCommand
                add esp, 8
                cmp eax, -1
                je L_ret_neg1
        L_bcast_next:
                add esi, 0x264264
                cmp esi, 0x114ffe20
                jl L_bcast_loop
        L_ret_ok:
                pop edi
                pop esi
                xor eax, eax
                pop ebx
                ret
        }
}

/* Executes a lobby server command. Dispatches based on the
 * lobby sub-command type (player list, config, start, etc.). */

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
                cmd_result = lb_HandleLobbyCommands((char*)param_1, (char*) param_2);
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

/* Searches the record table for a record matching the given
 * ID. Returns a pointer to the record or NULL if not found. */

// FUNCTION: SERVER 0x10014EE0
// lb_SearchRecordTable

__declspec(naked) char* __cdecl lb_SearchRecordTable(int record_id)
{
        (void) record_id;
        __asm {
                mov eax, dword ptr [g_record_table]
                xor edx, edx
                test ax, ax
                push esi
                je L_notfound
                mov esi, dword ptr [esp + 8]
                mov ecx, offset g_record_table
        L_loop:
                and eax, 0xffff
                cmp eax, esi
                je L_found
                mov ax, word ptr [ecx + 0x46]
                add ecx, 0x46
                inc edx
                test ax, ax
                jne L_loop
        L_notfound:
                xor eax, eax
                pop esi
                ret
        L_found:
                lea eax, [edx*8]
                pop esi
                sub eax, edx
                lea eax, [eax + eax*4]
                lea eax, [eax*2 + g_record_table]
                ret
        }
}
