// FUNCTION: GOLD 0x004e2cc0
// FUNCTION: GOLDTL 0x4e4540

extern int g_772f3c;
extern int g_68bfb8;
extern int g_14ce8e0;

int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_00426cc0(int);

int __cdecl fcn_004e4540(int id, int(__cdecl* cb)(int), int arg)
{
	if (g_772f3c != 0)
		return 0;
	if (fcn_005373e0(0, g_68bfb8 | 0x8000) == 0)
		return 0;
	do {
		if (fcn_00426cc0(id) == 0)
			return 0;
		if (g_14ce8e0 != 0) {
			if (cb != 0)
				return cb(arg);
			return 1;
		}
	} while (fcn_005373e0(0, g_68bfb8 | 0x8000) != 0);
	return 0;
}
