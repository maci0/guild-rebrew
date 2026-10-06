// FUNCTION: GOLD 0x005966d0
// FUNCTION: GOLDTL 0x0059f8b0

extern int g_7746a0;
extern int g_774800;
extern char g_14cf950;
extern int g_14ab07c;
extern int g_14ab750;
extern int g_14aadd8;
extern char g_6aa750[];
extern char g_6aa73c[];
extern char g_6aa728[];

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_005c1090(int);
void __cdecl fcn_005c0a30(int);
void __cdecl fcn_00532ef0(void);
void __cdecl fcn_005bebe0(int, int, int);

void __cdecl fcn_0059f8b0(int a1, int a2)
{
	int x;
	int y;
	int z;

	fcn_005338a0();
	while (fcn_005373e0(fcn_0059f8b0, 0x67fff) != 0) {
		x = fcn_005338d0(g_6aa750, g_14ab07c, 0xc);
		y = fcn_005338d0(g_6aa73c, g_14ab750, 0xc);
		z = fcn_005338d0(g_6aa728, g_14aadd8, 0xc);
		if (g_774800 != 0) {
			if (g_14cf950 == 0x19) {
				fcn_005c1090(a1);
			}
			if (g_14cf950 == 0x20) {
				fcn_005c0a30(a1);
			}
		}
		if (g_7746a0 != 0) {
			if (g_7746a0 == x) {
				fcn_005c0a30(a1);
				fcn_00532ef0();
			}
			else if (g_7746a0 == y) {
				fcn_005c1090(a1);
			}
			else if (g_7746a0 == z) {
				fcn_005bebe0(a1, a2, 4);
			}
		}
	}
}
