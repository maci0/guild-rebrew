

extern int g_7746a0;
extern unsigned short g_774970;
extern char g_7f4ca0[];
extern int g_14aac24;
extern char g_6aafe4[];

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
int __cdecl fcn_004eb220(char*);
void __cdecl fcn_005aa480(int);

void __cdecl fcn_005aaed0(int a)
{
	int x;

	x = 0;
	fcn_005338a0();
	while (fcn_005373e0(fcn_005aaed0, 0x67fff) != 0) {
		if (fcn_004eb220(g_7f4ca0 + g_774970 * 540) != 0) {
			x = fcn_005338d0(g_6aafe4, g_14aac24, 0x16);
		}
		if (g_7746a0 != 0 && g_7746a0 == x) {
			fcn_005aa480(a);
		}
	}
}
