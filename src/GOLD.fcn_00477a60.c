

typedef struct Spin00477a60 {
	char pad0[0x18];
	int max;
	int min;
	int pos;
	char pad24[0x28 - 0x24];
	unsigned char flags;
	char pad29[0x12c - 0x29];
	int value;
} Spin00477a60;
// SIZE 0x130

extern Spin00477a60* g_006ed9dc; /* 0x006ed9dc */
extern int g_0146739c; /* 0x0146739c */
extern int g_01467390; /* 0x01467390 */
extern int g_006ed9f4; /* 0x006ed9f4 */
extern int g_006310b4; /* 0x006310b4 */
extern int g_005f323c; /* 0x005f323c */
extern int g_00f8a66c; /* 0x00f8a66c */
extern int g_00f8a664; /* 0x00f8a664 */
#include "client_cursor.h"
extern int g_006ed9c4; /* 0x006ed9c4 */
extern int g_006ed9e8; /* 0x006ed9e8 */
extern int g_006ed9ec; /* 0x006ed9ec */

int __cdecl fcn_00475be0(Spin00477a60* p);
void __cdecl fcn_00477490(Spin00477a60* p, int v, int a3, int a4);

void __cdecl fcn_00477a60(void)
{
	int step;
	Spin00477a60* p;

	if (g_006ed9dc == 0 || !(g_006ed9dc->flags & 2)) {
		return;
	}
	if (g_0146739c != 0 && g_006ed9dc->value < g_006ed9dc->max) {
		g_006ed9dc->value = g_006ed9dc->max;
	}
	if (g_01467390 == 0 || g_006ed9dc->value == -1) {
		return;
	}
	if (g_006ed9f4 == 0) {
		step = fcn_00475be0(g_006ed9dc);
		g_006ed9f4 = 1;
		g_00f8a66c = g_006310b4;
		g_00f8a664 = g_005f323c;
		p = g_006ed9dc;
		g_006ed9c4 = p->value;
		g_006ed9e8 = g_01467380;
		g_006ed9ec = g_01467382;
		if (p->flags & 0x80) {
			g_005f323c = (g_006ed9c4 - p->min) * 4 / step + g_006ed9ec;
			g_006310b4 = (g_006ed9c4 - p->max) * 4 / step + g_006ed9ec;
		}
		p->pos = (g_006ed9c4 - p->min) * 4 / step + g_006ed9ec;
	}
	fcn_00477490(g_006ed9dc, g_006ed9c4, g_006ed9ec, g_01467382);
}
