#include "Develop/DieGildeAddOn/game/event_callbacks.h"
#include <string.h>

typedef struct Stats {
	int x0;
	int n;
	int x8[16];
	unsigned short x48[16];
	int x68[16];
	int xa8;
	int xac;
	int xb0;
	char* xb4;
} Stats;
// SIZE 0xb8

extern char* g_14a9aa8;
extern char* g_14a9ab4;
extern char* g_14a9ac0;
extern char g_6b5c60[];

char* __cdecl gm_LookupEntityRecordById(int);
char* __cdecl gm_FindRecordById(int);
int __cdecl fcn_0050de80(char* e, Stats* s);
int __cdecl gm_SearchTable67(int);
int __cdecl gm_StartFilteredEntitySearch(int, ...);
int __cdecl fcn_004d5450(int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl fcn_004e6240(char*, char*, char*, char*);

// Sends the two parties of a transfer (+0x34, +0x38) their message pair,
// chosen by the flag byte at +0x7c (1, 2 or 4). With flag 1 set, every
// listed record (+0x100, -1 = none) must exist and hold a positive total.

/* ADDRESS: GOLDTL 0x004d74b0 */
int __cdecl fcn_004d74b0(char* x)
{
	int i;
	int t;
	char* b;
	int t67;
	char buf[0x400];
	Stats st;
	char* a;
	char* r;
	int* id;
	unsigned char flags;

	a = gm_LookupEntityRecordById(*(int*) (x + 0x34));
	b = gm_LookupEntityRecordById(*(int*) (x + 0x38));
	if (a == 0 || b == 0 || a == b) {
		return 0;
	}
	if (x[0x7c] & 1) {
		id = (int*) (x + 0x100);
		for (i = 0; i < 3; i++, id++) {
			if (*id != -1) {
				r = gm_FindRecordById(*id);
				if (r == 0) {
					return 0;
				}
				fcn_0050de80(r, &st);
				if (st.xb0 <= 0) {
					return 0;
				}
			}
		}
	}
	t67 = gm_SearchTable67(*(int*) (x + 0x14));
	if (!gm_StartFilteredEntitySearch(1, 1, *(int*) (x + 0x10c))) {
		return 0;
	}
	flags = x[0x7c];
	if (flags & 1) {
		io_FormatTextBuffer(buf, 0x11e0, *(unsigned short*) b);
		strcat(buf, g_14a9aa8);
		fcn_004e6240(a, x, buf, g_6b5c60);
		io_FormatTextBuffer(buf, 0x11e1, *(unsigned short*) a);
		strcat(buf, g_14a9aa8);
		fcn_004e6240(b, x, buf, g_6b5c60);
	} else if (flags & 2) {
		t = fcn_004d5450(gm_SearchTable67(*(int*) (x + 0x10c))) + 0x1125;
		io_FormatTextBuffer(buf, 0x11e3, t, *(unsigned short*) b, t67);
		strcat(buf, g_14a9ab4);
		fcn_004e6240(a, x, buf, g_6b5c60);
		io_FormatTextBuffer(buf, 0x11e4, *(unsigned short*) a, t, t67);
		strcat(buf, g_14a9ab4);
		fcn_004e6240(b, x, buf, g_6b5c60);
		return 1;
	} else if (flags & 4) {
		io_FormatTextBuffer(buf, 0x11e6, *(unsigned short*) b);
		strcat(buf, g_14a9ac0);
		fcn_004e6240(a, x, buf, g_6b5c60);
		io_FormatTextBuffer(buf, 0x11e7, *(unsigned short*) a);
		strcat(buf, g_14a9ac0);
		fcn_004e6240(b, x, buf, g_6b5c60);
	}
	return 1;
}
