// FUNCTION: GOLD 0x005774f0
// SIZE: 92
// FUNCTION: GOLDTL 0x57fac0
// SIZE: 92

extern char g_7f4ca4[];
extern unsigned short g_774970;
extern unsigned char g_773d75;

char* __cdecl fcn_00503d10(int);
void __cdecl fcn_004c51a0(int, int, int, int);
void __cdecl fcn_004c51f0(int, int, int, int, char, int);

void __cdecl fcn_0057fac0(int a)
{
	char* e;

	if (a == 0) {
		e = fcn_00503d10(0x155);
		fcn_004c51a0(*(int*) (g_7f4ca4 + *(unsigned short*) ((char*)&g_774970) * 0x21c), -1, 0, 0x2bc0);
		fcn_004c51f0(*(int*) (e + 2), -1, 0x155, 3, g_773d75, 0);
	}
}
