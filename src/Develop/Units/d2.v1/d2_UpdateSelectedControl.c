#include "Develop/Units/d2.v1/d2_gui.h"
extern void __cdecl d2_ClearSelectedControl(void);
extern void __cdecl d2_DestroyElement(int a);
extern int __cdecl CountDisplayCounters(void);
extern void __cdecl d2_PositionControl(int a, int b, int c);
extern int __cdecl d2_CreateElement(short a, short b, int c);
extern void __cdecl d2_HandleTextInput(void);
extern int __cdecl d2_UpdateSelectedControlDrag(void);
extern void __cdecl d2_SetFieldTextId(int a, int b);
extern void __cdecl d2_HandleSliderInput(void);
extern void __cdecl d2_SetMouseTooltip(void *p);
extern int __cdecl d2_GetValueStep(void *p);
extern void __cdecl io_ClearInputButtonFlags(int a);
extern int __cdecl d2_MeasureTextWidth(void *p, int a);
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_100f1cc;
extern int g_100f1d4;
extern int g_100f1d8;
extern int g_100f1e0;
extern int g_100f898;
extern int g_100f89c;
extern int g_100f940;
extern int g_100f950;
extern int g_14ce8dc;
extern int g_67d3b0;
extern int g_67d8ec;
extern int g_7725e4;
extern int g_7725e8;
/* ADDRESS: GOLDTL 0x004748b0 */
int __cdecl d2_UpdateSelectedControl(void)
{
	unsigned int *p;
	unsigned int *candidateControl;
	int v7;
	int v8;
	int i;
	if (g_7725e8 && !g_14ce8dc) {
		p = *(unsigned int **) &tp_d2_SelectedControl;
		if (!g_14ce8d0 || p == 0
		    || !(*(unsigned char *) ((char *) p + 0x28) & 2)) {
			g_7725e8 = 0;
			d2_MouseBottomBoundary = g_100f1d8;
			d2_MouseTopBoundary = g_100f1e0;
			d2_ClearSelectedControl();
		}
	}
	p = *(unsigned int **) &tp_d2_SelectedControl;
	v7 = (short) *(short *) &io_ActiveCursorY;
	if (!g_14ce8d0) {
		g_7725e4 = 0;
	}
	if (p == 0 && g_67d8ec != -1) {
		d2_DestroyElement(g_67d8ec);
		g_67d8ec = -1;
		p = *(unsigned int **) &tp_d2_SelectedControl;
	}
	if (d2_CurrentElementId != -1) {
		v8 = (int)&((D2_CONTROL_TL*) *(int *)&d2_Controls)[d2_CurrentElementId];
		if (*(int *) (v8 + 0x20) == 0x41) {
			candidateControl = *(unsigned int **) (v8 + 0xc);
			if (d2_CurrentElementId == (int) candidateControl[0x4d]) {
				if (!g_14ce8d0) {
					goto label_474b14;
				}
				if (p == candidateControl || g_7725e4) {
					goto label_474afe;
				}
				if (p != 0) {
					((D2_CONTROL_TL*) *(int *)&d2_Controls)[p[0x4d]].value_03c = 0;
				}
				((D2_CONTROL_TL*) *(int *)&d2_Controls)[candidateControl[0x4d]].value_03c = 1;
				v8 = *(int *)&((D2_CONTROL_TL*) *(int *)&d2_Controls)[candidateControl[0x4d]].parent;
				g_100f940 = candidateControl[0x4b];
				g_100f950 = 0;
				g_100f1d4 = d2_MouseBottomBoundary - v7;
				i = 0;
				if (v8 != 0) {
					while (i < *(int *) (v8 + 0x2c)) {
						if (*(int *) (*(int *) (v8 + 0x28) + i * 4) == (int) candidateControl[0x4d]) {
							g_100f1cc = i;
						}
						i++;
					}
				}
				p = candidateControl;
				*(unsigned int **) &tp_d2_SelectedControl = candidateControl;
				if ((*(unsigned char *) ((char *) candidateControl + 0x28) & 0x40) && !candidateControl[6]
				    && !candidateControl[7] && !CountDisplayCounters() && !candidateControl[0x4b]) {
					candidateControl[0x4b] = 0xffffffff;
					p = *(unsigned int **) &tp_d2_SelectedControl;
				}
				if (*(unsigned char *) ((char *) p + 0x28) & 1) {
					g_100f898 = d2_MeasureTextWidth((char *) p + 0x2c, p[0x4e]);
					g_100f898 += p[1];
					g_100f89c = p[2];
					if (g_67d8ec != -1) {
						d2_PositionControl(g_100f898, g_100f89c - 7,
						    g_67d8ec);
					} else {
						g_67d8ec = d2_CreateElement(
						    (short) g_100f898,
						    (short) (g_100f89c - 7),
						    g_67d3b0 + 8);
					}
				} else if (g_67d8ec != -1) {
					d2_DestroyElement(g_67d8ec);
					g_67d8ec = -1;
				}
				p = *(unsigned int **) &tp_d2_SelectedControl;
			}
		}
	}
label_474afe:
	if (g_14ce8d0) {
		if (p == 0) {
			goto label_474b96;
		}
		g_7725e4 = 1;
	}
label_474b14:
	if (p != 0 && d2_CurrentElementId == (int) p[0x4d]
	    && (*(unsigned char *) ((char *) p + 0x28) & 2)
	    && g_14ce8d8) {
		if ((int) p[0x4b] < (int) p[6] && p[0x4b] != 0xffffffff
		    && p[0x4f] != 0xffffffff) {
			v7 = d2_GetValueStep(p);
			p[0x4b] += v7;
			p = *(unsigned int **) &tp_d2_SelectedControl;
		}
		if (!p[6] && !p[7] && !CountDisplayCounters() && !p[0x4b]
		    && (*(unsigned char *) ((char *) p + 0x28) & 0x40)) {
			p[0x4b] = 0xffffffff;
			p = *(unsigned int **) &tp_d2_SelectedControl;
		}
	}
label_474b96:
	if (io_RightButtonReleased) {
		if (p == 0) {
			goto label_474ca4;
		}
		if (*(unsigned char *) ((char *) p + 0x28) & 1) {
			io_ClearInputButtonFlags(0x10);
			p = *(unsigned int **) &tp_d2_SelectedControl;
		}
		((D2_CONTROL_TL*) *(int *)&d2_Controls)[p[0x4d]].value_03c = 0;
		*(unsigned int **) &tp_d2_SelectedControl = 0;
		g_7725e4 = 0;
		if (g_67d8ec == -1) {
			goto label_474ca4;
		}
		d2_DestroyElement(g_67d8ec);
		g_67d8ec = -1;
		p = *(unsigned int **) &tp_d2_SelectedControl;
	}
	if (p != 0) {
		if (!g_14ce8d0) {
			g_100f950 = 1;
			g_14ce8d8 = 0;
		}
		d2_HandleTextInput();
		if (d2_UpdateSelectedControlDrag()) {
			return 1;
		}
		if (*(unsigned int **) &tp_d2_SelectedControl != 0
		    && (*(unsigned char *) (*(int *) &tp_d2_SelectedControl + 0x28) & 0x10)
		    && d2_CurrentElementId == (int) (*(unsigned int **) &tp_d2_SelectedControl)[0x4d]
		    && g_14ce8d8) {
			candidateControl = *(unsigned int **) &tp_d2_SelectedControl;
			candidateControl[0x53] = candidateControl[0x53] + 1;
			if ((int) (candidateControl[0x54] + 0xffffffff + candidateControl[0x52]) < (int) candidateControl[0x53]) {
				candidateControl[0x53] = candidateControl[0x52];
			}
			d2_SetFieldTextId(candidateControl[0], candidateControl[0x53]);
		}
	}
label_474ca4:
	d2_HandleSliderInput();
	if (d2_CurrentElementId != -1) {
		v7 = (int)&((D2_CONTROL_TL*) *(int *)&d2_Controls)[d2_CurrentElementId];
		if (*(unsigned char *) (v7 + 0x1d0) & 0x40) {
			d2_SetMouseTooltip((void *) (v7 + 0xcc));
		}
	}
	return 0;
}
