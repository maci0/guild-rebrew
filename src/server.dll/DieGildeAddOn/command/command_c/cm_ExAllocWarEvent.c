
#include "../command_internal.h"

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 280B
 *    CFlags:
 *    Symbol: _AllocWarEvent
 *    Files: DieGildeAddOn/command/command.c * / *
 * int __cdecl cm_ExAllocWarEvent(int param_1,char *param_2)
 *
 * {
 *   void *pvVar1;
 *   void *pvVar2;
 *   ushort *puVar3;
 *   byte bVar4;
 *
 *   *(undefined4 *)(param_1 + 0x10) = g_timestamp_0b6c;
 *   pvVar1 = gm_SearchTable67(*(int *)(param_1 + 0x26));
 *   if (pvVar1 == (void *)0x0) {
 *     return 1;
 *   }
 *   pvVar2 = gm_SearchTable67(*(int *)(param_1 + 0x14));
 *   if (pvVar2 == (void *)0x0) {
 *     return 1;
 *   }
 *   puVar3 = gm_StartEntityQuery(*(int *)((int)pvVar2 + 0x5d),1,0,0xca);
 *   do {
 *     if (puVar3 == (ushort *)0x0) {
 * LAB_100101b7:
 *       puVar3 = (ushort *)gm_AllocObjekt(*(int *)((int)pvVar2 + 1),0xca,1);
 *       if (puVar3 == (ushort *)0x0) {
 *         return 1;
 *       }
 *       *(undefined4 *)(g_player_slot_0[*(byte *)(param_1 + 3)].data + 0x264200) =
 *            *(undefined4 *)(puVar3 + 1);
 * LAB_100101fa:
 *       *(undefined4 *)(puVar3 + 0xe) = *(undefined4 *)(param_1 + 0x18);
 *       *(undefined4 *)(puVar3 + 0x10) = *(undefined4 *)(param_1 + 0x1c);
 *       *(undefined4 *)(puVar3 + 0x12) = *(undefined4 *)(param_1 + 0x20);
 *       puVar3[0x14] = *(ushort *)(param_1 + 0x24);
 *       *(undefined4 *)(puVar3 + 0x15) = *(undefined4 *)(param_1 + 0x26);
 *       *(undefined4 *)(puVar3 + 0x19) = *(undefined4 *)(param_1 + 0x2e);
 *       *(undefined1 *)(puVar3 + 0x1b) = *(undefined1 *)(param_1 + 0x32);
 *       bVar4 = *(char *)((int)puVar3 + 0x37) + *(char *)(param_1 + 0x33);
 *       *(byte *)((int)puVar3 + 0x37) = bVar4;
 *       if (100 < bVar4) {
 *         *(undefined1 *)((int)puVar3 + 0x37) = 100;
 *         return 0;
 *       }
 *       *(undefined1 *)((int)puVar3 + 0x37) = *(undefined1 *)((int)puVar3 + 0x37);
 */

extern char g_player_slot_0[];
extern void* __cdecl gm_SearchTable67(int);

/* Execution handler: allocates a war/battle event entity.
 * Creates a combat-related game event with attacker/target
 * references and initializes event parameters. */

// FUNCTION: SERVER 0x10010140
__declspec(naked) int __cdecl cm_ExAllocWarEvent(int cmd, char* result)
{
	(void) cmd;
	(void) result;
	__asm {
		_emit 0xa1
		_emit 0x6c
		_emit 0x0b
		_emit 0x03
		_emit 0x10
		push ebx
		push esi
		mov esi, dword ptr [esp + 0xc]
		push edi
		mov ecx, dword ptr [esi + 0x26]
		mov dword ptr [esi + 0x10], eax
		push ecx
		call gm_SearchTable67
		mov ebx, eax
		add esp, 4
		test ebx, ebx
		jne L_have_attacker
		pop edi
		pop esi
		mov eax, 1
		pop ebx
		ret
	L_have_attacker:
		mov edx, dword ptr [esi + 0x14]
		push edx
		call gm_SearchTable67
		mov edi, eax
		add esp, 4
		test edi, edi
		jne L_have_target
		pop edi
		pop esi
		mov eax, 1
		pop ebx
		ret
	L_have_target:
		mov eax, dword ptr [edi + 0x5d]
		push 0xca
		push 0
		push 1
		push eax
		call gm_StartEntityQuery
		add esp, 0x10
		test eax, eax
		je L_alloc_new
	L_iter:
		mov ecx, dword ptr [eax + 0x2a]
		mov edx, dword ptr [ebx + 1]
		cmp ecx, edx
		je L_found_existing
		call gm_NextEntityQueryMatch
		test eax, eax
		jne L_iter
		jmp L_alloc_new
	L_found_existing:
		test eax, eax
		jne L_do_copy
	L_alloc_new:
		mov edx, dword ptr [edi + 1]
		push 1
		push 0xca
		push edx
		call gm_AllocObjekt
		add esp, 0xc
		test eax, eax
		jne L_alloc_ok
		pop edi
		pop esi
		mov eax, 1
		pop ebx
		ret
	L_alloc_ok:
		xor edx, edx
		mov dl, byte ptr [esi + 3]
		mov ecx, edx
		shl ecx, 4
		add ecx, edx
		shl ecx, 8
		add ecx, edx
		shl ecx, 4
		add ecx, edx
		mov edx, dword ptr [eax + 2]
		lea ecx, [ecx + ecx*8]
		_emit 0x89
		_emit 0x14
		_emit 0x8d
		_emit 0x08
		_emit 0x2d
		_emit 0x44
		_emit 0x10
	L_do_copy:
		lea ecx, [esi + 0x18]
		lea edx, [eax + 0x1c]
		mov bl, byte ptr [eax + 0x37]
		mov edi, dword ptr [ecx]
		mov dword ptr [edx], edi
		mov edi, dword ptr [ecx + 4]
		mov dword ptr [edx + 4], edi
		mov edi, dword ptr [ecx + 8]
		mov dword ptr [edx + 8], edi
		mov cx, word ptr [ecx + 0xc]
		mov word ptr [edx + 0xc], cx
		mov edx, dword ptr [esi + 0x26]
		mov dword ptr [eax + 0x2a], edx
		mov ecx, dword ptr [esi + 0x2e]
		mov dword ptr [eax + 0x32], ecx
		mov dl, byte ptr [esi + 0x32]
		mov byte ptr [eax + 0x36], dl
		mov cl, byte ptr [esi + 0x33]
		add bl, cl
		mov cl, bl
		mov byte ptr [eax + 0x37], bl
		cmp cl, 0x64
		jbe L_no_clamp
		mov ecx, 0x64
		pop edi
		mov byte ptr [eax + 0x37], cl
		pop esi
		xor eax, eax
		pop ebx
		ret
	L_no_clamp:
		xor ecx, ecx
		pop edi
		mov cl, byte ptr [eax + 0x37]
		pop esi
		mov byte ptr [eax + 0x37], cl
		xor eax, eax
		pop ebx
		ret
	}
}
