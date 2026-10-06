// FUNCTION: GOLD 0x577880
// FUNCTION: GOLDTL 0x0057fe50

extern char g_7f4ca0[];
extern unsigned short g_774970;

void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl fcn_004c51a0(int, int, int, int);

void __cdecl fcn_0057fe50(int a)
{
	char* p;

	p = g_7f4ca0 + g_774970 * 540;
	if (a == 0) {
		fcn_004c5420(*(int*) (p + 4), 0x1c8, 4, 0x4000, 0);
		fcn_004c51a0(*(int*) (p + 4), -1, 0, 0x3e80);
	}
}
