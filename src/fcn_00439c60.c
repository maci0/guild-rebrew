// GLOBAL: GOLDTL 0x6b8014
extern char g_6b8014[];
// GLOBAL: GOLD 0xfc2dec
extern char g_6b8014[];
// FUNCTION: GOLD 0x0043cbe0
// SIZE: 42
// FUNCTION: GOLDTL 0x439c60
// SIZE: 42

void __cdecl fcn_00438af0(int);

void __cdecl fcn_00439c60(int a1)
{
	if (a1 == *(int*) g_6b8014) {
		return;
	}
	if (*(int*) (a1 + 0x218) != 3) {
		return;
	}
	*(int*) g_6b8014 = a1;
	fcn_00438af0(0);
}
