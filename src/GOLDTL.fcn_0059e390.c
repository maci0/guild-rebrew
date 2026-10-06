// FUNCTION: GOLD 0x005951c0
// FUNCTION: GOLDTL 0x0059e390

extern int g_7746a0;
extern int g_14ad188;
extern int g_14ad1a8;
extern char g_6aa5f0[];
extern char g_6aa5e8[];

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_0059a0e0(void);
void __cdecl fcn_005ba900(int);
void __cdecl fcn_005ba8f0(int);

void __cdecl fcn_0059e390(int a)
{
	int x;
	int y;

	fcn_005338a0();
	while (fcn_005373e0(fcn_0059e390, 0x67fff) != 0) {
		x = fcn_005338d0(g_6aa5f0, g_14ad188, 0x10);
		y = fcn_005338d0(g_6aa5e8, g_14ad1a8, 0x10);
		fcn_0059a0e0();
		if (g_7746a0 != 0) {
			if (g_7746a0 == x) {
				fcn_005ba900(a);
			}
			else if (g_7746a0 == y) {
				fcn_005ba8f0(a);
			}
		}
	}
}
