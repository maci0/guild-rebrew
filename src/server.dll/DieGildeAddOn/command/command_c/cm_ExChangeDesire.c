
#include "../command_internal.h"
#include "../../../Units/Error/error.h"

extern double _g_stat_min_d;
extern double _g_stat_max_d;

/* Execution handler: modifies a character's desire/need stat.
 * Reads entity and stat index from the command, applies a delta
 * or sets an absolute value to the desire field. */

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
// FUNCTION: SERVER 0x1000e9c0
#ifdef REBREW_ALLOW_NAKED
// NAKED verification build: byte-identical to original 0x1000e9c0.
// C conversion blocker (docs/msvc6-allocator.md Finding 40): the
// Finding 7 family store materialization (base copy + &cmd + folded
// `mov [edi+0x10],eax` — every C emits lea esi,[eax+0x10] with 3
// prologue pushes instead of the deferred ebx/esi) PLUS the Finding 35
// FPU clamp re-compare (the clamp routes through a second fcom max
// after already knowing stat<max).
__declspec(naked) int __cdecl cm_ExChangeDesire(uchar* cmd, uchar* result)
{
	(void) cmd;
	(void) result;
	__asm {
		push edi
		mov edi, dword ptr [esp + 8]
		mov eax, dword ptr [edi + 0x10]
		push eax
		push edi
		call gm_GetFieldByType
		lea ecx, [esp + 0x10]
		push eax
		push ecx
		push 0
		push 0
		mov dword ptr [edi + 0x10], eax
		call gm_ResolveEntityById
		add esp, 0x18
		test eax, eax
		jne L_resolved
		push 1
		push 0x1002d0f4
		push 0x33af
		push 0x1002c748
		call LogMessageInternal
		add esp, 0x10
		mov eax, 1
		pop edi
		ret
	L_resolved:
		mov al, byte ptr [edi + 0x14]
		push ebx
		xor ebx, ebx
		lea edx, [edi + 0x15]
		test al, al
		jbe L_after_loop
		push esi
	L_loop:
		xor eax, eax
		mov al, byte ptr [edx]
		inc edx
		fld dword ptr [edx]
		lea ecx, [eax + eax*2 + 0x24]
		mov eax, dword ptr [esp + 0x10]
		shl ecx, 2
		add edx, 4
		fadd dword ptr [ecx + eax]
		fstp dword ptr [ecx + eax]
		mov esi, dword ptr [esp + 0x10]
		fld dword ptr [ecx + esi]
		fcomp _g_stat_max_d
		fnstsw ax
		test ah, 1
		jne L_clamp_chk
		fld dword ptr [ecx + esi]
		fcomp _g_stat_min_d
		fnstsw ax
		test ah, 1
		je L_use_max
	L_clamp_chk:
		fld dword ptr [ecx + esi]
		fcomp _g_stat_max_d
		fnstsw ax
		test ah, 1
		je L_load_min
		fld _g_stat_max_d
		jmp L_store
	L_load_min:
		fld dword ptr [ecx + esi]
		jmp L_store
	L_use_max:
		fld _g_stat_min_d
	L_store:
		fstp dword ptr [ecx + esi]
		xor eax, eax
		inc ebx
		mov al, byte ptr [edi + 0x14]
		cmp ebx, eax
		jb L_loop
		pop esi
	L_after_loop:
		mov eax, dword ptr [esp + 0x10]
		pop ebx
		test eax, eax
		je L_done
		mov byte ptr [eax], 1
	L_done:
		xor eax, eax
		pop edi
		ret
	}
}
#else
extern double _g_stat_min_d;
extern double _g_stat_max_d;

int __cdecl cm_ExChangeDesire(uchar* cmd, uchar* result)
{
	int field;
	int ok;
	int idx;
	int i;
	int entity;
	uchar* src;
	float* stat;
	int base;

	base = (int)cmd;
	field = gm_GetFieldByType((char*)cmd, *(int*)(cmd + 0x10));
	ok = gm_ResolveEntityById(0, 0, (void**)&cmd, field);
	*(int*)(base + 0x10) = field;
	if (ok == 0) {
		LogMessageInternal((char*)0x1002c748, 0x33af, (char*)0x1002d0f4, 1);
		return 1;
	}
	entity = (int)cmd;
	src = (uchar*)(base + 0x15);
	i = 0;
	if (*(uchar*)(base + 0x14) > 0) {
		do {
			idx = *src;
			src++;
			stat = (float*)(entity + (idx * 3 + 0x24) * 4);
			*stat += *(float*)src;
			src += 4;
			if (*stat > _g_stat_max_d)
				*stat = _g_stat_max_d;
			else if (*stat < _g_stat_min_d)
				*stat = _g_stat_min_d;
			i++;
		} while (i < (unsigned int)*(uchar*)(base + 0x14));
	}
	if (result != 0)
		*result = 1;
	return 0;
}
#endif
