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

