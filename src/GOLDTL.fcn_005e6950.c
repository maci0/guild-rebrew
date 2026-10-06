// FUNCTION: GOLD 0x005d9ce0
// FUNCTION: GOLDTL 0x005e6950

extern int g_7746d8;
extern int g_7746a0;
extern int g_14b5aec;
extern int g_14b5bfc;
extern char g_6ad4ec[];
extern char g_6ad4d8[];

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_005e5ea0(int);
void __cdecl fcn_005e6e00(void);

void __cdecl fcn_005e6950(int a)
{
	int x;
	int y;

	x = 0;
	fcn_005338a0();
	while (fcn_005373e0(fcn_005e6950, 0x67fff) != 0) {
		if (g_7746d8 & 0x200) {
			x = fcn_005338d0(g_6ad4ec, g_14b5aec, 0x16);
		}
		y = fcn_005338d0(g_6ad4d8, g_14b5bfc, 0x16);
		if (g_7746a0 != 0) {
			if (g_7746a0 == x) {
				fcn_005e5ea0(a);
			}
			else if (g_7746a0 == y) {
				fcn_005e6e00();
			}
		}
	}
}
