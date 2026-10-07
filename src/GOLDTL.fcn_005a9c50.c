// FUNCTION: GOLD 0x5a0920
// FUNCTION: GOLDTL 0x005a9c50

typedef struct
{
	char pad0[0xd];
	unsigned char xd;
	char pade[0x1ba];
	int x1c8;
	char pad1cc[0x50];
} Player;
// SIZE 0x21c

extern unsigned short g_774970;
extern char g_7f4ca0[];
extern int g_7746a0;
extern int g_14aa2f0;
extern int g_14aa2f4;
extern int g_14aa2ec;
extern int g_14ad240;
extern int g_14ad248;
extern char s_6aaf40[];
extern char s_6aaf24[];
extern char s_6aaf08[];
extern char s_6aaef4[];
extern char s_6aaedc[];

void __cdecl fcn_005338a0(void);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_005338d0(char*, int, int);
int __cdecl fcn_0057ec70(int);
void __cdecl fcn_005ce460(int);
void __cdecl fcn_005a92c0(int);
void __cdecl fcn_005a9a10(void);

void __cdecl fcn_005a9c50(int arg)
{
	int a;
	int b;
	int c;
	int d;
	int e;

	fcn_005338a0();
	if (fcn_005373e0((void*) fcn_005a9c50, 0x67fff) != 0) {
		do {
			if (fcn_0057ec70(0x1000) == 1) {
				a = fcn_005338d0(s_6aaf40, g_14aa2f0, 0xc);
				b = fcn_005338d0(s_6aaf24, g_14aa2f4, 0xc);
				c = fcn_005338d0(s_6aaf08, g_14aa2ec, 0xc);
			}
			else {
				c = 0;
				b = 0;
				a = 0;
			}
			if (fcn_0057ec70(0x8000) == 1) {
				e = fcn_005338d0(s_6aaef4, g_14ad240, 0x16);
			}
			else {
				e = 0;
			}
			if ((((Player*)g_7f4ca0)[g_774970].x1c8 & 0x4000) && ((Player*)g_7f4ca0)[g_774970].xd == 1 && fcn_0057ec70(0x2000) == 1) {
				d = fcn_005338d0(s_6aaedc, g_14ad248, 0x16);
			}
			else {
				d = 0;
			}
			if (g_7746a0 != 0) {
				if (g_7746a0 == a) {
					fcn_005ce460(0x112);
				}
				else if (g_7746a0 == b) {
					fcn_005ce460(0x111);
				}
				else if (g_7746a0 == c) {
					fcn_005ce460(0x113);
				}
				else if (g_7746a0 == d) {
					fcn_005a92c0(arg);
				}
				else if (g_7746a0 == e) {
					fcn_005a9a10();
				}
			}
		} while (fcn_005373e0((void*) fcn_005a9c50, 0x67fff) != 0);
	}
}
