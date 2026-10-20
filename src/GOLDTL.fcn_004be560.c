extern int g_772514;
extern char* g_1015ea0;
extern char* g_entity_type_table;
extern int g_100f1dc;
extern int g_774654;
extern int g_14ce8e0;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
int __cdecl fcn_004727a0(int, int);
int __cdecl fcn_00519190(int, ...);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_005039e0(int);
int __cdecl fcn_00502cd0(int, int, ...);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl sprintf(char*, const char*, ...);
int __cdecl fcn_005373e0(int, int);
void __cdecl fcn_00471e30(int);
void __cdecl fcn_004116d0(void);

/* Route one enhanced-building selection through the query engine: build the
 * window, walk the candidate query, spawn one icon record per hit, then keep
 * dispatching until the master loop closes the dialog. */
/* ADDRESS: GOLDTL 0x004be560 */
unsigned int __cdecl fcn_004be560(char* a0, int a1, unsigned int a2)
{
	int items[10];
	char* src;
	char* q;
	char* e;
	char* v;
	int win;
	int t;
	int n;
	int i;
	unsigned int ret;

	ret = a2;
	src = g_entity_type_table + (unsigned char) *a0 * 0x24d;
	a2 = fcn_00470820(0, 0, (char*) 0x6816e8);
	fcn_00471b60(a2);
	fcn_004727a0(a2, 4);
	fcn_00472250(a2, 4, fcn_00519190(0x7d));
	fcn_004727a0(a2, 2);
	win = a2;
	n = 0;
	if (*src == 0x1c) {
		q = (char*) fcn_00502cd0(*(int*) (a0 + 0x5d), 2, 0, 0x1dc, 6);
		if (!q) {
			goto tail;
		}
		e = (char*) fcn_00502cd0(*(int*) (q + 0x14), 1, 5);
		if (!e) {
			goto tail;
		}
		do {
			if (*(int*) (e + 0xe) >= 2) {
				items[n] = fcn_0046f740((n % 4) * 0x40, (n / 4) * 0x40, *(unsigned short*) e + 0xdf, g_772514);
				v = (char*) (items[n] * 0x2f4 + (int) g_1015ea0);
				*(unsigned int*) (v + 0x5c) = 1;
				*(unsigned int*) (v + 0x1d0) = 3;
				*(unsigned int*) (v + 0x1e4) = 0x525;
				*(int*) (0x90d520 + n * 4) = *(unsigned short*) e;
				n++;
			}
			e = (char*) gm_NextEntityQueryMatch();
		} while (e);
	} else if (*src == 9) {
		q = (char*) fcn_00502cd0(*(int*) (a0 + 0x5d), 2, 0, 0x116, 6);
		if (!q) {
			goto tail;
		}
		e = (char*) fcn_00502cd0(*(int*) (q + 0x14), 1, 5);
		if (!e) {
			goto tail;
		}
		do {
			if (*(int*) (e + 0xe) >= 1) {
				items[n] = fcn_0046f740((n % 4) * 0x40, (n / 4) * 0x40, *(unsigned short*) e + 0xdf, g_772514);
				v = (char*) (items[n] * 0x2f4 + (int) g_1015ea0);
				*(unsigned int*) (v + 0x5c) = 1;
				*(unsigned int*) (v + 0x1d0) = 3;
				*(unsigned int*) (v + 0x1e4) = 0x525;
				*(int*) (0x90d520 + n * 4) = *(unsigned short*) e;
				n++;
			}
			e = (char*) gm_NextEntityQueryMatch();
		} while (e);
	} else {
		fcn_005039e0((int) a0);
		q = (char*) fcn_00502cd0(*(int*) (a0 + 0x5d), 2, 0, 0xff, 6);
		for (i = 0; i < *(unsigned short*) 0x7f3ee4; i++) {
			e = (char*) fcn_00502cd0(*(int*) (q + 0x14), 1, 0, *(int*) (0x90d520 + i * 4));
			if (e && *(int*) (e + 0xe) >= 2) {
				items[i] = fcn_0046f740((i % 4) * 0x40, (i / 4) * 0x40, *(int*) (0x90d520 + i * 4) + 0xdf, g_772514);
				v = (char*) (items[i] * 0x2f4 + (int) g_1015ea0);
				*(unsigned int*) (v + 0x5c) = 1;
				*(unsigned int*) (v + 0x1d0) = 0x23;
				*(unsigned int*) (v + 0x1e4) = 0x525;
				*(unsigned int*) (v + 0x1dc) = 4;
				*(unsigned int*) (v + 0x1e0) = 0xf;
				sprintf((char*) (v + 0xcc), (char*) 0x679060, *(int*) (*(int*) (0x90d520 + i * 4) * 8 + 0x14a79c0));
			}
		}
	}
tail:
	*(unsigned short*) 0x7f3ee4 = (unsigned short) n;
	*(int*) (0x90d520 + n * 4) = 0;
	t = fcn_0046f740((n % 4) * 0x40 + 7, (n / 4) * 0x40 + 7, 0x527, g_772514);
	items[n] = t;
	v = (char*) (t * 0x2f4 + (int) g_1015ea0);
	*(unsigned int*) (v + 0x5c) = 1;
	*(unsigned int*) (v + 0x1d0) = 3;
	t = fcn_005373e0(0x4be560, 0x657c7);
	do {
		if (!t) {
			fcn_00471e30(win);
			fcn_004116d0();
			return ret;
		}
		if (g_14ce8e0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			t = 0;
			if (*(unsigned short*) 0x7f3ee4 != 0xffff) {
				do {
					if (*(int*) 0x67d370 == items[t]) {
						ret = *(int*) (0x90d520 + t * 4);
						g_774654 = 1;
						break;
					}
					t++;
				} while (t < (int) (*(unsigned short*) 0x7f3ee4 + 1));
			}
		}
		t = fcn_005373e0(0x4be560, 0x657c7);
	} while (1);
}
