extern int g_6a256c;
extern int g_6b7fac;
extern int g_772514;
extern int g_774654;
extern int g_14ce8e0;
extern char g_1015f40[];
extern char g_868060[];
extern char* g_85ab80;

char* __cdecl fcn_00445600(int, int, int, char*);
void __cdecl fcn_00412e50(int, int);
int __cdecl fcn_005373e0(void*, int);
int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00471e30(int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00519190(char* fmt, ...);
void __cdecl d2_SetBackgroundTexture(const char* name, int win);
char* __cdecl fcn_00502cd0(int, ...);
char* __cdecl gm_FindSlotById(int, int);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl fcn_005a30c0(int x, int y, int layer, int a4, int a5);
int __cdecl sprintf(char*, const char*, ...);

/* ADDRESS: GOLDTL 0x005a31b0 */
void __cdecl fcn_005a31b0(char* a0)
{
	char name[260];
	int win;
	int win2;
	unsigned short* it;
	char* slot;
	int p;
	int k;
	int idx;
	int n;
	int flag;
	double dt;
	char* v12p;

	flag = 0;
	dt = 0.0f;
	if (a0[0] != 'G') {
		return;
	}
	p = (int) fcn_00445600(0, 0x100, 0, "dummy_Kartentisch_RECHTS_UNTEN");
	if (p != 0) {
		fcn_00412e50(p, g_6a256c);
	}
	p = (int) fcn_00445600(0, 0x40, 0, "ob_KARTENTISCH");
	idx = -1;
	k = -1;
	if (fcn_005373e0((void*) 0x5a31b0, 0x677c7)) {
		do {
			n = 0;
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
			}
			if (k != 1) {
				if (idx != -1) {
					fcn_00471e30(idx);
				}
				idx = fcn_00470820(0, 0, "Handel\\Handel_Stadtinfo");
				fcn_00471b60(idx);
				d2_SetForm(idx, 0);
				win = g_772514 * 0x3cc;
				*(int*) (win + 0x10162e8) = 0x18;
				*(int*) (win + 0x10162ec) = 0x18;
				*(int*) (win + 0x10162f0) = 0x1c;
				*(int*) (win + 0x10162f4) = 0xb;
				d2_SetForm(idx, 1);
				fcn_00519190((char*) 0x1a11);
				d2_SetForm(idx, 5);
				fcn_00519190((char*) 0x1a14, *(int*) (a0 + 0x65) * 0x2f4 + g_868060, *(int*) (*(int*) (a0 + 0x65) * 0x2a90 + (int) g_85ab80));
				win = *(int*) (idx * 700 + 0x103814c) * 0x3cc;
				v12p = g_1015f40 + win;
				sprintf(name, "Wappen128_ns_Stadt_%s", (char*) (*(int*) (a0 + 0x65) * 0x2f4 + (int) g_868060));
				d2_SetBackgroundTexture(name, *(int*) (win + 0x1015f40));
				*(int*) (win + 0x10162e4) = 0;
				flag = g_6b7fac;
				slot = fcn_00502cd0(*(int*) (a0 + 0x5d), 2, 0, 0x1db, 6);
				if (slot == 0) {
					return;
				}
				win2 = (int) fcn_00502cd0(*(int*) (a0 + 0x5d), 2, 0, 0x1dc, 6);
				if (win2 == 0) {
					return;
				}
				d2_SetForm(idx, 3);
				fcn_00519190((char*) 0x1a12);
				it = gm_NextEntityQueryMatch();
				while (it != 0) {
					p = (int) gm_FindSlotById(*(int*) (a0 + 0x65), *it);
					if (p != 0 && *(int*) (p + 4) != 0) {
						fcn_005a30c0((n & 3) * 0x3c + 0xe, (n >> 2) * 0x50 + 0x1e, g_772514, *it, *(int*) (a0 + 0x65));
						n++;
					}
					it = gm_NextEntityQueryMatch();
				}
				n = 0;
				d2_SetForm(idx, 4);
				fcn_00519190((char*) 0x1a13);
				it = gm_NextEntityQueryMatch();
				while (it != 0) {
					p = (int) gm_FindSlotById(*(int*) (a0 + 0x65), *it);
					if (p != 0 && *(int*) (p + 4) != 0) {
						fcn_005a30c0((n & 3) * 0x3c + 0xe, (n >> 2) * 0x50 + 0x1e, g_772514, *it, *(int*) (a0 + 0x65));
						n++;
					}
					it = gm_NextEntityQueryMatch();
				}
				k = 1;
			}
			dt = (double) (g_6b7fac - flag) * *(double*) 0x665fa8;
			if (*(double*) 0x665ed0 <= dt) {
				dt = *(double*) 0x665ed0;
			}
			*(float*) (v12p + 0x3a4) = (float) dt;
		} while (fcn_005373e0((void*) 0x5a31b0, 0x677c7));
		if (idx != -1) {
			fcn_00471e30(idx);
		}
	}
}
