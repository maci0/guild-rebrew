/* Owned (GOLDTL) by src/GOLDTL.fcn_004da4d0.c. */
extern int d2_CurrentWindowId;
extern int d2_VoteRow0Count;
extern int d2_VoteRow1Count;
extern int d2_VoteRow2Count;

void __cdecl d2_ClearWindowChildren(int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
#include "Develop/Units/d2.v1/d2_gui.h"
void __cdecl d2_SetElementFont(int, int);
void __cdecl d2_AddElementToWindow(int, int, int, int);


/* The positional GOLD twin 0x4d8cb0 is NOT the same build: its first 0xcf bytes
 * match, then the a3 branches drop the reference's `movsx eax,dx` truncation
 * (`lea edx,[eax+eax*4+0x28] / add edx,edx / push edx`) where GOLDTL has
 * `... / movsx eax,dx / push eax`, and the a3==1 arm schedules its
 * `g_772514` load before the counter load.  The `(short)` cast is source-level,
 * so one body cannot carry both markers; the file stays GOLDTL-only. */

/* ADDRESS: GOLDTL 0x004da510 */
/* ADDRESS: GOLDDE 0x004c6fe0 */
void __cdecl d2_UpdateVoteTallyIcons(int a1, int reset, int row)
{
	char buf[0x40];
	int h;

	if (reset != 0) {
		d2_ClearWindowChildren(d2_CurrentWindowId, 1);
		io_FormatTextBuffer(buf, 0x12d3);
		h = d2_ShowTxt(0, 0x20, buf, d2_CurrentWindowId);
		d2_SetElementFont(h, 0x54);
		io_FormatTextBuffer(buf, 0x12d4);
		h = d2_ShowTxt(0, 0x3e, buf, d2_CurrentWindowId);
		d2_SetElementFont(h, 0x54);
		io_FormatTextBuffer(buf, 0x12d5);
		h = d2_ShowTxt(0, 0x2f, buf, d2_CurrentWindowId);
		d2_SetElementFont(h, 0x54);
		d2_VoteRow0Count = 0;
		d2_VoteRow1Count = 0;
		d2_VoteRow2Count = 0;
		return;
	}
	if (row == 0) {
		d2_AddElementToWindow((short) ((d2_VoteRow0Count * 5 + 40) * 2), 0x20, 0x4df, d2_CurrentWindowId);
		d2_VoteRow0Count++;
		return;
	}
	if (row == 1) {
		d2_AddElementToWindow((short) ((d2_VoteRow1Count * 5 + 40) * 2), 0x3e, 0x4df, d2_CurrentWindowId);
		d2_VoteRow1Count++;
		return;
	}
	if (row == 2) {
		d2_AddElementToWindow((short) ((d2_VoteRow2Count * 5 + 40) * 2), 0x2f, 0x4df, d2_CurrentWindowId);
		d2_VoteRow2Count++;
	}
}
unsigned char _dpad_772ec4[84];
