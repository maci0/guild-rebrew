/* Owned (GOLDTL) by src/GOLDTL.fcn_004da4d0.c. */
extern int g_772514;
extern int g_772f1c;
extern int g_772f18;
extern int g_772f20;

void __cdecl fcn_0046f2c0(int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl fcn_00472900(int, int);
void __cdecl fcn_0046f740(int, int, int, int);


/* The positional GOLD twin 0x4d8cb0 is NOT the same build: its first 0xcf bytes
 * match, then the a3 branches drop the reference's `movsx eax,dx` truncation
 * (`lea edx,[eax+eax*4+0x28] / add edx,edx / push edx`) where GOLDTL has
 * `... / movsx eax,dx / push eax`, and the a3==1 arm schedules its
 * `g_772514` load before the counter load.  The `(short)` cast is source-level,
 * so one body cannot carry both markers; the file stays GOLDTL-only. */

/* ADDRESS: GOLDTL 0x004da510 */
void __cdecl fcn_004da510(int a1, int a2, int a3)
{
	char buf[0x40];
	int h;

	if (a2 != 0) {
		fcn_0046f2c0(g_772514, 1);
		io_FormatTextBuffer(buf, 0x12d3);
		h = d2_ShowTxt(0, 0x20, buf, g_772514);
		fcn_00472900(h, 0x54);
		io_FormatTextBuffer(buf, 0x12d4);
		h = d2_ShowTxt(0, 0x3e, buf, g_772514);
		fcn_00472900(h, 0x54);
		io_FormatTextBuffer(buf, 0x12d5);
		h = d2_ShowTxt(0, 0x2f, buf, g_772514);
		fcn_00472900(h, 0x54);
		g_772f1c = 0;
		g_772f18 = 0;
		g_772f20 = 0;
		return;
	}
	if (a3 == 0) {
		fcn_0046f740((short) ((g_772f1c * 5 + 40) * 2), 0x20, 0x4df, g_772514);
		g_772f1c++;
		return;
	}
	if (a3 == 1) {
		fcn_0046f740((short) ((g_772f18 * 5 + 40) * 2), 0x3e, 0x4df, g_772514);
		g_772f18++;
		return;
	}
	if (a3 == 2) {
		fcn_0046f740((short) ((g_772f20 * 5 + 40) * 2), 0x2f, 0x4df, g_772514);
		g_772f20++;
	}
}
unsigned char _dpad_772ec4[84];
