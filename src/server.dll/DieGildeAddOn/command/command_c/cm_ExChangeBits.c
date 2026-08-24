
#include "../command_internal.h"
#include "../../../Units/Error/error.h"

#ifdef __clang__
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 208B
 *    CFlags:
 *    Symbol: _ExSetEntityBitmask
 *    Files: DieGildeAddOn/command/command.c * / *
 * int __cdecl cm_ExChangeBits(int param_1,char *param_2)
 *
 * {
 *   int iVar1;
 *   int iVar2;
 *   uint *puVar3;
 *   byte bVar4;
 *   uint uVar5;
 *   void *pvStack_8;
 *   void *pvStack_4;
 *
 *   iVar1 = param_1;
 *   iVar2 = gm_GetFieldByType((char *)param_1,*(int *)(param_1 + 0x10));
 *   *(int *)(iVar1 + 0x10) = iVar2;
 *   iVar2 = gm_ResolveEntityById((void **)&param_1,&pvStack_8,&pvStack_4,iVar2);
 *   if (iVar2 == 0) {
 *     LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x340d,
 *                        s_cm_ExChangeBits___Invalid_Id_1002d114,1);
 *     return 1;
 *   }
 *   if ((param_1 == 0) && (param_1 = (int)pvStack_8, pvStack_8 == (void *)0x0)) {
 *     param_1 = (int)pvStack_4;
 *   }
 *   puVar3 = (uint *)(param_1 + *(int *)(iVar1 + 0x14));
 *   iVar2 = *(int *)(iVar1 + 0x18);
 *   if (iVar2 == 1) {
 *     bVar4 = (byte)*puVar3 & ~*(byte *)(iVar1 + 0x20);
 *     *(byte *)puVar3 = bVar4;
 *     *(byte *)puVar3 = *(byte *)(iVar1 + 0x1c) | bVar4;
 *   }
 *   else if (iVar2 == 2) {
 *     *(ushort *)puVar3 = (ushort)*puVar3 & ~*(ushort *)(iVar1 + 0x20);
 *     *(ushort *)puVar3 = *(ushort *)(iVar1 + 0x1c) | (ushort)*puVar3;
 *   }
 *   else if (iVar2 == 4) {
 *     uVar5 = *puVar3 & ~*(uint *)(iVar1 + 0x20);
 *     *puVar3 = uVar5;
 *     *puVar3 = *(uint *)(iVar1 + 0x1c) | uVar5;
 *   }
 *   if (param_2 != (char *)0x0) {
 *     *param_2 = '\x01';
 *   }
 */

extern char s_cm_ExChangeBits___Invalid_Id_1002d114[];

/* Execution handler: modifies bit flags on an entity. Resolves
 * entity by ID, then sets, clears, or toggles bit fields based
 * on the command payload's mask and operation. */

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
// FUNCTION: SERVER 0x1000eaa0
#ifdef REBREW_ALLOW_NAKED
// NAKED verification build: byte-identical to original 0x1000eaa0.
// C conversion blocker (docs/msvc6-allocator.md Finding 39): the
// reference folds the pre-resolve field store as `mov [esi+0x10],eax`
// while passing `&cmd` to gm_ResolveEntityById; every C formulation
// (cmd/base stores, char-cast read/store splits, `cmd + 0`, volatile,
// int* base[4], 6+ shapes) either CSE-hoists the address
// (`lea edi,[esi+0x10]` before the first call) or reloads cmd from its
// home slot — the same family blocker as cm_ExFree/cm_ExMoveObjekt/
// cm_ExChangeAttribute (Findings 7/37/38).
__declspec(naked) int __cdecl cm_ExChangeBits(int cmd, char* result)
{
	(void) cmd;
	(void) result;
	__asm {
		sub esp, 8
		push esi
		mov esi, dword ptr [esp + 0x10]
		mov eax, dword ptr [esi + 0x10]
		push eax
		push esi
		call gm_GetFieldByType
		lea ecx, [esp + 0x10]
		mov dword ptr [esi + 0x10], eax
		push eax
		lea edx, [esp + 0x10]
		push ecx
		lea eax, [esp + 0x20]
		push edx
		push eax
		call gm_ResolveEntityById
		add esp, 0x18
		test eax, eax
		jne L_resolved
		push 1
		push 0x1002d114
		push 0x340d
		push 0x1002c748
		call LogMessageInternal
		add esp, 0x10
		mov eax, 1
		pop esi
		add esp, 8
		ret
	L_resolved:
		mov eax, dword ptr [esp + 0x10]
		test eax, eax
		jne L_have_p
		mov eax, dword ptr [esp + 4]
		test eax, eax
		jne L_have_p
		mov eax, dword ptr [esp + 8]
	L_have_p:
		mov ecx, dword ptr [esi + 0x14]
		add eax, ecx
		mov ecx, dword ptr [esi + 0x18]
		dec ecx
		je L_size1
		dec ecx
		je L_size2
		sub ecx, 2
		jne L_done
		mov ecx, dword ptr [esi + 0x20]
		mov edx, dword ptr [eax]
		not ecx
		and edx, ecx
		mov dword ptr [eax], edx
		mov ecx, edx
		mov edx, dword ptr [esi + 0x1c]
		or edx, ecx
		mov dword ptr [eax], edx
		jmp L_done
	L_size2:
		mov cx, word ptr [esi + 0x20]
		not cx
		and word ptr [eax], cx
		mov cx, word ptr [eax]
		mov dx, word ptr [esi + 0x1c]
		or dx, cx
		mov word ptr [eax], dx
		jmp L_done
	L_size1:
		mov cl, byte ptr [esi + 0x20]
		mov dl, byte ptr [eax]
		not cl
		and dl, cl
		mov byte ptr [eax], dl
		mov cl, dl
		mov dl, byte ptr [esi + 0x1c]
		or dl, cl
		mov byte ptr [eax], dl
	L_done:
		mov eax, dword ptr [esp + 0x14]
		test eax, eax
		je L_finish
		mov byte ptr [eax], 1
	L_finish:
		xor eax, eax
		pop esi
		add esp, 8
		ret
	}
}
#else
int __cdecl cm_ExChangeBits(int cmd, char *result)
{
	void* pv8;
	void* pv4;
	unsigned int* puVar3;
	unsigned char bVar4;
	unsigned int uVar5;
	int field;
	int size;
	int* base;

	base = (int*)cmd;
	field = gm_GetFieldByType((char*)cmd, *(int*)(cmd + 0x10));
	base[4] = field;
	field = gm_ResolveEntityById((void**)&cmd, &pv8, &pv4, field);
	if (field == 0) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x340d,
		                   s_cm_ExChangeBits___Invalid_Id_1002d114, 1);
		return 1;
	}
	if (cmd != 0)
		puVar3 = (unsigned int*)(cmd + *(int*)(base + 0x14));
	else if (pv8 != 0)
		puVar3 = (unsigned int*)((char*)pv8 + *(int*)(base + 0x14));
	else
		puVar3 = (unsigned int*)((char*)pv4 + *(int*)(base + 0x14));
	size = *(int*)(base + 0x18);
	switch (size) {
	case 1:
		bVar4 = *(unsigned char*)puVar3 & (unsigned char)~*(unsigned char*)(base + 0x20);
		*(unsigned char*)puVar3 = bVar4;
		*(unsigned char*)puVar3 = (unsigned char)(*(unsigned char*)(base + 0x1c) | bVar4);
		break;
	case 2:
		*(unsigned short*)puVar3 = *(unsigned short*)puVar3 & (unsigned short)~*(unsigned short*)(base + 0x20);
		*(unsigned short*)puVar3 = *(unsigned short*)(base + 0x1c) | *(unsigned short*)puVar3;
		break;
	case 4:
		uVar5 = *puVar3 & ~*(unsigned int*)(base + 0x20);
		*puVar3 = uVar5;
		*puVar3 = *(unsigned int*)(base + 0x1c) | uVar5;
		break;
	}
	if (result != 0)
		*result = 1;
	return 0;
}
#endif
