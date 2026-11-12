
/* fcn_005a89a0: load edx=a; call fcn_005a8600(*(int*)(edx+1)); if eax!=0 call fcn_005b1980(edx, eax). */

int __cdecl fcn_005a8600(int);
int __cdecl fcn_005b1980(void*, int);

/* MSVC6 /O2 homes `a` in esi across the call. The image keeps it in edx. */
void __cdecl fcn_005a89a0(char* a)
{
	(void) a;
	__asm {
		mov edx, dword ptr [esp+4]
		mov eax, dword ptr [edx+1]
		push eax
		call fcn_005a8600
		add esp, 4
		test eax, eax
		je done
		push eax
		push edx
		call fcn_005b1980
		add esp, 8
	done:
	}
}
