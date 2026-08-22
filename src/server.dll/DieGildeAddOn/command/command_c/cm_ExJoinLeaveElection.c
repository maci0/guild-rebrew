extern int g_1003546c;
unsigned short* __cdecl gm_StartEntityQuery(int, int, int, ...);
unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);

/* Execution handler: processes join/leave actions for elections.
 * For 'join', finds an empty election slot and assigns the player.
 * For 'leav', finds the player's slot and clears it. */

// CFLAGS: /O2 /Gd /DREBREW_ALLOW_NAKED
// FUNCTION: SERVER 0x1000fd50
__declspec(naked) int __cdecl cm_ExJoinLeaveElection(int cmd, char* result)
{
	(void) cmd;
	(void) result;
	__asm {
		push ebp
		push esi
		push edi
		mov edi, dword ptr [esp + 0x14]
		test edi, edi
		je L_no_param2
		mov byte ptr [edi], 2
		mov byte ptr [edi + 1], 0
		mov dword ptr [edi + 6], 0
	L_no_param2:
		mov ebp, dword ptr [esp + 0x10]
		mov eax, dword ptr [ebp + 0x10]
		cmp eax, 0x6a6f696e
		jne L_try_leav
		mov eax, dword ptr [ebp + 0x18]
		push eax
		push 1
		push 1
		call gm_StartFilteredEntitySearch
		add esp, 0xc
		test eax, eax
		je L_ret1
		mov ecx, dword ptr [eax + 0x5d]
		push 0x12d
		push 0
		push 6
		push 2
		push ecx
		call gm_StartEntityQuery
		add esp, 0x14
		test eax, eax
		je L_ret1
		mov edi, dword ptr [ebp + 0x14]
		lea esi, [eax + 0x1c]
		xor ecx, ecx
		mov edx, esi
	L_join_scan1:
		cmp dword ptr [edx], edi
		je L_ret1
		inc ecx
		add edx, 4
		cmp ecx, 4
		jl L_join_scan1
		xor ecx, ecx
		mov edx, esi
	L_join_scan2:
		cmp dword ptr [edx], -1
		je L_join_found
		inc ecx
		add edx, 4
		cmp ecx, 4
		jl L_join_scan2
	L_ret1:
		pop edi
		pop esi
		mov eax, 1
		pop ebp
		ret
	L_join_found:
		cmp ecx, 4
		jge L_ret1
		mov edx, dword ptr [esp + 0x14]
		test edx, edx
		je L_join_write
		mov byte ptr [edx], 1
	L_join_write:
		mov edx, dword ptr [ebp + 0x14]
		pop edi
		mov dword ptr [eax + ecx*4 + 0x1c], edx
		pop esi
		xor eax, eax
		pop ebp
		ret
	L_try_leav:
		cmp eax, 0x6c656176
		jne L_try_cler
		mov eax, dword ptr [ebp + 0x18]
		push eax
		push 1
		push 1
		call gm_StartFilteredEntitySearch
		add esp, 0xc
		test eax, eax
		je L_ret1
		mov ecx, dword ptr [eax + 0x5d]
		push 0x12d
		push 0
		push 6
		push 2
		push ecx
		call gm_StartEntityQuery
		add esp, 0x14
		test eax, eax
		je L_ret1
		mov esi, dword ptr [ebp + 0x14]
		xor ecx, ecx
		lea edx, [eax + 0x1c]
	L_leav_scan:
		cmp dword ptr [edx], esi
		je L_leav_found
		inc ecx
		add edx, 4
		cmp ecx, 4
		jl L_leav_scan
		pop edi
		pop esi
		mov eax, 1
		pop ebp
		ret
	L_leav_found:
		cmp ecx, 4
		jge L_ret1
		test edi, edi
		je L_leav_write
		mov byte ptr [edi], 1
	L_leav_write:
		pop edi
		mov dword ptr [eax + ecx*4 + 0x1c], 0xffffffff
		pop esi
		xor eax, eax
		pop ebp
		ret
	L_try_cler:
		cmp eax, 0x636c6572
		jne L_ret1
		mov edx, dword ptr [ebp + 0x18]
		push edx
		push 1
		push 1
		call gm_StartFilteredEntitySearch
		add esp, 0xc
		test eax, eax
		je L_ret1
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
		lea ecx, [ecx + ecx*8]
		lea ecx, [ecx*4 + 0x100358a0]
		test ecx, ecx
		je L_cler_query
		cmp ecx, dword ptr g_1003546c
		je L_cler_query
		mov dl, byte ptr [ecx + 8]
		test dl, dl
		je L_cler_query
		cmp byte ptr [ecx + 2], 0xf
		jne L_ret1
	L_cler_query:
		mov edx, dword ptr [eax + 0x5d]
		push 0x12d
		push 0
		push 6
		push 2
		push edx
		call gm_StartEntityQuery
		add esp, 0x14
		test eax, eax
		je L_ret1
		test edi, edi
		je L_cler_clear
		mov byte ptr [edi], 1
	L_cler_clear:
		add eax, 0x1c
		mov ecx, 4
	L_cler_loop:
		mov edx, dword ptr [eax]
		mov esi, dword ptr [ebp + 0x14]
		cmp edx, esi
		jne L_cler_no_clear
		mov dword ptr [eax], 0xffffffff
	L_cler_no_clear:
		add eax, 4
		dec ecx
		jne L_cler_loop
		pop edi
		pop esi
		xor eax, eax
		pop ebp
		ret
	}
}
