#include "Develop/Units/d2.v1/d2_gui.h"

extern char g_6811b0[];
extern char g_7f4ca0[];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern float g_662cf8; extern int g_6652f8[];

int __cdecl d2_SetForm(int win, int layer);
int __cdecl d2_AddElementToWindow(int x, int y, int id, int win);
int __cdecl d2_EqualizeWindowButtonWidths(int x, int y, char* text, int win);
void __cdecl d2_SetElementFont(int element, int value);
int __cdecl io_AppendText();
void __cdecl io_FormatTextBuffer(char* buf, char* fmt, ...);
void __cdecl d2_CreateWindowScrollbar(int x, int y, int owner, int other, int arg5,
                           int* id2, int* id1, int* id3);
void __cdecl d2_DrawSegmentedBar(int x0, int y, int len, int t);
void __cdecl d2_FormatWorkerFullName(void* a1, void* a2);
void __cdecl d2_FormatCandidateRolePair(char* o, char* buf);

/* ADDRESS: GOLDTL 0x0058bfd0 */
void __cdecl d2_RenderCandidateStatCards(int* ctx)
{
	int i;
	int saved;
	int n;
	int* v1;
	int v9;
	int v10;
	int v11;
	char buf[256];
	char buf2[256];
	int e;
	int j;
	int h;
	int y;
	int* r;

	n = 0;
	v1 = (int*) ctx[7];
	i = g_6652f8[v1[0]];
	if (i > 0) {
		e = 0;
		r = ctx + 0xc;
		do {
			if (*(int*) ((char*) v1[4] + e) != -1) {
				r[-1] = v1[4] + e;
				n++;
				h = *(int*) ((char*) v1[4] + e);
				r[-2] = -1;
				r[0] = h;
				r += 3;
			}
			e += 0x44;
		} while (--i);
	}
	if (n < 8) {
		r = ctx + n * 3 + 0xc;
		i = 8 - n;
		do {
			r[-1] = 0;
			*r = -1;
			r[-2] = -1;
			r += 3;
		} while (--i);
	}
	saved = *(int*) (ctx[2] * 0x3cc + 0x1016198);
	d2_SetForm(ctx[0], 2);
	io_AppendText(g_6811b0);
	d2_SetForm(ctx[0], 3);
	io_AppendText(g_6811b0);
	d2_SetForm(ctx[0], 5);
	io_AppendText(g_6811b0);
	d2_CreateWindowScrollbar(0, 0, ctx[4], ctx[2], *(int*) (ctx[2] * 0x3cc + 0x1015f50),
	             &v9, &v11, &v10);
	d2_SetForm(ctx[0], 2);
	i = 0;
	if (n > 0) {
		r = ctx + 0xb;
		do {
			h = *(int*) (ctx[2] * 0x3cc + 0x1015f4c);
			y = (h - *(short*) (g_772500 + 0x2399c)) / 2;
			r[-1] = d2_AddElementToWindow(y,
			                     *(int*) (ctx[2] * 0x3cc + 0x1015f50) * i + 2,
			                     0x6c7, ctx[2]);
			h = d2_AddElementToWindow(y + 2,
			                 *(int*) (ctx[2] * 0x3cc + 0x1015f50) * i + 4,
			                 *(int*) (*r + 0x3c), ctx[2]);
			r[-1] = h;
			*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[h].value_05c)) = 1;
			*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[r[-1]].flags_1d0)) = 3;
			d2_FormatWorkerFullName((void*) *r, buf);
			d2_FormatCandidateRolePair((char*) *r, buf2);
			y = *(int*) (ctx[2] * 0x3cc + 0x1015f50) * i + 0x38;
			h = d2_EqualizeWindowButtonWidths(0, y, buf, ctx[2]);
			*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[h].value_06c)) = 1;
			*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[h].width)) =
			    *(int*) (ctx[2] * 0x3cc + 0x1015f4c);
			d2_SetElementFont(h, 0x54);
			y += 0xd;
			h = d2_EqualizeWindowButtonWidths(0, y, buf2, ctx[2]);
			*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[h].value_06c)) = 1;
			*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[h].width)) =
			    *(int*) (ctx[2] * 0x3cc + 0x1015f4c);
			d2_SetElementFont(h, 0x54);
			y += 0x12;
			j = 0;
			do {
				io_FormatTextBuffer(buf, "%s:", 0x16b7 + j);
				h = d2_EqualizeWindowButtonWidths(0x28, y, buf, ctx[2]);
				*(int*) (((char*)&((D2_CONTROL_TL*)g_1015ea0)[h].width)) = 0x12c;
				d2_SetElementFont(h, 0x54);
				d2_DrawSegmentedBar(0xa0, y,
				             *(unsigned char*) (*r + 0x24 + j), 0x4df);
				j++;
				y += 0xd;
			} while (j < 5);
			i++;
			r += 3;
		} while (i < n);
	}
	*(int*) (ctx[2] * 0x3cc + 0x1016198) = saved;
	d2_SetForm(ctx[0], 5);
	io_AppendText(g_6811b0);
	io_FormatTextBuffer(buf, "%1N3",
	             *(unsigned short*) (g_7f4ca0 +
	                                 (unsigned int) g_774970 * 0x21c));
	io_AppendText("$7<$R%s$0<$4>$L%s$A$0>", 0x4101, buf);
	io_FormatTextBuffer(buf, "AD %i", *(unsigned short*) ((char*) v1 + 0xa) + 0x578);
	io_AppendText("$7<$R%s$0<$4>$L%s$A$0>", 0x4102, buf);
	io_FormatTextBuffer(buf, "%i %%",
	             (int) ((float) *(unsigned char*) ((char*) v1 + 0xc) *
	                    0.0039215689f * g_662cf8));
	io_AppendText("$7<$R%s$0<$4>$L%s$A$0>", 0x4103, buf);
}
