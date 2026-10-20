#include "client_types.h"

extern unit_77e980 g_77e980[1024];
extern unit_77e980* g_7dc420;
extern char g_7749dc;
extern int g_7749d4;
extern unsigned char g_6a4758;
extern int g_6a475c;
extern unsigned short g_6a4760;
extern int g_6a4764;

void __cdecl fcn_0041d9e0(const char* msg);

/* ADDRESS: GOLDTL 0x005462a0 */
unit_77e980* __cdecl fcn_005462a0(void)
{
	unit_77e980* e;
	unit_77e980* base;
	char matched;

	matched = 0;
	base = 0;
	if (g_7749d4 < 0 || g_7749d4 >= 0x400) {
		fcn_0041d9e0((const char*) 0x6a5784);
	} else {
		base = &g_77e980[g_7749d4];
	}
	e = g_7dc420;
	if (e == 0 || e == base || (unsigned int) e > (unsigned int) base) {
		return 0;
	}
	if (g_7749dc != 0) {
		g_7749dc = 0;
	} else {
		e++;
		g_7dc420 = e;
	}
	for (;;) {
		if (e->kind != 0) {
			if (g_6a4758 != 0xff) {
				if (e->kind != g_6a4758) {
					goto nomatch;
				}
				matched = 1;
			}
			if (g_6a475c != -1) {
				if (*(int*) ((char*) e + 4) != g_6a475c) {
					goto nomatch;
				}
				matched = 1;
			}
			if (g_6a4760 != 0xffff) {
				if (*(unsigned short*) ((char*) e + 8) != g_6a4760) {
					goto nomatch;
				}
				matched = 1;
			}
			if (g_6a4764 != -1) {
				if (*(int*) ((char*) e + 0x10) == g_6a4764) {
					return e;
				}
				goto nomatch;
			}
		}
		if (matched) {
			return e;
		}
		goto next;
nomatch:
		matched = 0;
next:
		if ((unsigned int) e >= (unsigned int) base) {
			e = 0;
			g_7dc420 = e;
			break;
		}
		e++;
		g_7dc420 = e;
	}
	return e;
}
