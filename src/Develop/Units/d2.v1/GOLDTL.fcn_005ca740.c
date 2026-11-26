
extern int __cdecl d2_AddElementToWindow(int x, int y, int id, int ctx);
extern int __cdecl io_FormatTextBuffer(char* dst, const char* fmt, ...);
extern int __cdecl fcn_005c9090(char* text, int x, int y, int color, int flags);
extern int __cdecl fcn_004677e0(int x, int y, int w, int a, int b, int c, int d, int ctx);
extern float __cdecl gm_CalcEntityFavor(unsigned int, unsigned int, unsigned int);
#include "d2_gui.h"
extern int __cdecl fcn_00472640(int element, int a);
#include "Develop/DieGildeAddOn/game/game_data.h"
/* Draw the trade-good detail window: create the frame and the four value
 * labels, format the two lines of text into the message buffer, draw the
 * unit icon plus its 0xca-wide gauges, then create the element and kick off
 * its animation. */
/* ADDRESS: GOLDTL 0x005ca740 */
int __cdecl fcn_005ca740(int a0, int a1, int a2, int a3, int* row, int a5)
{
	int v8;
	int v10;
	int v5;
	int v6;
	int v7; unsigned char kind;
	char buf[0x100];

	(void) a2;
	v10 = ((D2_BILD_GROESSE*)g_772500)[0x5da].breite / 2 + a0;
	v8 = a1 + 0x1c;
	row[1] = d2_AddElementToWindow(a0, v8, 0x5da, d2_CurrentWindowId);
	row[2] = -1;
	if (row[0] != 0) {
		v5 = *(int*) (row[0] + 0x18c);
		row[6] = d2_AddElementToWindow(v10 - ((D2_BILD_GROESSE*)g_772500)[v5].breite / 2 - 3,
		                     a1 + 0x1d, v5, d2_CurrentWindowId);
		d2_AddElementToWindow(a0 + 3, a1 + 0x1f, row[7], d2_CurrentWindowId);
		if (row[8])
			d2_AddElementToWindow(a0 + 3, ((D2_BILD_GROESSE*)g_772500)[0x5da].hoehe + 9 + a1,
			             row[8], d2_CurrentWindowId);
		if (row[9])
			d2_AddElementToWindow(((D2_BILD_GROESSE*)g_772500)[0x5da].breite - 0x10 + a0,
			             a1 + 0x1f, row[9], d2_CurrentWindowId);
		d2_AddElementToWindow(((D2_BILD_GROESSE*)g_772500)[0x5da].breite - 0x10 + a0,
		             ((D2_BILD_GROESSE*)g_772500)[0x5da].hoehe + 9 + a1, row[10],
		             d2_CurrentWindowId);
		if (a5 && *(unsigned char*) (row[0] + 0xd))
			io_FormatTextBuffer(buf, (const char*) 0x6ac964,
			             ((*(unsigned char*) (row[0] + 9) != 0) ? 10 : 0) + 0x114 +
			                 *(unsigned char*) (row[0] + 0xd),
			             *(unsigned short*) row[0]);
		else
			io_FormatTextBuffer(buf, (const char*) 0x6ac96c, *(unsigned short*) row[0]);
		v7 = a3;
		fcn_005c9090(buf, v10, row[5], 0xca, a3);
		io_FormatTextBuffer(buf, (const char*) 0x6ac95c, *(unsigned short*) row[0]);
		fcn_005c9090(buf, v10, row[5] + 0xe, 0xca, v7);
		if (*(unsigned char*) (row[0] + 2) != 6) {
			v6 = fcn_004677e0(v10 - 0x23, ((D2_BILD_GROESSE*)g_772500)[0x5da].hoehe + 0x1e + a1,
			                  0x40, 0, 100, 0x75, 0x442, d2_CurrentWindowId);
			row[2] = v6;
			if (*(unsigned char*) (row[0] + 2) != 7) {
				d2_SetElementValue(row[2], 0, 100, (int)gm_CalcEntityFavor(*(unsigned short*) &g_774970,
				             *(unsigned short*) row[0], 1));
			} else {
				d2_SetElementValue(v6, 0, 100, 0, 1);
			}
			fcn_00472640(row[2], 0);
		}
		if (row[0xc]) {
			*(int*) ((int)((char*)&((D2_CONTROL_TL*)g_1015ea0)[row[1]].value_05c)) = 1;
			*(int*) ((int)((char*)&((D2_CONTROL_TL*)g_1015ea0)[row[1]].flags_1d0)) = 3;
			*(int*) ((int)((char*)&((D2_CONTROL_TL*)g_1015ea0)[row[1]].associated_object)) = row[0];
		}
		kind = *(unsigned char*) (row[0] + 2);
		if (kind != 5 && kind != 6 && kind != 7)
			return 0;
		d2_AddElementToWindow(a0 - 0x20, v8, *(int*) (row[0] + 0x54), d2_CurrentWindowId);
	} else {
		d2_AddElementToWindow(v10 - ((D2_BILD_GROESSE*)g_772500)[0x4fb].breite / 2 - 3,
		             a1 + 0x1d, 0x4fb, d2_CurrentWindowId);
	}
	return 0;
}
