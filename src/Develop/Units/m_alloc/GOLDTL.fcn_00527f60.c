#include <string.h>

/*
 * Town view refresh and element cache rebuild (party/status panel).
 *
 * The body is entered only while the active slot's kind byte is 6. It first
 * runs the screen setup, disposes any cached element handles, and then either
 * tears the cache down (a0 bit 0 set) or rebuilds the six label elements with
 * their current texts.
 *
 * Reconstructed range 0x527f60..0x5286d0. The native body continues at
 * 0x5286d0 with fcn_005279f0(a1) and the remaining update sequence through
 * 0x528fcf; that part is not reconstructed here.
 */

extern unsigned short g_774970;		/* 0x00774970 */
extern int g_1040490;			/* 0x01040490 */
extern int g_1040494;			/* 0x01040494 */
extern int g_774674;			/* 0x00774674 */
extern int g_774678;			/* 0x00774678 */
extern int g_77467c;			/* 0x0077467c */
extern int g_77250c;			/* 0x0077250c */
extern int g_14ce860;			/* 0x014ce860 */
extern int g_14ce864;			/* 0x014ce864 */
extern unsigned char g_77534c;		/* 0x0077534c */
extern int g_6a2578;			/* 0x006a2578 */
extern int g_6a257c;			/* 0x006a257c */
extern int g_6a2580;			/* 0x006a2580 */
extern int g_6a2584;			/* 0x006a2584 */
extern int g_6a2588;			/* 0x006a2588 */
extern int g_6a258c;			/* 0x006a258c */
extern int g_6a2590;			/* 0x006a2590 */
extern int g_6a2594;			/* 0x006a2594 */
extern int g_6a2598;			/* 0x006a2598 */
extern int g_6a25a0;			/* 0x006a25a0 */
extern int g_6a25a4;			/* 0x006a25a4 */
extern unsigned char g_77670c;		/* 0x0077670c */
extern char g_6b5c60[];			/* 0x006b5c60 */
extern char* g_1015ea0;			/* 0x01015ea0 */
#include "GOLDTL.fcn_00527f60_gconf.h"

int __cdecl fcn_0047a040(int, int, int, int);
int __cdecl fcn_0047cb60(int, int, int, int);
int __cdecl fcn_0046b2b0(int);
int __cdecl fcn_0046f740(int, int, int, int);
int __cdecl fcn_0046fac0(int, int, char*, int);
int __cdecl fcn_00469c30(int, int, int);
int __cdecl fcn_0046fcd0(int, int, char*);

/* ADDRESS: GOLDTL 0x00527f60 */
void __cdecl fcn_00527f60(unsigned char a0, int a1)
{
	if (g_slot_table[2 + g_774970 * 0x21c] != 6) {
		return;
	}
	fcn_0047a040(0, 0, g_1040494, g_1040490);
	if (g_774674) {
		fcn_0047cb60(g_14ce860 - 0x80, 0, g_77250c, g_774674);
	}
	if (g_774678) {
		fcn_0047cb60(g_14ce860 - 0x100, g_14ce864 - 0x80, g_77250c, g_774678);
	}
	if (g_77467c) {
		fcn_0047cb60(*(int*) (0x6a24d8 + g_77534c * 4), 0, g_77250c, g_77467c);
	}
	if (a0 & 1) {
		if (g_6a2578 != -1) {
			fcn_0046b2b0(g_6a2578);
			g_6a2578 = -1;
		}
		if (g_6a257c != -1) {
			fcn_0046b2b0(g_6a257c);
			g_6a257c = -1;
		}
		if (g_6a2580 != -1) {
			fcn_0046b2b0(g_6a2580);
			g_6a2580 = -1;
		}
		if (g_6a25a0 != -1) {
			fcn_0046b2b0(g_6a25a0);
			g_6a25a0 = -1;
		}
		if (g_6a25a4 != -1) {
			fcn_0046b2b0(g_6a25a4);
			g_6a25a4 = -1;
		}
		if (g_6a2584 != -1) {
			fcn_0046b2b0(g_6a2584);
			g_6a2584 = -1;
		}
		if (g_6a2588 != -1) {
			fcn_0046b2b0(g_6a2588);
			g_6a2588 = -1;
		}
		if (g_6a258c != -1) {
			fcn_0046b2b0(g_6a258c);
			g_6a258c = -1;
		}
		if (g_6a2590 != -1) {
			fcn_0046b2b0(g_6a2590);
			g_6a2590 = -1;
		}
		if (g_6a2594 != -1) {
			fcn_0046b2b0(g_6a2594);
			g_6a2594 = -1;
		}
		g_6a2578 = fcn_0046f740(0x10, 8, *(int*) (g_slot_table + 0x54 + g_774970 * 0x21c), g_6a2598);
		*(int*) (g_1015ea0 + 0x1d0 + g_6a2578 * 0x2f4) = 0x43;
		*(int*) (g_1015ea0 + 0x5c + g_6a2578 * 0x2f4) = 1;
		g_6a257c = fcn_0046f740(0x23a, 0xd, 0x522, g_6a2598);
		*(int*) (g_1015ea0 + 0x1d0 + g_6a257c * 0x2f4) = 0x43;
		*(int*) (g_1015ea0 + 0x5c + g_6a257c * 0x2f4) = 1;
		g_6a25a0 = fcn_0046fac0(0x39, 0xd, g_6b5c60, g_6a2598);
		*(int*) (g_1015ea0 + 0x1d0 + g_6a25a0 * 0x2f4) = 0x43;
		*(int*) (g_1015ea0 + 0x5c + g_6a25a0 * 0x2f4) = 1;
		*(int*) (g_1015ea0 + 0x84 + g_6a25a0 * 0x2f4) = 0x55;
		g_6a2588 = fcn_00469c30((short) (g_1040494 - 0x8d), (short) (g_1040490 - 0x73), 0x583);
		*(int*) (g_1015ea0 + 0x1d0 + g_6a2588 * 0x2f4) = 0x43;
		*(int*) (g_1015ea0 + 0x5c + g_6a2588 * 0x2f4) = 1;
		g_6a258c = fcn_00469c30((short) (g_1040494 - 0x57), (short) (g_1040490 - 0x4f), 0x7d9);
		*(int*) (g_1015ea0 + 0x1d0 + g_6a258c * 0x2f4) = 3;
		*(int*) (g_1015ea0 + 0x5c + g_6a258c * 0x2f4) = 1;
		g_6a2584 = fcn_00469c30((short) (g_1040494 - 0x2a), (short) (g_1040490 - 0x66), 0x584);
		*(int*) (g_1015ea0 + 0x1d0 + g_6a2584 * 0x2f4) = 0x43;
		*(int*) (g_1015ea0 + 0x5c + g_6a2584 * 0x2f4) = 1;
		g_6a2590 = fcn_00469c30((short) (g_1040494 - 0x4a), 0xd6, 0x585);
		*(int*) (g_1015ea0 + 0x1d0 + g_6a2590 * 0x2f4) = 0x43;
		*(int*) (g_1015ea0 + 0x5c + g_6a2590 * 0x2f4) = 1;
		g_6a2594 = fcn_00469c30((short) (g_1040494 - 0x48), 0xd7, 0x551);
		*(int*) (g_1015ea0 + 0x1d0 + g_6a2594 * 0x2f4) = 0x43;
		*(int*) (g_1015ea0 + 0x5c + g_6a2594 * 0x2f4) = 1;
		*(int*) (g_1015ea0 + 0x20 + g_6a2594 * 0x2f4) = 8;
		g_6a25a4 = fcn_0046fcd0((short) (g_1040494 - 0x6a), (short) (g_1040490 - 0x7e), g_6b5c60);
		*(int*) (g_1015ea0 + 0x6c + g_6a25a4 * 0x2f4) = 1;
		*(int*) (g_1015ea0 + 0x84 + g_6a25a4 * 0x2f4) = 0x54;
		*(int*) (g_1015ea0 + 0x18 + g_6a25a4 * 0x2f4) = 0x6b;
		*(int*) (g_1015ea0 + 0x1c + g_6a25a4 * 0x2f4) = 0x20;
	}
	else {
		if (g_77670c) {
			if (g_6a2578 != -1) {
				strcpy(g_1015ea0 + 0xcc + g_6a2578 * 0x2f4, *(char**) 0x14ad034);
			}
			if (g_6a257c != -1) {
				strcpy(g_1015ea0 + 0xcc + g_6a257c * 0x2f4, *(char**) 0x14ad040);
			}
			if (g_6a25a0 != -1) {
				strcpy(g_1015ea0 + 0xcc + g_6a25a0 * 0x2f4, *(char**) 0x14ad030);
			}
			if (g_6a2588 != -1) {
				strcpy(g_1015ea0 + 0xcc + g_6a2588 * 0x2f4, *(char**) 0x14ad02c);
			}
			if (g_6a2584 != -1) {
				strcpy(g_1015ea0 + 0xcc + g_6a2584 * 0x2f4, *(char**) 0x14ad028);
			}
			if (g_6a2594 != -1) {
				strcpy(g_1015ea0 + 0xcc + g_6a2594 * 0x2f4, *(char**) 0x14ad038);
			}
		}
		else {
			if (g_6a2578 != -1) {
				*(char*) (g_1015ea0 + 0xcc + g_6a2578 * 0x2f4) = *g_6b5c60;
			}
			if (g_6a257c != -1) {
				*(char*) (g_1015ea0 + 0xcc + g_6a257c * 0x2f4) = *g_6b5c60;
			}
			if (g_6a25a0 != -1) {
				*(char*) (g_1015ea0 + 0xcc + g_6a25a0 * 0x2f4) = *g_6b5c60;
			}
			if (g_6a2588 != -1) {
				*(char*) (g_1015ea0 + 0xcc + g_6a2588 * 0x2f4) = *g_6b5c60;
			}
			if (g_6a2584 != -1) {
				*(char*) (g_1015ea0 + 0xcc + g_6a2584 * 0x2f4) = *g_6b5c60;
			}
			if (g_6a2594 != -1) {
				*(char*) (g_1015ea0 + 0xcc + g_6a2594 * 0x2f4) = *g_6b5c60;
			}
		}
	}
}
unsigned char _dpad_100f8c0[26080];
