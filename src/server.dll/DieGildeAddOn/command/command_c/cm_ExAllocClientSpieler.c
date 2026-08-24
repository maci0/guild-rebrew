/* Ghidra decompilation reference:
 */

#include "../command_internal.h"
#include "../../../Units/Error/error.h"

ushort __cdecl gm_CreateEntityFromParents(uint, int, int, ushort, int, uint, uint, uint);
char* __cdecl strncpy(char*, const char*, unsigned int);

/* Execution handler: allocates a client-side player entity.
 * Similar to cm_ExAllocSpieler but for client-connected players,
 * updating player slot flags and setting connection state. */

/*
 * NOTE: blocked from C conversion (result-register role, see
 * docs/msvc6-allocator.md "cm_ExAllocClientSpieler").  Semantically correct
 * C (best 142/361) preserved:
 *
 *   int __cdecl cm_ExAllocClientSpieler(int cmd, char* result)
 *   {
 *       unsigned int entity;  char* rec;  short* t;  char* r2;  int f;
 *       *(int*) (cmd + 0x10) = g_timestamp_0b6c;
 *       *(int*) (cmd + 0x45) = rand();
 *       srand(*(int*) (cmd + 0x22));
 *       entity = gm_CreateEntityFromParents(result ? 6 : 7,
 *           *(int*) (cmd + 0x14), *(int*) (cmd + 0x18),
 *           *(unsigned short*) (cmd + 0x1c), 0,
 *           (unsigned char) *(char*) (cmd + 0x1e), 0,
 *           (unsigned char) *(char*) (cmd + 0x23));
 *       entity = entity & 0xffff;
 *       if (entity == 0xffff) {
 *           LogMessageInternal((char*) 0x1002c748, 0x290f, (char*) 0x1002cbd4, 1);
 *           return 1;
 *       }
 *       LogMessageInternal((char*) 0x1002c748, 0x2917, (char*) 0x1002cbbc, 1);
 *       rec = g_static_entity_table_358a0 + entity * 0x21c;
 *       f = 0x99099 * (unsigned char) *(char*) (cmd + 3);
 *       *(int*) (0x10442d00 + f * 4) = *(int*) (rec + 4);
 *       strncpy(rec + 0x30, (char*) cmd + 0x25, 0x10);
 *       t = gm_GetEntityTableEntry(rec);
 *       if (t != 0) {
 *           *(unsigned short*) t = *(unsigned short*) (rec + 0x50);
 *           strncpy((char*) t + 2, (char*) cmd + 0x35, 0x10);
 *           strncpy(rec + 0x40, (char*) cmd + 0x35, 0x10);
 *           r2 = (char*) gm_LookupEntityRecordById(*(int*) (rec + 0x60));
 *           if (r2 != 0) strncpy(r2 + 0x40, (char*) cmd + 0x35, 0x10);
 *       }
 *       *(int*) (rec + 0x54) = *(int*) (cmd + 0x1f);
 *       *(unsigned char*) (rec + 0xc) = *(unsigned char*) (cmd + 0x24);
 *       if (result != (char*) 0) {
 *           result[0] = 1;
 *           result[1] = 1;
 *           *(char**) (result + 6) = rec;
 *       }
 *       return 0;
 *   }
 */
// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
// FUNCTION: SERVER 0x1000d570
#ifdef REBREW_ALLOW_NAKED
// NAKED verification build: byte-identical to original 0x1000d570.
// C conversion blocker (docs/msvc6-allocator.md line 1210): result-
// register role — the reference's `result ? 6 : 7` first arg is
// materialized via `mov ebx,[esp+0x18]; mov eax,ebx; neg eax;
// sbb eax,eax; ... add eax,7` (eax = result!=0 ? -1 : 0, then +7),
// and the store-multiply chain for entity*0x21c differs; best C 142/361.
__declspec(naked) int __cdecl cm_ExAllocClientSpieler(int cmd, char* result)
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
		push edi
		mov edi, dword ptr [esp + 0x10]
		mov dword ptr [edi + 0x10], eax
		call rand
		mov ecx, dword ptr [edi + 0x22]
		mov dword ptr [edi + 0x45], eax
		push ecx
		call srand
		mov ebx, dword ptr [esp + 0x18]
		mov eax, ebx
		neg eax
		sbb eax, eax
		xor edx, edx
		mov dl, byte ptr [edi + 0x23]
		xor ecx, ecx
		mov cl, byte ptr [edi + 0x1e]
		push edx
		mov dx, word ptr [edi + 0x1c]
		push 0
		push ecx
		mov ecx, dword ptr [edi + 0x18]
		push 0
		push edx
		mov edx, dword ptr [edi + 0x14]
		add eax, 7
		push ecx
		push edx
		push eax
		call gm_CreateEntityFromParents
		mov si, ax
		add esp, 0x24
		and esi, 0xffff
		cmp esi, 0xffff
		jne L_ok
		push 1
		push 0x1002cbd4
		push 0x290f
		push 0x1002c748
		call LogMessageInternal
		add esp, 0x10
		mov eax, 1
		pop edi
		pop esi
		pop ebx
		ret
	L_ok:
		push ebp
		push 1
		push 0x1002cbbc
		push 0x2917
		push 0x1002c748
		call LogMessageInternal
		lea eax, [esi + esi*2]
		xor ecx, ecx
		mov cl, byte ptr [edi + 3]
		lea edx, [edi + 0x25]
		lea eax, [eax + eax*4]
		push 0x10
		push edx
		lea esi, [eax + eax*8]
		mov eax, ecx
		shl eax, 4
		add eax, ecx
		shl eax, 8
		add eax, ecx
		shl eax, 4
		add eax, ecx
		shl esi, 2
		lea eax, [eax + eax*8]
		mov ecx, dword ptr [esi + 0x100358a4]
		mov dword ptr [eax*4 + 0x10442d00], ecx
		lea eax, [esi + 0x100358d0]
		push eax
		call strncpy
		lea ebp, [esi + 0x100358a0]
		push ebp
		call gm_GetEntityTableEntry
		add esp, 0x20
		test eax, eax
		je L_skip_table
		mov cx, word ptr [esi + 0x100358f0]
		lea ebx, [edi + 0x35]
		mov word ptr [eax], cx
		push 0x10
		add eax, 2
		push ebx
		push eax
		call strncpy
		push 0x10
		lea edx, [esi + 0x100358e0]
		push ebx
		push edx
		call strncpy
		mov eax, dword ptr [esi + 0x10035900]
		push eax
		call gm_LookupEntityRecordById
		add esp, 0x1c
		test eax, eax
		je L_skip_record
		push 0x10
		add eax, 0x40
		push ebx
		push eax
		call strncpy
		add esp, 0xc
	L_skip_record:
		mov ebx, dword ptr [esp + 0x18]
	L_skip_table:
		mov ecx, dword ptr [edi + 0x1f]
		mov dword ptr [esi + 0x100358f4], ecx
		mov dl, byte ptr [edi + 0x24]
		test ebx, ebx
		mov byte ptr [esi + 0x100358ac], dl
		je L_done
		mov byte ptr [ebx], 1
		mov byte ptr [ebx + 1], 1
		mov dword ptr [ebx + 6], ebp
	L_done:
		pop ebp
		pop edi
		pop esi
		xor eax, eax
		pop ebx
		ret
	}
}
#else
extern unsigned char g_static_entity_table_358a0[];
int __cdecl cm_ExAllocClientSpieler(int cmd, char* result)
{
	unsigned int entity;
	char* rec;
	short* t;
	char* r2;
	int f;

	*(int*)(cmd + 0x10) = g_timestamp_0b6c;
	*(int*)(cmd + 0x45) = rand();
	srand(*(int*)(cmd + 0x22));
	entity = gm_CreateEntityFromParents(result ? 6 : 7,
		*(int*)(cmd + 0x14), *(int*)(cmd + 0x18),
		*(unsigned short*)(cmd + 0x1c), 0,
		(unsigned char)*(char*)(cmd + 0x1e), 0,
		(unsigned char)*(char*)(cmd + 0x23));
	entity = entity & 0xffff;
	if (entity == 0xffff) {
		LogMessageInternal((char*)0x1002c748, 0x290f, (char*)0x1002cbd4, 1);
		return 1;
	}
	LogMessageInternal((char*)0x1002c748, 0x2917, (char*)0x1002cbbc, 1);
	rec = (char*)g_static_entity_table_358a0 + entity * 0x21c;
	f = 0x99099 * (unsigned char)*(char*)(cmd + 3);
	*(int*)(0x10442d00 + f * 4) = *(int*)(rec + 4);
	strncpy(rec + 0x30, (char*)cmd + 0x25, 0x10);
	t = gm_GetEntityTableEntry(rec);
	if (t != 0) {
		*(unsigned short*)t = *(unsigned short*)(rec + 0x50);
		strncpy((char*)t + 2, (char*)cmd + 0x35, 0x10);
		strncpy(rec + 0x40, (char*)cmd + 0x35, 0x10);
		r2 = (char*)gm_LookupEntityRecordById(*(int*)(rec + 0x60));
		if (r2 != 0)
			strncpy(r2 + 0x40, (char*)cmd + 0x35, 0x10);
	}
	*(int*)(rec + 0x54) = *(int*)(cmd + 0x1f);
	*(unsigned char*)(rec + 0xc) = *(unsigned char*)(cmd + 0x24);
	if (result != (char*)0) {
		result[0] = 1;
		result[1] = 1;
		*(char**)(result + 6) = rec;
	}
	return 0;
}
#endif
