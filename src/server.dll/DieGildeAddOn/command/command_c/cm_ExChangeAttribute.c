
#include "../command_internal.h"
#include "../../../Units/Error/error.h"

#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 242B
 *    CFlags:
 *    Symbol: _ExAccumulateEntityFields
 *    Files: DieGildeAddOn/command/command.c * / *
 * int __cdecl cm_ExChangeAttribute(int param_1,char *param_2)
 *
 * {
 *   char cVar1;
 *   int iVar2;
 *   int iVar3;
 *   int iVar4;
 *   ushort *puVar5;
 *   int *piVar6;
 *   int *piVar7;
 *   uint uVar8;
 *   void *pvStack_8;
 *   void *pvStack_4;
 *
 *   iVar2 = param_1;
 *   iVar3 = gm_GetFieldByType((char *)param_1,*(int *)(param_1 + 0x10));
 *   iVar4 = gm_ResolveEntityById((void **)&param_1,&pvStack_8,&pvStack_4,iVar3);
 *   if (iVar4 == 0) {
 *     LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,0x31f7,
 *                        s_cm_ExChangeAttribute___Invalid_I_1002d0b0,1);
 *     return 1;
 *   }
 *   *(int *)(iVar2 + 0x10) = iVar3;
 *   if ((param_1 == 0) && (param_1 = (int)pvStack_8, pvStack_8 == (void *)0x0)) {
 *     param_1 = (int)pvStack_4;
 *   }
 *   uVar8 = 0;
 *   piVar6 = (int *)(iVar2 + 0x15);
 *   if (*(char *)(iVar2 + 0x14) != '\0') {
 *     do {
 *       cVar1 = (char)*piVar6;
 *       iVar3 = (int)*(char *)((int)piVar6 + 1);
 *       puVar5 = (ushort *)((int)piVar6 + 2);
 *       piVar6 = piVar6 + 1;
 *       piVar7 = (int *)((uint)*puVar5 + param_1);
 *       if (cVar1 == '\x01') {
 *         for (; iVar3 != 0; iVar3 = iVar3 + -1) {
 *           *(char *)piVar7 = (char)*piVar7 + (char)*piVar6;
 *           piVar6 = (int *)((int)piVar6 + 1);
 *           piVar7 = (int *)((int)piVar7 + 1);
 *         }
 *       }
 */

extern char s_cm_ExChangeAttribute___Invalid_I_1002d0b0[];

/* Execution handler: modifies a numeric attribute on an entity.
 * Resolves entity, reads field type/offset/value from the command
 * payload, then applies the change to the entity's memory. */

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
// FUNCTION: SERVER 0x1000e7d0
#ifdef REBREW_ALLOW_NAKED
// NAKED verification build: byte-identical to original 0x1000e7d0.
// C conversion blocker (docs/msvc6-allocator.md Finding 38): best C is
// 213/242 — the head, calls, selection and all three add-to-memory
// inner loops match byte-for-byte, but the loop's register pairing
// ({count,offset,dst2}->ecx with src->eax in the reference vs
// {count,offset,dst2}->eax with src->ecx in every formulation) is an
// allocator fixed-point that 19 C shapes could not invert.
__declspec(naked) int __cdecl cm_ExChangeAttribute(int cmd, char *result)
{
	(void) cmd;
	(void) result;
	__asm {
		sub esp, 8
		push ebp
		mov ebp, dword ptr [esp + 0x10]
		push esi
		mov eax, dword ptr [ebp + 0x10]
		push eax
		push ebp
		call gm_GetFieldByType
		mov esi, eax
		lea ecx, [esp + 0x14]
		push esi
		lea edx, [esp + 0x14]
		push ecx
		lea eax, [esp + 0x24]
		push edx
		push eax
		call gm_ResolveEntityById
		add esp, 0x18
		test eax, eax
		jne L_resolved
		push 1
		push 0x1002d0b0
		push 0x31f7
		push 0x1002c748
		call LogMessageInternal
		add esp, 0x10
		mov eax, 1
		pop esi
		pop ebp
		add esp, 8
		ret
	L_resolved:
		mov eax, dword ptr [esp + 0x14]
		push ebx
		test eax, eax
		push edi
		mov dword ptr [ebp + 0x10], esi
		je L_chk_exist
		mov edi, eax
		jmp L_have_dst
	L_chk_exist:
		mov eax, dword ptr [esp + 0x10]
		test eax, eax
		mov edi, eax
		jne L_have_dst
		mov edi, dword ptr [esp + 0x14]
	L_have_dst:
		mov cl, byte ptr [ebp + 0x14]
		xor ebx, ebx
		test cl, cl
		lea eax, [ebp + 0x15]
		jbe L_loop_done
	L_loop:
		movsx edx, byte ptr [eax]
		movsx esi, byte ptr [eax + 1]
		inc eax
		xor ecx, ecx
		inc eax
		mov cx, word ptr [eax]
		add eax, 2
		add ecx, edi
		dec edx
		je L_size1
		dec edx
		je L_size2
		sub edx, 2
		jne L_loop_next
		test esi, esi
		jbe L_loop_next
	L_loop_size4:
		mov edx, dword ptr [eax]
		add eax, 4
		add dword ptr [ecx], edx
		add ecx, 4
		dec esi
		jne L_loop_size4
		jmp L_loop_next
	L_size2:
		test esi, esi
		jbe L_loop_next
	L_loop_size2_inner:
		mov dx, word ptr [eax]
		add eax, 2
		add word ptr [ecx], dx
		add ecx, 2
		dec esi
		jne L_loop_size2_inner
		jmp L_loop_next
	L_size1:
		test esi, esi
		jbe L_loop_next
	L_loop_size1_inner:
		mov dl, byte ptr [eax]
		add byte ptr [ecx], dl
		inc eax
		inc ecx
		dec esi
		jne L_loop_size1_inner
	L_loop_next:
		xor ecx, ecx
		inc ebx
		mov cl, byte ptr [ebp + 0x14]
		cmp ebx, ecx
		jb L_loop
	L_loop_done:
		mov eax, dword ptr [esp + 0x20]
		pop edi
		test eax, eax
		pop ebx
		je L_done
		mov byte ptr [eax], 1
	L_done:
		pop esi
		xor eax, eax
		pop ebp
		add esp, 8
		ret
	}
}
#else
int __cdecl cm_ExChangeAttribute(int cmd, char *result)
{
	void* pv8;
	void* pv4;
	int* resolved;
	register char* src;
	char* entity;
	char* dst2;
	unsigned short* puVar5;
	int field;
	int ok;
	unsigned int n;
	int size;
	unsigned int i;

	field = gm_GetFieldByType((char*)cmd, *(int*)(cmd + 0x10));
	ok = gm_ResolveEntityById(&resolved, &pv8, &pv4, field);
	if (ok == 0) {
		LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, 0x31f7,
		                   s_cm_ExChangeAttribute___Invalid_I_1002d0b0, 1);
		return 1;
	}
	*(int*)(cmd + 0x10) = field;
	if (resolved != 0)
		entity = (char*)resolved;
	else if (pv8 != 0)
		entity = (char*)pv8;
	else
		entity = (char*)pv4;
	src = (char*)(cmd + 0x15);
	i = 0;
	if (*(unsigned char*)(cmd + 0x14) > 0) {
		do {
			size = *(char*)src;
			n = *(char*)(src + 1);
			src++;
			puVar5 = (unsigned short*)(src + 1);
			src++;
			dst2 = entity + *puVar5;
			src += 2;
			switch (size) {
			case 1:
				while (n > 0) {
					*dst2 += *src;
					src++;
					dst2++;
					n--;
				}
				break;
			case 2:
				while (n > 0) {
					*(short*)dst2 += *(short*)src;
					src += 2;
					dst2 += 2;
					n--;
				}
				break;
			case 4:
				while (n > 0) {
					*(int*)dst2 += *(int*)src;
					src += 4;
					dst2 += 4;
					n--;
				}
				break;
			}
			i++;
		} while (i < (unsigned int)*(unsigned char*)(cmd + 0x14));
	}
	if (result != 0)
		*result = 1;
	return 0;
}
#endif
