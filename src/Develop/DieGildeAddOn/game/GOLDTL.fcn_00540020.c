/*
 * Round/day refresh for the town view.
 *
 * Takes the active slot record, rebuilds the day rectangle from the clock
 * state and then refreshes the HUD element that carries the current date.
 *
 * Reconstructed range 0x540020..0x5400c2. The native body continues at
 * 0x5400c2 with the g_6a3420 branch and the rest of the refresh through
 * 0x541149; that part is not reconstructed here.
 */

extern unsigned short g_774970;		/* 0x00774970 */
extern unsigned char g_7747b0;		/* 0x007747b0 */
extern int g_774950;			/* 0x00774950 */
#include "GOLDTL.fcn_00540020_gconf.h"

int __cdecl gm_GetEntityTableEntry(unsigned char*);
int __cdecl fcn_00500e20(int*);
int __cdecl fcn_0052a310(int*);
int __cdecl fcn_004ec9e0(void);

/* ADDRESS: GOLDTL 0x00540020 */
void __cdecl fcn_00540020(void)
{
	int v10;
	int v24;
	int v25;
	unsigned short v26;
	int v5;

	v5 = gm_GetEntityTableEntry(g_slot_table + (g_774970 & 0xffff) * 0x21c);
	fcn_00500e20((int*) 0x7f4c00);
	v24 = *(int*) 0x7f4c04;
	v10 = *(int*) 0x7f4c00;
	v25 = *(int*) 0x7f4c08;
	v26 = *(unsigned short*) 0x7f4c0c;
	if ((g_7747b0 & 4) && (2 <= g_774950)) {
		v10 = *(int*) 0x7f4c00 + 1;
	}
	fcn_0052a310(&v10);
	fcn_004ec9e0();
	*(int*) (v5 + 0x58) = 0x3f000000;
	*(int*) (v5 + 0x5c) = 0x3f800000;
	*(int*) (v5 + 0x60) = 0x3f800000;
}
