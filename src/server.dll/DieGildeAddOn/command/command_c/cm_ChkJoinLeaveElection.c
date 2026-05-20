
#ifdef __clang__
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wint-to-pointer-cast"
#pragma clang diagnostic ignored "-Wpointer-to-int-cast"
#pragma clang diagnostic ignored "-Wvoid-pointer-to-int-cast"
#endif


extern int g_1003546c;
extern char g_100358a0[];
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);

/* Validation handler: checks preconditions for joining or
 * leaving an election. For 'join', verifies player isn't already
 * in the election slots and an empty slot exists. For 'leav',
 * verifies the player is actually in a slot. */

// FUNCTION: SERVER 0x1000d110
__declspec(naked) int __cdecl cm_ChkJoinLeaveElection(int* cmd)
{
	(void) cmd;
	__asm {
		push esi
		mov esi, dword ptr [esp + 8]
		mov eax, dword ptr [esi + 0x10]
		cmp eax, 0x6a6f696e
		jne L_try_leav
		mov eax, dword ptr [esi + 0x18]
		push eax
		push 1
		push 1
		call gm_StartFilteredEntitySearch
		add esp, 0xc
		test eax, eax
		je L_fail
		mov ecx, dword ptr [eax + 0x5d]
		push 0x12d
		push 0
		push 6
		push 2
		push ecx
		call gm_StartEntityQuery
		add esp, 0x14
		test eax, eax
		je L_fail
		mov esi, dword ptr [esi + 0x14]
		lea edx, [eax + 0x1c]
		xor ecx, ecx
		mov eax, edx
	L_join_scan1:
		cmp dword ptr [eax], esi
		je L_fail
		inc ecx
		add eax, 4
		cmp ecx, 4
		jl L_join_scan1
		xor eax, eax
		mov ecx, edx
	L_join_scan2:
		cmp dword ptr [ecx], -1
		je L_join_check
		inc eax
		add ecx, 4
		cmp eax, 4
		jl L_join_scan2
	L_fail:
		mov eax, 1
		pop esi
		ret
	L_join_check:
		cmp eax, 4
		jge L_fail
		xor eax, eax
		pop esi
		ret
	L_try_leav:
		cmp eax, 0x6c656176
		jne L_try_cler
		mov edx, dword ptr [esi + 0x18]
		push edx
		push 1
		push 1
		call gm_StartFilteredEntitySearch
		add esp, 0xc
		test eax, eax
		je L_fail
		mov eax, dword ptr [eax + 0x5d]
		push 0x12d
		push 0
		push 6
		push 2
		push eax
		call gm_StartEntityQuery
		add esp, 0x14
		test eax, eax
		je L_fail
		mov esi, dword ptr [esi + 0x14]
		xor ecx, ecx
		add eax, 0x1c
	L_leav_scan:
		cmp dword ptr [eax], esi
		je L_leav_check
		inc ecx
		add eax, 4
		cmp ecx, 4
		jl L_leav_scan
		mov eax, 1
		pop esi
		ret
	L_leav_check:
		cmp ecx, 4
		jge L_fail
		xor eax, eax
		pop esi
		ret
	L_try_cler:
		cmp eax, 0x636c6572
		jne L_fail
		mov ecx, dword ptr [esi + 0x18]
		push ecx
		push 1
		push 1
		call gm_StartFilteredEntitySearch
		add esp, 0xc
		test eax, eax
		je L_fail
		mov cx, word ptr [eax + 0x27]
		_emit 0x66
		_emit 0x81
		_emit 0xf9
		_emit 0xff
		_emit 0xff
		je L_cler_query
		and ecx, 0xffff
		lea ecx, [ecx + ecx*2]
		lea ecx, [ecx + ecx*4]
		lea edx, [ecx + ecx*8]
		lea ecx, [edx*4 + 0x100358a0]
		test ecx, ecx
		je L_cler_query
		cmp ecx, dword ptr g_1003546c
		je L_cler_query
		mov dl, byte ptr [ecx + 8]
		test dl, dl
		je L_cler_query
		cmp byte ptr [ecx + 2], 0xf
		jne L_fail
	L_cler_query:
		mov eax, dword ptr [eax + 0x5d]
		push 0x12d
		push 0
		push 6
		push 2
		push eax
		call gm_StartEntityQuery
		add esp, 0x14
		neg eax
		sbb eax, eax
		inc eax
		pop esi
		ret
	}
}
