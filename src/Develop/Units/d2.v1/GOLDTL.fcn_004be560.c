extern int g_772514;
extern char* g_1015ea0;
extern unsigned char* lpGebaeudePROT;
extern int g_100f1dc;
#include "client_dialog_state.h"
extern int g_14ce8e0;
extern int g_67d370;
extern unsigned short g_7f3ee4;
extern int g_90d520[];
extern int g_14a79c0[];
extern char g_679060[];

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
int __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_005039e0(int);
int __cdecl fcn_00502cd0(int, int, ...);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_0064d41a(char*, const char*, ...);
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
	unsigned char* src;
	char* q;
	char* e;
	int win;
	int t;
	int n;
	int i;
	unsigned int ret;

	ret = a2;
	src = lpGebaeudePROT + (unsigned char) *a0 * 0x24d;
	a2 = fcn_00470820(0, 0, (char*) 0x6816e8);
	fcn_00471b60(a2);
	d2_SetForm(a2, 4);
	fcn_00472250(a2, 4, io_AppendText(0x7d));
	d2_SetForm(a2, 2);
	win = a2;
	if (*src == 0x1c) {
		q = (char*) fcn_00502cd0(*(int*) (a0 + 0x5d), 2, 0, 0x1dc, 6);
		n = 0;
		if (!q) {
			goto tail;
		}
		e = (char*) fcn_00502cd0(*(int*) (q + 0x14), 1, 5);
		if (!e) {
			goto tail;
		}
		do {
			if (*(int*) (e + 0xe) > 1) {
				t = fcn_0046f740((n % 4) * 0x40, (n / 4) * 0x40,
					*(unsigned short*) e + 0xdf, g_772514);
				items[n] = t;
				*(unsigned int*) (t * 0x2f4 + g_1015ea0 + 0x5c) = 1;
				*(unsigned int*) (t * 0x2f4 + g_1015ea0 + 0x1d0) = 3;
				*(unsigned int*) (t * 0x2f4 + g_1015ea0 + 0x1e4) = 0x525;
				g_90d520[n] = *(unsigned short*) e;
				n++;
			}
			e = (char*) gm_NextEntityQueryMatch();
		} while (e);
	} else if (*src == 9) {
		q = (char*) fcn_00502cd0(*(int*) (a0 + 0x5d), 2, 0, 0x116, 6);
		n = 0;
		if (!q) {
			goto tail;
		}
		e = (char*) fcn_00502cd0(*(int*) (q + 0x14), 1, 5);
		if (!e) {
			goto tail;
		}
		do {
			if (*(int*) (e + 0xe) >= 1) {
				t = fcn_0046f740((n % 4) * 0x40, (n / 4) * 0x40,
					*(unsigned short*) e + 0xdf, g_772514);
				items[n] = t;
				*(unsigned int*) (t * 0x2f4 + g_1015ea0 + 0x5c) = 1;
				*(unsigned int*) (t * 0x2f4 + g_1015ea0 + 0x1d0) = 3;
				*(unsigned int*) (t * 0x2f4 + g_1015ea0 + 0x1e4) = 0x525;
				g_90d520[n] = *(unsigned short*) e;
				n++;
			}
			e = (char*) gm_NextEntityQueryMatch();
		} while (e);
	} else {
		fcn_005039e0((int) a0);
		q = (char*) fcn_00502cd0(*(int*) (a0 + 0x5d), 2, 0, 0xff, 6);
		n = 0;
		for (i = 0; i < g_7f3ee4; i++) {
			e = (char*) fcn_00502cd0(*(int*) (q + 0x14), 1, 0, g_90d520[n]);
			if (e && *(int*) (e + 0xe) > 1) {
				t = fcn_0046f740((n % 4) * 0x40, (n / 4) * 0x40,
					g_90d520[n] + 0xdf, g_772514);
				items[n] = t;
				*(unsigned int*) (t * 0x2f4 + g_1015ea0 + 0x5c) = 1;
				*(unsigned int*) (t * 0x2f4 + g_1015ea0 + 0x1d0) = 0x23;
				*(unsigned int*) (t * 0x2f4 + g_1015ea0 + 0x1e4) = 0x525;
				*(unsigned int*) (t * 0x2f4 + g_1015ea0 + 0x1dc) = 4;
				*(unsigned int*) (t * 0x2f4 + g_1015ea0 + 0x1e0) = 0xf;
				fcn_0064d41a((char*) (t * 0x2f4 + g_1015ea0 + 0xcc),
					g_679060, g_14a79c0[g_90d520[n] * 2]);
				n++;
			}
		}
	}
tail:
	g_7f3ee4 = (unsigned short) n;
	g_90d520[n] = 0;
	t = fcn_0046f740((n % 4) * 0x40 + 7, (n / 4) * 0x40 + 7, 0x527, g_772514);
	items[n] = t;
	*(unsigned int*) (t * 0x2f4 + g_1015ea0 + 0x5c) = 1;
	*(unsigned int*) (t * 0x2f4 + g_1015ea0 + 0x1d0) = 3;
	while (fcn_005373e0(0x4be560, 0x657c7)) {
		if (g_14ce8e0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			for (t = 0; t < g_7f3ee4 + 1; t++) {
				if (g_67d370 == items[t]) {
					ret = g_90d520[t];
					g_774654 = 1;
					break;
				}
			}
		}
	}
	fcn_00471e30(win);
	fcn_004116d0();
	return ret;
}
