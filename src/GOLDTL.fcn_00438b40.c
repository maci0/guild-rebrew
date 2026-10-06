extern int g_6b8014;
extern int g_67a370;

void __cdecl fcn_00438af0(unsigned char a);
void __cdecl fcn_00438ac0(char* p, int a);
void __cdecl fcn_00437ac0(int list, char* p, int mask, void(__cdecl* fn)(void));
void __cdecl fcn_00456df0(void);

// FUNCTION: GOLD 0x0043b790
// FUNCTION: GOLDTL 0x438b40
void __cdecl fcn_00438b40(char* p, int* v)
{
	if (p == ((char*)g_6b8014)) {
		fcn_00438af0(1);
	} else {
		fcn_00438ac0(p, 1);
	}
	fcn_00437ac0(g_67a370, p, 0xc0, fcn_00456df0);
	*(int*) (p + 0x4c) = v[0];
	*(int*) (p + 0x50) = v[1];
	*(int*) (p + 0x54) = v[2];
}
