extern int g_6b8010;
// FUNCTION: GOLDTL 0x5986f0
// SIZE: 79

void __cdecl fcn_004432d0(int, int);
void __cdecl fcn_00455540(int, void*, int);

void __cdecl fcn_005986f0(int a1, int a2)
{
	int v[4];
	int saved;

	saved = g_6b8010;
	fcn_004432d0(0, 1);
	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
	fcn_00455540(a2, v, a1);
	fcn_004432d0(saved, 1);
}
