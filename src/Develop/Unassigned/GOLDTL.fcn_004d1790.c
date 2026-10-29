extern int g_14ce8d4;
extern int g_7e4300;
extern int g_14ce8e4;
extern int g_6772c4;
extern int g_67d370;
extern int g_14ce8cc;
extern int g_14ce8e0;
extern char* g_7e4260[32];
extern unsigned short* g_772f24;
extern unsigned short* g_772e9c;
extern int g_772ee4;
extern int g_772ee8;
extern char g_68b844[];

void __cdecl fcn_005345a0(void);
void __cdecl fcn_00534520(void);
int __cdecl fcn_004cef70(int, char*);
char __cdecl fcn_004d15c0(int, char*);
int __cdecl fcn_004c3030(int, int, int, int);
void __cdecl fcn_00414c30(int, int);
void __cdecl fcn_004d1910(void);

/* ADDRESS: GOLDTL 0x004d1790 */
void __cdecl fcn_004d1790(int a0)
{
	char** q;
	char* o;
	char* p;

	if (g_14ce8d4 == 0) {
		if (g_7e4300 != 0)
			fcn_005345a0();
	}
	if (g_14ce8d4 != 0 && g_14ce8e4 == 0) {
		if (g_7e4300 == 0 && g_6772c4 != 0 && g_67d370 == -1) {
			fcn_004d1910();
			fcn_00534520();
		}
	} else {
		if (g_14ce8cc != 0) {
			for (q = g_7e4260; q < g_7e4260 + 32; q++) {
				o = *q;
				if (o == 0)
					continue;
				if (*(char*) (o + 0x188) == 0)
					continue;
				if ((fcn_004cef70(*g_772f24, o) & 0x800) == 0)
					continue;
				if (*(int*) (o + 0x184) == 0)
					continue;
				if (*(char*) (o + 8) == 0)
					continue;
				if (!fcn_004d15c0(a0, o))
					continue;
				fcn_004c3030(*(unsigned short*) o, g_772f24 == g_772e9c ? g_772ee4 : g_772ee8, (int) g_68b844, -1);
				*(char*) (o + 0x188) = 0;
			}
		}
	}
	for (q = g_7e4260; q < g_7e4260 + 32; q++) {
		o = *q;
		if (o == 0)
			continue;
		if (*(char*) (*(int*) (o + 0x184) + 0x8c) & 0x40)
			continue;
		p = (char*) *(int*) (*(int*) (o + 0x184) + 0x34);
		if (*(char*) (o + 0x188)) {
			if ((*(unsigned char*) (p + 0x215) & 0x80) == 0)
				fcn_00414c30((int) p, 1);
		} else {
			if ((*(unsigned char*) (p + 0x215) & 0x80) == 0x80)
				fcn_00414c30((int) p, 0);
		}
	}
	if (g_14ce8e0 != 0)
		fcn_004d1910();
}
