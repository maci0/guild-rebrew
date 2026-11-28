#include "Develop/Units/d2.v1/client_dialog_helpers.h"
#include "Develop/Units/d2.v1/d2_gui.h"
extern unsigned char d2_PlotRadius;
extern int d2_CurrentWindowId;
extern int d2_WindowMetricsView;
extern int g_1015f50;
extern unsigned char *d2_Controls;
extern int gm_GameTime;
extern int gm_GameTimeHour;
extern int gm_GameTimeSliceDword;
extern short gm_GameTimeTailWord;
extern float g_6628bc;
extern float g_662924;
extern float g_66293c;
extern float g_662a98;

typedef struct {
	int f[10];
} Arg;

typedef struct {
	float f[10];
} Gfx;

typedef struct {
	char out[12];
	int src[4];
	char buf[0x10];
} Loc;

void __cdecl d2_ClearPaintbox(void);
void __cdecl d2_DrawLine(int, int, int, int, int, int, int);
int __cdecl d2_EqualizeWindowButtonWidths(int, int, char *, int);
int __cdecl d2_MeasureTextWidth(char *, int);
void __cdecl gm_PackGameTime(int *, char *);
int __cdecl d2_DrawHistoryGraph(Arg, int, int);
void __cdecl io_FormatTextBuffer(char *, char *, ...);

/* ADDRESS: GOLDTL 0x005d3d90 */
void __cdecl d2_DrawCityHistoryCharts(unsigned short flags, Gfx g, int win)
{
	unsigned char saved;
	int m;
	int h;
	Loc loc;
	int w;
	int step;
	int i;
	int n;
	int id;
	int x1;
	int x2;
	int d;
	float y;

	m = 0;
	saved = d2_PlotRadius;
	d2_ClearPaintbox();
	d2_ClearWindowChildren(win, 1);
	d2_PlotRadius = 1;
	w = *(int *) ((char *) &d2_WindowMetricsView + win * 0x3cc);
	h = *(int *) ((char *) &g_1015f50 + win * 0x3cc);
	step = (w - 0x69) / 16;
	if (flags & 1)
		m = d2_DrawHistoryGraph(*(Arg *) &g, w - 1, h);
	d2_PlotRadius = 1;
	if (flags & 2)
		d2_DrawMoodHistoryGraph(*(Arg *) &g, w - 1, h);
	if (flags & 4)
		d2_DrawRedHistoryGraph(*(GRAPH_VALUE *) &g, w - 1, h);
	if (flags & 8)
		d2_DrawYellowHistoryGraph(*(GRAPH_VALUE *) &g, w - 1, h);
	if (flags & 0x10)
		d2_DrawMagentaHistoryGraph(*(GRAPH_VALUE *) &g, w - 1, h);
	d2_PlotRadius = 0;
	d2_DrawLine(0x2d, 8, 0x2d, h - 0x13, 0x10, 0x10, 0x10);
	d2_DrawLine(0x2d, h - 0x13, w - 0x3b, h - 0x13, 0x10, 0x10, 0x10);
	y = (float) h - g_66293c;
	for (i = 0; i < 4; i++) {
		n = (int) ((float) i * g_6628bc * y + g_662924);
		d2_DrawLine(0x28, n, 0x2d, n, 0x10, 0x10, 0x10);
	}
	for (i = 0, n = 0x64; n > 0; i++, n -= 0x19) {
		io_FormatTextBuffer(loc.buf, (char *) 0x6acbec, n);
		id = d2_EqualizeWindowButtonWidths(3, (int) ((float) i * g_6628bc * y + 5.0f), loc.buf, d2_CurrentWindowId);
		*(int *) (((char*)&((D2_CONTROL_TL*)d2_Controls)[id].width)) = 0x23;
		*(int *) (((char*)&((D2_CONTROL_TL*)d2_Controls)[id].value_070)) = 1;
	}
	if (m != 0) {
		x1 = w - 0x3c;
		d2_DrawLine(x1, 8, x1, h - 0x13, 0x10, 0x10, 0x10);
		x2 = w - 0x37;
		d2_DrawLine(x2, 8, x1, 8, 0x10, 0x10, 0x10);
		d2_DrawLine(x2, (h - 0x1e) / 2 + 8, x1, (h - 0x1e) / 2 + 8, 0x10, 0x10, 0x10);
		io_FormatTextBuffer(loc.buf, (char *) 0x67d444, m);
		d = d2_MeasureTextWidth(loc.buf, 0x55) + 2;
		id = d2_EqualizeWindowButtonWidths(x1, 5, loc.buf, d2_CurrentWindowId);
		*(int *) (((char*)&((D2_CONTROL_TL*)d2_Controls)[id].width)) = d;
		*(int *) (((char*)&((D2_CONTROL_TL*)d2_Controls)[id].value_070)) = 1;
		io_FormatTextBuffer(loc.buf, (char *) 0x67d444, m / 2);
		id = d2_EqualizeWindowButtonWidths(x1, (h - 0x1e) / 2 + 5, loc.buf, d2_CurrentWindowId);
		*(int *) (((char*)&((D2_CONTROL_TL*)d2_Controls)[id].width)) = d;
		*(int *) (((char*)&((D2_CONTROL_TL*)d2_Controls)[id].value_070)) = 1;
	}
	loc.src[0] = gm_GameTime;
	loc.src[1] = gm_GameTimeHour;
	loc.src[2] = gm_GameTimeSliceDword;
	*(short *) ((char *) loc.src + 0xc) = gm_GameTimeTailWord;
	gm_PackGameTime(loc.src, loc.out);
	if (loc.out[1] == 1) {
		io_FormatTextBuffer(loc.buf, (char *) 0x67d444, *(short *) (loc.out + 2));
		d = d2_MeasureTextWidth(loc.buf, 0x55);
		id = d2_EqualizeWindowButtonWidths(step * 16 + 0x2d, h - 0xd, loc.buf, d2_CurrentWindowId);
		*(int *) (((char*)&((D2_CONTROL_TL*)d2_Controls)[id].width)) = d;
	}
	loc.src[0]--;
	gm_PackGameTime(loc.src, loc.out);
	for (i = 0xf; i != 0; i--) {
		n = step * i + 0x2d;
		d2_DrawLine(n, h - 0x13, n, h - 0x10, 0x10, 0x10, 0x10);
		if (loc.out[1] == 1) {
			io_FormatTextBuffer(loc.buf, (char *) 0x67d444, *(short *) (loc.out + 2));
			d = d2_MeasureTextWidth(loc.buf, 0x55);
			id = d2_EqualizeWindowButtonWidths(n, h - 0xd, loc.buf, d2_CurrentWindowId);
			*(int *) (((char*)&((D2_CONTROL_TL*)d2_Controls)[id].width)) = d;
			d2_DrawLine(n, h - 0x13, n, h - 0xd, 0x10, 0x10, 0x10);
		}
		loc.src[0]--;
		gm_PackGameTime(loc.src, loc.out);
	}
	if (loc.out[1] == 1) {
		io_FormatTextBuffer(loc.buf, (char *) 0x67d444, *(short *) (loc.out + 2));
		d = d2_MeasureTextWidth(loc.buf, 0x55);
		id = d2_EqualizeWindowButtonWidths(0x2d, h - 0xd, loc.buf, d2_CurrentWindowId);
		*(int *) (((char*)&((D2_CONTROL_TL*)d2_Controls)[id].width)) = d;
	}
	d2_PlotRadius = saved;
}
