// FUNCTION: GOLD 0x00592370
// FUNCTION: GOLDTL 0x0059b0b0

extern int g_7746a0;
extern int g_14a7d28;
extern int g_14a7b50;
extern char g_6a9924[];
extern char g_6aa34c[];

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
void __cdecl fcn_005cf560(int);
void __cdecl fcn_005b6300(int, char*);

void __cdecl fcn_0059b0b0(int a)
{
	int x;
	int y;

	fcn_005338a0();
	while (fcn_005373e0(fcn_0059b0b0, 0x67fff) != 0) {
		x = fcn_005338d0(g_6a9924, g_14a7d28, 0xc);
		y = fcn_005338d0(g_6aa34c, g_14a7b50, 0xc);
		if (g_7746a0 != 0) {
			if (g_7746a0 == x) {
				fcn_005cf560(a);
			}
			else if (g_7746a0 == y) {
				fcn_005b6300(a, g_6aa34c);
			}
		}
	}
}
