extern int g_67a370;

void __cdecl fcn_00438ac0(char* p, int a);
void __cdecl fcn_00437ac0(int list, char* p, int mask, void(__cdecl* fn)(void));
void __cdecl fcn_00456df0(void);

// FUNCTION: GOLDTL 0x438bd0
void __cdecl fcn_00438bd0(char* p, int* v)
{
	fcn_00438ac0(p, 1);
	fcn_00437ac0(g_67a370, p, 0xc0, fcn_00456df0);
	*(int*) (p + 0x6c) = v[0];
	*(int*) (p + 0x70) = v[1];
	*(int*) (p + 0x74) = v[2];
}
