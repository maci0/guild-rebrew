#include <stdio.h>
#include "command.h"
#include "../../Units/Error/error.h"

/* Module-specific external strings and data */
extern char s_D__Develop_DieGildeAddOn_command_1002d70c[];
extern char s_lb_ExLobbyServerCommand___i_1002d858[];

/* Module-specific globals with complex types */
extern PlayerSlot g_player_slots_base[8];
extern short g_record_table[];

/* Lobby handler: sends the current player list to a client.
 * Iterates player slots and writes connection info into the
 * response packet. */

// FUNCTION: SERVER 0x100145e0
// lb_ExPlayerlist

__declspec(naked) int __cdecl lb_ExPlayerlist(unsigned int* player, unsigned char* msg)
{
        (void) player;
        (void) msg;
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

__declspec(naked) int __cdecl lb_SendLobbyConfig(unsigned int* player, unsigned char* msg)
{
        (void) player;
        (void) msg;
        __asm {
                push esi
                mov esi, dword ptr [esp + 8]
                push edi
                mov eax, dword ptr [esi]
                test ah, 0x60
                je L_pkt_ok
                push 1
                push 0x1002d740
                push 0x264
                push 0x1002d70c
                call LogMessageInternal
                mov eax, dword ptr [esp + 0x20]
                push eax
                mov byte ptr [eax], 2
                jmp L_q_and_long_ret
        L_pkt_ok:
                mov edi, dword ptr [esp + 0x10]
                mov ecx, dword ptr [esi + 4]
                cmp ecx, dword ptr [edi + 0x14]
                je L_match
                push edi
                push esi
                mov byte ptr [edi], 2
                call cm_QueuePlayerCommand
                add esp, 8
                inc eax
                neg eax
                sbb eax, eax
                pop edi
                neg eax
                dec eax
                pop esi
                ret
        L_match:
                mov ecx, dword ptr [edi + 0x18]
                cmp ecx, 1
                jbe L_value_ok
                push 1
                push 0x1002d774
                push 0x279
                push 0x1002d70c
                call LogMessageInternal
                mov byte ptr [edi], 2
                push edi
        L_q_and_long_ret:
                push esi
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
        L_value_ok:
                test ecx, ecx
                mov dword ptr [esi + 0x264210], ecx
                je L_clear_flag
                or ah, 8
                jmp L_after_flag
        L_clear_flag:
                and ah, 0xf7
        L_after_flag:
                mov dword ptr [esi], eax
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
                push 1
                push 0x1002d758
                push 0x28c
                push 0x1002d70c
                call LogMessageInternal
                add esp, 0x10
                xor eax, eax
                pop edi
                pop esi
                ret
        L_ret_neg1:
                pop edi
                or eax, 0xffffffff
                pop esi
                ret
        }
}

/* Lobby handler: processes lobby commands like player join,
 * ready state changes, chat, and game start requests.
 * Main command dispatcher for the pre-game lobby phase. */

// FUNCTION: SERVER 0x10014a50
// lb_BroadcastStateChange

__declspec(naked) int __cdecl lb_BroadcastStateChange(unsigned int* player, unsigned char* msg)
{
        (void) player;
        (void) msg;
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

__declspec(naked) int __cdecl lb_HandleDataTransfer(unsigned int* player, unsigned char* msg)
{
        (void) player;
        (void) msg;
        __asm {
                push ebx
                push esi
                push edi
                mov edi, dword ptr [esp + 0x10]
                mov eax, dword ptr [edi]
                test ah, 0x60
                je L_valid
                push 1
                push 0x1002d740
                push 0x31d
                push 0x1002d70c
                call LogMessageInternal
                mov eax, dword ptr [esp + 0x24]
                push eax
                push edi
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
                mov ebx, dword ptr [esp + 0x14]
                mov eax, dword ptr [edi + 4]
                mov ecx, dword ptr [ebx + 0x14]
                lea esi, [ebx + 0x14]
                cmp eax, ecx
                je L_search
                push ebx
                push edi
                mov byte ptr [ebx], 2
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
        L_search:
                mov eax, 0x101deb00
        L_search_loop:
                mov ecx, dword ptr [eax]
                test cl, 1
                je L_search_next
                test ch, 2
                je L_search_next
                cmp eax, edi
                je L_search_next
                mov ecx, dword ptr [eax + 0x264218]
                mov edx, dword ptr [esi + 0xc]
                cmp ecx, edx
                je L_found_slot
        L_search_next:
                add eax, 0x264264
                cmp eax, 0x114ffe20
                jl L_search_loop
                jmp L_do_transfer
        L_found_slot:
                mov edx, dword ptr [edi + 0x264218]
                mov dword ptr [esi + 0xc], edx
        L_do_transfer:
                mov eax, dword ptr [edi + 0x264210]
                add edi, 0x26420c
                mov ecx, 0x15
                mov dword ptr [esi + 4], eax
                rep movsd
                movsw
                movsb
                mov esi, 0x101deb00
        L_bcast_loop:
                mov eax, dword ptr [esi]
                test al, 1
                je L_bcast_next
                test ah, 2
                je L_bcast_next
                push ebx
                push esi
                call cm_QueuePlayerCommand
                add esp, 8
                cmp eax, -1
                je L_ret_neg1
        L_bcast_next:
                add esi, 0x264264
                cmp esi, 0x114ffe20
                jl L_bcast_loop
                pop edi
                pop esi
                xor eax, eax
                pop ebx
                ret
        L_ret_neg1:
                pop edi
                pop esi
                or eax, 0xffffffff
                pop ebx
                ret
        }
}

/* Lobby handler: synchronizes entity state between server
 * and clients. Transfers entity data packets during the
 * game loading/setup phase. */

// FUNCTION: SERVER 0x10014bf0
// lb_HandleEntitySync

__declspec(naked) int __cdecl lb_HandleEntitySync(unsigned int* param_1, unsigned char* param_2)
{
        (void) player;
        (void) msg;
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
        (void) player;
        (void) msg;
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

int __cdecl lb_ExLobbyServerCommand(unsigned int* conn, int cmd)
{
        int cmd_result;
        char log_buf[128];

        sprintf(log_buf, s_lb_ExLobbyServerCommand___i_1002d858, (unsigned int) *(unsigned char*) (cmd + 0x10));
        LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002d70c, 0x3a5, log_buf, 1);
        switch (*(unsigned int*) (cmd + 0x10)) {
        case 0:
                cmd_result = lb_ExPlayerlist(conn, (unsigned char*) cmd);
                return cmd_result;
        case 1:
                cmd_result = lb_SendLobbyConfig(conn, (unsigned char*) cmd);
                return cmd_result;
        case 2:
                cmd_result = lb_HandleLobbyCommands((char*)conn, (char*) cmd);
                return cmd_result;
        case 3:
                cmd_result = lb_BroadcastStateChange(conn, (unsigned char*) cmd);
                return cmd_result;
        case 4:
                cmd_result = lb_HandleDataTransfer(conn, (unsigned char*) cmd);
                return cmd_result;
        case 5:
                cmd_result = lb_HandleEntitySync(conn, (unsigned char*) cmd);
                return cmd_result;
        case 6:
                cmd_result = cm_RouteCommand(conn, (unsigned char*) cmd);
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
