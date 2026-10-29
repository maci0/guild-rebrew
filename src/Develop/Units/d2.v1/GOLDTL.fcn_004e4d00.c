


extern int g_6b7fac;
extern int g_772f3c;
extern int g_68bfb8;
extern int g_14ce8e0;
extern int g_774654;
extern int* g_772f40;

int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_004cfca0(void);
void __cdecl fcn_004e5140(int);
void __cdecl fcn_004e4de0(int);

int __cdecl fcn_004e4d00(int secs, int(__cdecl* cb)(int), int arg)
{
	int start;
	int res;

	start = (*(unsigned int*)&g_6b7fac);
	res = 0;
	if (g_772f3c != 0)
		return 0;
	if (fcn_005373e0(fcn_004e4de0, g_68bfb8 | 0x8000) != 0) {
		do {
			if (g_14ce8e0 != 0) {
				if (cb != 0)
					res = cb(arg);
				else
					res = 1;
				g_774654 = 1;
			} else if ((*(unsigned int*)&g_6b7fac) >= secs * (1.0 / 14.0) + start) {
				g_774654 = 1;
			}
			fcn_004cfca0();
			fcn_004e5140((*(int*)&g_772f40));
		} while (fcn_005373e0(fcn_004e4de0, g_68bfb8 | 0x8000) != 0);
	}
	return res;
}
