// FUNCTION: GOLD 0x0059fdf0
// SIZE: 133
// FUNCTION: GOLDTL 0x005a9120
// SIZE: 133

extern int g_7746a0;
extern unsigned short g_774970;
extern char g_7f4ca0[];
extern int g_14abb58;
extern char g_6aae28[];

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_005a9070(int);

void __cdecl fcn_005a9120(int a)
{
	int x;

	fcn_005338a0();
	while (fcn_005373e0(fcn_005a9120, 0x67fff) != 0) {
		if (g_7f4ca0[g_774970 * 540 + 0x166] != 0) {
			x = fcn_005338d0(g_6aae28, g_14abb58, 0x16);
		}
		else {
			x = 0;
		}
		if (g_7746a0 != 0 && g_7746a0 == x) {
			fcn_005a9070(a);
		}
	}
}
