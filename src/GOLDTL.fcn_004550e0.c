extern int g_67a370;

void __cdecl fcn_00454560(int* n);
char __cdecl fcn_004545c0(void* p, int* n);
void __cdecl fcn_004379a0(int list, int a, int mask, char(__cdecl* fn)(void*, int*), int* arg);
void __cdecl fcn_00454850(int* n, int a, int b, int c);

// FUNCTION: GOLD 0x004587a0
// SIZE: 81
// FUNCTION: GOLDTL 0x4550e0
// SIZE: 81
void __cdecl fcn_004550e0(int a1, int* n)
{
	int i;

	if (n != 0) {
		for (i = 0; i < 4; i++) {
			fcn_00454560((int*) n[i]);
		}
		fcn_004379a0(g_67a370, a1, n[0x11] | 0x200, fcn_004545c0, n);
		fcn_00454850(n, n[0xd], 1, n[0xe]);
	}
}
