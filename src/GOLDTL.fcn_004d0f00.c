extern unsigned short* g_772f24;
extern int g_7746a0;
extern char* g_7e4260[32];
extern int g_14ce8cc;
extern int g_67d370;
extern char* g_7746a4;
extern char g_14cf736;
extern int g_772e9c;
extern int g_772ed4;
extern int g_772ed8;

int __cdecl fcn_004cef70(int, char*);
int __cdecl fcn_004ce270(char*, char*);
void __cdecl fcn_004d1910(void);
int* __cdecl fcn_004c30a0(int, int, char*, int, int);

// FUNCTION: GOLDTL 0x4d0f00
// SIZE: 285

void __cdecl fcn_004d0f00(void)
{
	unsigned short* me;
	char* e;
	char* x;
	char* t;
	int i;

	me = g_772f24;
	g_7746a0 = 0;
	for (i = 0; i < 32; i++) {
		e = g_7e4260[i];
		if (e != 0 && e[0x188] != 0 && (fcn_004cef70(*me, e) & 0x800) != 0
		    && *(int*) (e + 0x184) != 0 && e[8] != 0)
			break;
	}
	if (g_14ce8cc == 0 || g_67d370 != -1)
		return;
	x = g_7746a4;
	if (x != 0 && *(int*) (x + 0x220) == 2) {
		t = *(char**) (x + 0x204);
		if ((fcn_004cef70(*me, t) & 0x800) != 0 && g_14cf736 == 0
		    && (e == 0 || fcn_004ce270(e, t) == 0)) {
			fcn_004d1910();
			t[0x188] = 1;
			if (*(int*) (t + 0x16c) == g_772e9c)
				fcn_004c30a0(*(unsigned short*) t, g_772ed4, "_ARBEITER_KOMMENTARE_KLICK", -1, 0);
			else
				fcn_004c30a0(*(unsigned short*) t, g_772ed8, "_ARBEITER_KOMMENTARE_KLICK", -1, 0);
			x = g_7746a4;
		}
	}
	g_7746a0 = (int) x;
}
