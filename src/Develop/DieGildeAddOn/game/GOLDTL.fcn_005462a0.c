#include "client_types.h"

extern unit_77e980 g_77e980[1024];
extern unit_77e980* g_7dc420;
extern char g_7749dc;
extern int g_7749d4;
extern unsigned char g_6a4758[4];
extern int g_6a475c;
extern unsigned short g_6a4760;
extern int g_6a4764;

void __cdecl ReportClientMessage(const char* msg);

/* ADDRESS: GOLDTL 0x005462a0 */
unit_77e980* __cdecl he_fn_Handlung(void)
{
	unit_77e980* e;
	unit_77e980* base;
	char matched;
	unsigned char kind;
	int id;
	unsigned short house;
	int target;

	matched = 0;
	base = 0;
	if (g_7749d4 < 0 || g_7749d4 >= 0x400) {
		ReportClientMessage((const char*) 0x6a5784);
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
	kind = g_6a4758[0];
	id = g_6a475c;
	house = g_6a4760;
	target = g_6a4764;
	for (;;) {
		if (e->kind != 0) {
			if (kind != 0xff) {
				if (e->kind != kind) {
					goto nomatch;
				}
				matched = 1;
			}
			if (id != -1) {
				if (*(int*) ((char*) e + 4) != id) {
					goto nomatch;
				}
				matched = 1;
			}
			if (house != 0xffff) {
				if (*(unsigned short*) ((char*) e + 8) != house) {
					goto nomatch;
				}
				matched = 1;
			}
			if (target != -1) {
				if (*(int*) ((char*) e + 0x10) != target) {
					goto nomatch;
				}
			}
		}
		if (matched) {
			break;
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
