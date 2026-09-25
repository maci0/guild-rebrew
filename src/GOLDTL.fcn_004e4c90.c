// FUNCTION: GOLDTL 0x4e4c90
// SIZE: 111

extern int g_772f3c;
extern int g_68bfb8;
extern int g_772f30;
extern int g_774654;
extern int g_772f40;

int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_004cfca0(void);
void __cdecl fcn_004e5140(int);

void __cdecl fcn_004e4c90(int dur)
{
	int end;

	end = g_772f30;
	if (g_772f3c != 0)
		return;
	if (fcn_005373e0(fcn_004e4c90, g_68bfb8 | 0x8000) == 0)
		return;
	do {
		if (g_772f30 >= end + dur)
			g_774654 = 1;
		fcn_004cfca0();
		fcn_004e5140(g_772f40);
	} while (fcn_005373e0(fcn_004e4c90, g_68bfb8 | 0x8000) != 0);
}
