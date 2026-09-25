// FUNCTION: GOLD 0x005a2f30
// SIZE: 128
// FUNCTION: GOLDTL 0x005ac250
// SIZE: 128

extern int g_7746a0;
extern int g_7746d8;
extern int g_14ab918;
extern char g_6ab07c[];

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_005abfd0(int);

void __cdecl fcn_005ac250(int a)
{
	int x;

	x = 0;
	fcn_005338a0();
	while (fcn_005373e0(fcn_005ac250, 0x67fff) != 0) {
		if (!(g_7746d8 & 0x200)) {
			x = fcn_005338d0(g_6ab07c, g_14ab918, 0x16);
		}
		if (g_7746a0 != 0 && !(g_7746d8 & 0x200) && g_7746a0 == x) {
			fcn_005abfd0(a);
		}
	}
}
