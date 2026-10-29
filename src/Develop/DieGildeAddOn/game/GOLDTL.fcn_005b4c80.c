#include <string.h>

// SIZE 0x3cc
typedef struct {
	char pad0[0x258];
	int x258;
	char pad25c[0x20];
	int x27c;
	char pad280[0x14c];
} Win_5b4c80;

// SIZE 0x2f4
typedef struct {
	char pad0[0x5c];
	int used;
	char pad60[0x290];
	void* ent;
} Ctl_5b4c80;

// SIZE 0x21c
typedef struct {
	unsigned short slot;
	char pad2[0x21a];
} Ent_5b4c80;

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];
extern char* g_1015ea0;
extern char g_7f4ca0[];
extern int g_14ce8e0;
extern int g_774654;
extern int g_100f1dc;
extern int g_67d370;
extern int g_772514;

int __cdecl fcn_0046e940(int x, int y, int w, int h, int a5);
int __cdecl fcn_0046f100(int x, int y, int cx, int cy, int a5, int win);
void __cdecl fcn_00472900(int, int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_005b4660(void*);
char* __cdecl fcn_00519190(int, ...);
int __cdecl fcn_005b44b0(Ent_5b4c80*);
int __cdecl fcn_00472250(int, int, char*);
void __cdecl fcn_005b0f00(Win_5b4c80*);
int __cdecl fcn_0046f280(int);


/* Modal two-column entity list: fills it once, then pumps the UI and opens
 * the entry the player picks. */
/* ADDRESS: GOLDTL 0x005b4c80 */
void __cdecl fcn_005b4c80(void)
{
	int ids[0x300];
	Win_5b4c80* rp;
	int left;
	int win;
	int right;
	int fill;
	int saved;
	int n;
	int i;

	memset(ids, 0xff, sizeof(ids));
	fill = 1;
	left = fcn_0046f100(0, 0, 0x140, 0x190, 0x10, win = fcn_0046e940(0x20, 0x60, 0x280, 0x190, 0x414));
	right = fcn_0046f100(0x140, 0, 0x140, 0x190, 0x10, win);
	fcn_00472900(((Win_5b4c80*)g_1015f40)[win].x27c, 0x54);
	fcn_00472900(((Win_5b4c80*)g_1015f40)[left].x27c, 0x54);
	fcn_00472900(((Win_5b4c80*)g_1015f40)[right].x27c, 0x54);
	if (fcn_005373e0((void*) fcn_005b4c80, 0x657c7)) {
		rp = &((Win_5b4c80*)g_1015f40)[right];
		do {
			if (g_14ce8e0 != 0) {
				g_774654 = 1;
			}
			if (g_100f1dc != -1) {
				for (i = 0; i < 0x300; i++) {
					if (ids[i] != -1 && g_67d370 == ids[i]) {
						if (((Ctl_5b4c80*)g_1015ea0)[g_67d370].ent != 0) {
							fcn_005b4660(((Ctl_5b4c80*)g_1015ea0)[g_67d370].ent);
						}
						break;
					}
				}
			}
			if (fill) {
				g_772514 = left;
				saved = ((Win_5b4c80*)g_1015f40)[left].x258;
				fcn_00519190((int) "$C");
				ids[0] = fcn_00472250(-1, g_772514, fcn_00519190((int) "%ib[NIEMAND]$6THeCnt:%i$A", 2, fcn_005b44b0(0)));
				((Ctl_5b4c80*)g_1015ea0)[ids[0]].ent = 0;
				((Ctl_5b4c80*)g_1015ea0)[ids[0]].used = 1;
				n = 1;
				for (i = 0; i < 0x300; i++) {
					if (n >= 0x40) {
						break;
					}
					ids[i] = -1;
					if (((Ent_5b4c80*)g_7f4ca0)[i].slot != 0xffff) {
						ids[i] = fcn_00472250(-1, g_772514, fcn_00519190((int) "%it[%1N4]$6THeCnt:%i$A", ((Ent_5b4c80*)g_7f4ca0)[i].slot, fcn_005b44b0(&((Ent_5b4c80*)g_7f4ca0)[i])));
						((Ctl_5b4c80*)g_1015ea0)[ids[i]].ent = &((Ent_5b4c80*)g_7f4ca0)[i];
						n++;
						((Ctl_5b4c80*)g_1015ea0)[ids[i]].used = 1;
					}
					if (n >= 0x3f) {
						if (g_772514 == right) {
							break;
						}
						g_772514 = right;
						fcn_00519190((int) "$C");
						n = 0;
					}
				}
				((Win_5b4c80*)g_1015f40)[left].x258 = saved;
				fill = 0;
			}
			fcn_005b0f00(&((Win_5b4c80*)g_1015f40)[left]);
			fcn_005b0f00(rp);
		} while (fcn_005373e0((void*) fcn_005b4c80, 0x657c7));
	}
	fcn_0046f280(win);
	fcn_0046f280(left);
	fcn_0046f280(right);
}
