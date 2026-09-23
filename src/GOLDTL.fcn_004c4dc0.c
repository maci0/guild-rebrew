// GLOBAL: GOLDTL 0x68a9d0
extern char g_68a9d0[];
// GLOBAL: GOLD 0x60bd68
extern char g_68a9d0[];
// GLOBAL: GOLDTL 0x68a9d4
extern char g_68a9d4[];
// GLOBAL: GOLD 0x60bd6c
extern char g_68a9d4[];
// GLOBAL: GOLDTL 0x68a9d8
extern char g_68a9d8[];
// GLOBAL: GOLD 0x60bd70
extern char g_68a9d8[];
// FUNCTION: GOLD 0x004c4450
// SIZE: 48
// FUNCTION: GOLDTL 0x4c4dc0
// SIZE: 37

int __cdecl fcn_004c4dc0(int a1, int a2)
{
	if (a2 == -2) {
		return *(int*) g_68a9d0;
	}
	if (a2 == -3) {
		return *(int*) g_68a9d4;
	}
	if (a2 == -4) {
		return *(int*) g_68a9d8;
	}
	return a2;
}
