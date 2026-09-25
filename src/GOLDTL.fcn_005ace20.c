// FUNCTION: GOLD 0x005a3b00
// SIZE: 141
// FUNCTION: GOLDTL 0x005ace20
// SIZE: 141

extern int g_7746a0;
extern int g_14ab8c8;
extern int g_14ab89c;
extern char g_6ab12c[];
extern char g_6ab11c[];

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_005abd60(void);
void __cdecl fcn_005ab3e0(int, int);

void __cdecl fcn_005ace20(int a1, int a2)
{
	int x;
	int y;

	fcn_005338a0();
	while (fcn_005373e0(fcn_005ace20, 0x67fff) != 0) {
		x = fcn_005338d0(g_6ab12c, g_14ab8c8, 0x16);
		y = fcn_005338d0(g_6ab11c, g_14ab89c, 0x16);
		if (g_7746a0 != 0) {
			if (g_7746a0 == x) {
				fcn_005abd60();
			}
			else if (g_7746a0 == y) {
				fcn_005ab3e0(a1, a2);
			}
		}
	}
}
