// FUNCTION: GOLD 0x0043b820
// FUNCTION: GOLDTL 0x438c40

extern int g_67a370;

void __cdecl fcn_00438ac0(char*, int);
void __cdecl fcn_00437ac0(int, char*, int, void*);
void __cdecl fcn_00456df0(void);

void __cdecl fcn_00438c40(char* o, int* v)
{
	fcn_00438ac0(o, 1);
	fcn_00437ac0(g_67a370, o, 0xc0, fcn_00456df0);
	*(int*) (o + 0x78) = v[0];
	*(int*) (o + 0x7c) = v[1];
	*(int*) (o + 0x80) = v[2];
}
