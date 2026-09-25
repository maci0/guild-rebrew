extern int g_67a370;

char __cdecl fcn_00442cb0(void* p, int arg);
void __cdecl fcn_004379a0(int list, int a, int mask, char(__cdecl* fn)(void*, int), int arg);

// FUNCTION: GOLD 0x00447300
// SIZE: 51
// FUNCTION: GOLDTL 0x442d50
// SIZE: 51
char __cdecl fcn_00442d50(int a, unsigned char b)
{
	if (a != 0) {
		fcn_004379a0(g_67a370, a, 0x3ff, fcn_00442cb0, b);
		return 1;
	}
	return 0;
}
