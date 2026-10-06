// FUNCTION: GOLD 0x00404dd0
// FUNCTION: GOLDTL 0x4056f0

extern int g_6b8014;
extern int g_6b5cbc;
extern int g_6b5cc0;
void __cdecl fcn_004055a0(int, int, float*, float*);
void __cdecl fcn_00433780(int);
void __cdecl fcn_00412cf0(int, float*, float*, int, int);

void __cdecl fcn_004056f0(int a1, int a2, int a3)
{
	float a[3];
	float b[4];

	if (a1 != 0) {
		fcn_004055a0(a1, a2, b, a);
		fcn_00433780(g_6b8014);
		g_6b5cbc = 0;
		g_6b5cc0 = 0;
		fcn_00412cf0(g_6b8014, b, a, a3, 0x28);
	}
}
