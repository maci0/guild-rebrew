
#include "../command_internal.h"
#include "../../../Units/Error/error.h"

extern char s_cm_ExClearLagerslot___Invalid__L_1002d088[];
extern char s_cm_ExClearLagerslot___Lager_has_n_1002d054[];
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
int __cdecl gm_RemoveObjectByType(void**, unsigned int);

/*
 * Ghidra decompilation reference:
 * /+ [rebrew] FUNCTION: MATCHING
 *    Origin: GAME
 *    Size: 191B
 *    CFlags:
 *    Symbol: _cm_ExClearLagerslot
 *    Files: DieGildeAddOn/command/command.c * / *
 * int __cdecl cm_ExClearLagerslot(short *param_1,uchar *param_2)
 *
 * {
 *   short *psVar1;
 *   int iVar2;
 *   ushort *puVar3;
 *   uint line;
 *   char *msg;
 *
 *   psVar1 = param_1;
 *   iVar2 = gm_GetFieldByType((char *)param_1,*(int *)(param_1 + 8));
 *   *(int *)(psVar1 + 8) = iVar2;
 *   iVar2 = gm_ResolveEntityById((void **)0x0,&param_1,(void **)0x0,iVar2);
 *   if (iVar2 == 0) {
 *     msg = s_cm_ExClearLagerslot___Invalid__L_1002d088;
 *     line = 0x314b;
 *   }
 *   else {
 *     if ((*param_1 == 0x2a) || (*param_1 == 0x116)) {
 *       puVar3 = gm_StartEntityQuery(*(int *)(param_1 + 10),1,0,(uint)(ushort)psVar1[10]);
 *       if (puVar3 == (ushort *)0x0) {
 *         return 1;
 *       }
 *       if (*(int *)(puVar3 + 7) != 1) {
 *         return 1;
 *       }
 *       gm_RemoveObjectByType((char **)(param_1 + 10),(uint)(ushort)psVar1[10]);
 *       if (param_2 != (uchar *)0x0) {
 *         *param_2 = '\x01';
 *       }
 *       return 0;
 *     }
 *     msg = s_cm_ExClearLagerslot___Lager_has_n_1002d054;
 *     line = 0x3155;
 *   }
 *   LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748,line,msg,1);
 *   return 1;
 * }
 */

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
// FUNCTION: SERVER 0x1000e690
#ifdef REBREW_ALLOW_NAKED
// NAKED verification build: byte-identical to original 0x1000e690.
// C conversion blocker (docs/msvc6-allocator.md Finding 42): the
// Finding 7 family store materialization — the reference keeps the
// short* base in esi and folds `mov [esi+0x10],eax` while passing
// &cmd in the middle of gm_ResolveEntityById(0, &cmd, 0, field);
// every C emits `mov eax,[esp+4]` first and CSE-hoists
// `lea esi,[eax+0x10]`, shifting the resolve arg pushes.
__declspec(naked) int __cdecl cm_ExClearLagerslot(short* cmd, uchar* result)
{
	(void) cmd;
	(void) result;
	__asm {
		push esi
		mov esi, dword ptr [esp + 8]
		mov eax, dword ptr [esi + 0x10]
		push eax
		push esi
		call gm_GetFieldByType
		push eax
		lea ecx, [esp + 0x14]
		push 0
		push ecx
		push 0
		mov dword ptr [esi + 0x10], eax
		call gm_ResolveEntityById
		add esp, 0x18
		test eax, eax
		jne L_resolved
		push 1
		push 0x1002d088
		push 0x314b
		jmp L_log
	L_resolved:
		mov eax, dword ptr [esp + 8]
		mov cx, word ptr [eax]
		cmp cx, 0x2a
		je L_type_ok
		cmp cx, 0x116
		je L_type_ok
		push 1
		push 0x1002d054
		push 0x3155
	L_log:
		push 0x1002c748
		call LogMessageInternal
		add esp, 0x10
		mov eax, 1
		pop esi
		ret
	L_type_ok:
		mov eax, dword ptr [eax + 0x14]
		xor edx, edx
		mov dx, word ptr [esi + 0x14]
		push edx
		push 0
		push 1
		push eax
		call gm_StartEntityQuery
		add esp, 0x10
		test eax, eax
		jne L_check_count
		mov eax, 1
		pop esi
		ret
	L_check_count:
		cmp dword ptr [eax + 0xe], 1
		je L_remove
		mov eax, 1
		pop esi
		ret
	L_remove:
		mov edx, dword ptr [esp + 8]
		xor ecx, ecx
		mov cx, word ptr [esi + 0x14]
		add edx, 0x14
		push ecx
		push edx
		call gm_RemoveObjectByType
		mov eax, dword ptr [esp + 0x14]
		add esp, 8
		test eax, eax
		je L_done
		mov byte ptr [eax], 1
	L_done:
		xor eax, eax
		pop esi
		ret
	}
}
#else
int __cdecl cm_ExClearLagerslot(short* cmd, uchar* result)
{
	short* psVar1;
	int field;
	int ok;
	unsigned short* puVar3;
	uint line;
	char* msg;

	psVar1 = cmd;
	field = gm_GetFieldByType((char*)cmd, *(int*)(cmd + 8));
	*(int*)(psVar1 + 8) = field;
	ok = gm_ResolveEntityById(0, (void**)&cmd, 0, field);
	if (ok == 0) {
		msg = s_cm_ExClearLagerslot___Invalid__L_1002d088;
		line = 0x314b;
	} else {
		if ((*cmd == 0x2a) || (*cmd == 0x116)) {
			puVar3 = gm_StartEntityQuery(*(int*)(cmd + 10), 1, 0, (uint)(ushort)psVar1[10]);
			if (puVar3 == 0) {
				return 1;
			}
			if (*(int*)(puVar3 + 7) != 1) {
				return 1;
			}
			gm_RemoveObjectByType((char**)(cmd + 10), (uint)(ushort)psVar1[10]);
			if (result != 0) {
				*result = 1;
			}
			return 0;
		}
		msg = s_cm_ExClearLagerslot___Lager_has_n_1002d054;
		line = 0x3155;
	}
	LogMessageInternal(s_D__Develop_DieGildeAddOn_command_1002c748, line, msg, 1);
	return 1;
}
#endif
