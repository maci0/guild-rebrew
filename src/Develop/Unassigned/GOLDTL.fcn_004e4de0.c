


extern int g_6b7fac;
extern int g_772f3c;
extern int g_68bfb8;
extern int g_774654;
extern int* g_772f40;

int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_004cfca0(void);
void __cdecl fcn_004e5140(int);

void __cdecl fcn_004e4de0(int secs)
{
	int start;
	double end;

	start = (*(unsigned int*)&g_6b7fac);
	if (g_772f3c != 0)
		return;
	if (fcn_005373e0(fcn_004e4de0, g_68bfb8 | 0x8000) == 0)
		return;
	end = secs * (1.0 / 14.0) + start;
	do {
		if ((*(unsigned int*)&g_6b7fac) >= end)
			g_774654 = 1;
		fcn_004cfca0();
		fcn_004e5140((*(int*)&g_772f40));
	} while (fcn_005373e0(fcn_004e4de0, g_68bfb8 | 0x8000) != 0);
}
