#include "client_data.h"
#include "Develop/Units/d2.v1/d2_win.h"
extern int main_LoopFlags;
extern int d2_CurrentWindowId;
#include "Develop/DieGildeAddOn/game/game_player.h"
extern char *g_1015ea0;


extern int g_14ad084;
extern int g_14ce8e0;
#include "client_dialog_state.h"
extern int g_100f1dc;
extern int d2_CurrentElementId;
extern char g_7f4ca0[];

struct d2_daterec {
	char day;
	char month;
	short year;
	int time;
	short rest;
};

int __cdecl fcn_00470820(int, int, char *);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl fcn_00471af0(int, int);
void __cdecl fcn_00471e30(int);
int __cdecl d2_GetWindowListItem(int, int, int);
void __cdecl fcn_00472640(int, int);
int __cdecl gm_HasActiveMission(int);
void __cdecl d2_ShowMissionForEntity(int);
void __cdecl cm_SendChangePlayerIdentity(int, int);
char *__cdecl gm_LookupEntityRecordById(int);
float __cdecl fcn_00505e30(unsigned short);
void __cdecl fcn_00509050(char *, char *);
int __cdecl fcn_00509120(char *, char *);
int __cdecl gm_AccumulateTyped2(char *);
int __cdecl gm_WalkEntityChain(unsigned short);
int __cdecl io_AppendText();
void __cdecl io_FormatTextBuffer();
int __cdecl fcn_00526120(char *, int);
void __cdecl fcn_00533a60(int, int, int *, int, char *, char *);
void __cdecl fcn_00534210(int, int, char *, int, int);
int __cdecl main_RunFrameLoop(int, int);
char *__cdecl he_StartHandlungSearch(int, ...);
char *__cdecl he_fn_Handlung(void);
int __cdecl d2_ShowGiftDialog(void *, void *);
int __cdecl fcn_005db8e0(void *, void *);
int __cdecl fcn_005dbb60(void *, void *);
int __cdecl _ftol(void);
int __cdecl d2_ShowTxt(int, int, char *, int);
#include "Develop/Units/d2.v1/d2_gui.h"
/* ADDRESS: GOLDTL 0x005d1790 */
void __cdecl fcn_005d1790(unsigned short *person, int a1)
{
	char bufB[512];
	char bufA[512];
	int msg;
	char buf12[64];
	int r5;
	int r4;
	int r3;
	struct d2_daterec dt;
	int r2;
	int r1;
	int h;
	int ok;
	int t;
	int inx;
	int i;
	int idx;
	int stamp;
	char *p;
	char *q;
	char *r;

	r1 = -1;
	r5 = -1;
	r3 = -1;
	ok = 0;
	r4 = -1;
	r2 = -1;
	msg = main_LoopFlags;
	h = fcn_00470820(0, 0, "panel\\info_spieler");
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(h);
	d2_SetForm(h, 1);
	io_AppendText(0x1f53, *person);
	d2_SetForm(h, 2);
	fcn_00509050((char *)person, (char *)&dt);
	io_FormatTextBuffer(buf12, "*%i.%i.%i", dt.day, dt.month, dt.year);
	io_AppendText("$3>$L%s$A$0>", buf12);
	if (fcn_00509120((char *)person, (char *)&dt) != 0) {
		io_FormatTextBuffer(buf12, "+%i.%i.%i", dt.day, dt.month, dt.year);
		io_AppendText("$3>$L%s$A$0>", buf12);
		ok = 1;
	} else {
		io_AppendText("$5<$R%s$0<$3>$L%i$A$0>", 0x1f54,
		    (int)fcn_00505e30(*person));
	}
	if (*((char *)person + 0x164) != 0) {
		io_AppendText("$5<$R%s$0<$3>$L%s$A$0>", 0x1f55,
		    *((unsigned char *)person + 0x164) + (*((char *)person + 9) != 0 ? 0x18f : 0x130));
	} else if (*((char *)person + 0x165) != 0) {
		io_AppendText("$5<$R%s$0<$3>$L%s$A$0>", 0x1f56,
		    *((unsigned char *)person + 0x165) + (*((char *)person + 9) != 0 ? 0x230 : 0x20d));
	}
	t = *((char *)person + 9) != 0 ? 0x27b : 0x253;
	if (*((char *)person + 0x166) == 0 && *((char *)person + 0x169) == 0) {
		io_FormatTextBuffer(buf12, "%s", "-");
		io_AppendText("$5<$R%s$0<$3>$L%s$A$0>", 0x1f57, buf12);
	}
	if (*((char *)person + 0x166) != 0 && *((char *)person + 0x169) != 0) {
		io_AppendText("$5<$R%s$0<$3>$L%s$A%s$A$0>", 0x1f57,
		    *((unsigned char *)person + 0x166) + t,
		    *((unsigned char *)person + 0x169) + t);
	} else if (*((char *)person + 0x166) != 0) {
		io_AppendText("$5<$R%s$0<$3>$L%s$A$0>", 0x1f57,
		    *((unsigned char *)person + 0x166) + t);
	} else if (*((char *)person + 0x169) != 0) {
		io_AppendText("$5<$R%s$0<$3>$L%s$A$0>", 0x1f57,
		    *((unsigned char *)person + 0x169) + t);
	}
	if (ok == 0) {
		io_AppendText("$5<$R%s$0<$3>$L%T$A$0>", 0x1f58, gm_WalkEntityChain(*person));
	} else {
		gm_WalkEntityChain(*person);
		io_AppendText("$5<$R%s$0<$3>$L%s$A$0>", 0x1f58, 0x679794);
	}
	p = gm_LookupEntityRecordById(*(int *)((char *)person + 0x5c));
	if (ok != 0) {
		*(unsigned short *)buf12 = *(unsigned short *)0x679794;
		io_AppendText("$5<$R%s$0<$3>$L%s$A$0>", g_14ad084, buf12);
	} else if (p != 0 && *((unsigned char *)p + 8) > 0) {
		io_FormatTextBuffer(buf12, 0x1f5f, *(unsigned short *)p);
		io_AppendText("$5<$R%s$0<$3>$L%s$A$0>", 0x1f59, buf12);
	} else {
		q = he_StartHandlungSearch(1, 0, 0x41);
		while (q != 0) {
			if (*(int *)(q + 0xac) == *(int *)((char *)person + 4)) {
				r = gm_LookupEntityRecordById(*(int *)(q + 0xb0));
				if (r != 0) {
					io_FormatTextBuffer(buf12, 0x1f5e, *(unsigned short *)r);
					io_AppendText("$5<$R%s$0<$3>$L%s$A$0>", 0x1f59, buf12);
					goto printed;
				}
				break;
			}
			q = he_fn_Handlung();
		}
		if (p != 0) {
			io_FormatTextBuffer(buf12, 0x1f60, *(unsigned short *)p);
			io_AppendText("$5<$R%s$0<$3>$L%s$A$0>", 0x1f59, buf12);
		} else {
			io_AppendText("$5<$R%s$0<$3>$L%s$A$0>", 0x1f59, 0x1f5d);
		}
	printed:
		;
	}
	io_AppendText("$5<$R%s $0<$3>$L%s$A$0>", 0x488,
	    (gm_GameTime.a < 0x75 ? 0x486 : 0x483) + *((unsigned char *)person + 0xc));
	io_AppendText("$5<$R%s$0<", 0x1f5a);
	ok = 0;
	p = (char *)person + 0x68;
	i = 5;
	do {
		q = gm_LookupEntityRecordById(*(int *)p);
		if (q != 0) {
			ok = 1;
			io_AppendText("$3>$L%1N1$A$0>", *(unsigned short *)q);
		}
		p += 4;
		i--;
	} while (i != 0);
	if (ok == 0) {
		io_AppendText("$3>$L-$A$0>");
	}
	d2_SetForm(h, 3);
	stamp = ((D2_WIN*)g_1015f40)[d2_CurrentWindowId].width;
	io_FormatTextBuffer(buf12, 0x1f61);
	idx = d2_ShowTxt(0, 1, buf12, d2_CurrentWindowId);
	((D2_CONTROL_TL*) (g_1015ea0))[idx].value_06c = 1;
	((D2_CONTROL_TL*) (g_1015ea0))[idx].width = stamp;
	inx = 2;
	i = 0;
	do {
		inx += 0x18;
		io_FormatTextBuffer(buf12, i + 0x16b7);
		d2_ShowTxt(10, inx - 1, buf12, d2_CurrentWindowId);
		fcn_00534210(0xaf, inx, (char *)person, i, 0x4e5);
		i++;
	} while (i < 5);
	io_FormatTextBuffer(buf12, 0x1f63);
	idx = d2_ShowTxt(0, 0x9a, buf12, d2_CurrentWindowId);
	inx = 7;
	((D2_CONTROL_TL*) (g_1015ea0))[idx].value_06c = 1;
	((D2_CONTROL_TL*) (g_1015ea0))[idx].width = stamp;
	if (*(int *)((char *)person + 0x2c) != 0) {
		if (*(int *)((char *)person + 0x2c) & 0xf) {
			io_FormatTextBuffer(buf12, 0x161e);
			idx = d2_ShowTxt(0, inx * 0x18 + 10, buf12, d2_CurrentWindowId);
			((D2_CONTROL_TL*) (g_1015ea0))[idx].value_06c = 1;
			((D2_CONTROL_TL*) (g_1015ea0))[idx].width = stamp;
			inx++;
		}
		if (*(int *)((char *)person + 0x2c) & 0xf0) {
			io_FormatTextBuffer(buf12, 0x161f);
			idx = d2_ShowTxt(0, inx * 0x18 + 10, buf12, d2_CurrentWindowId);
			((D2_CONTROL_TL*) (g_1015ea0))[idx].value_06c = 1;
			((D2_CONTROL_TL*) (g_1015ea0))[idx].width = stamp;
			inx++;
		}
		if (*(int *)((char *)person + 0x2c) & 0xf00) {
			io_FormatTextBuffer(buf12, 0x1620);
			idx = d2_ShowTxt(0, inx * 0x18 + 10, buf12, d2_CurrentWindowId);
			((D2_CONTROL_TL*) (g_1015ea0))[idx].value_06c = 1;
			((D2_CONTROL_TL*) (g_1015ea0))[idx].width = stamp;
			inx++;
		}
		if (*(int *)((char *)person + 0x2c) & 0x3000) {
			io_FormatTextBuffer(buf12, 0x1621);
			idx = d2_ShowTxt(0, inx * 0x18 + 10, buf12, d2_CurrentWindowId);
			((D2_CONTROL_TL*) (g_1015ea0))[idx].value_06c = 1;
			((D2_CONTROL_TL*) (g_1015ea0))[idx].width = stamp;
			inx++;
		}
		if (*(int *)((char *)person + 0x2c) & 0x1c000) {
			io_FormatTextBuffer(buf12, 0x1622);
			idx = d2_ShowTxt(0, inx * 0x18 + 10, buf12, d2_CurrentWindowId);
			((D2_CONTROL_TL*) (g_1015ea0))[idx].value_06c = 1;
			((D2_CONTROL_TL*) (g_1015ea0))[idx].width = stamp;
			inx++;
		}
		if (*(int *)((char *)person + 0x2c) & 0xe0000) {
			io_FormatTextBuffer(buf12, 0x1623);
			idx = d2_ShowTxt(0, inx * 0x18 + 10, buf12, d2_CurrentWindowId);
			((D2_CONTROL_TL*) (g_1015ea0))[idx].value_06c = 1;
			((D2_CONTROL_TL*) (g_1015ea0))[idx].width = stamp;
			inx++;
		}
		if (*(int *)((char *)person + 0x2c) & 0x700000) {
			io_FormatTextBuffer(buf12, 0x1624);
			idx = d2_ShowTxt(0, inx * 0x18 + 10, buf12, d2_CurrentWindowId);
			((D2_CONTROL_TL*) (g_1015ea0))[idx].value_06c = 1;
			((D2_CONTROL_TL*) (g_1015ea0))[idx].width = stamp;
			inx++;
		}
		if (*(int *)((char *)person + 0x2c) & 0x1800000) {
			io_FormatTextBuffer(buf12, 0x1625);
			idx = d2_ShowTxt(0, inx * 0x18 + 10, buf12, d2_CurrentWindowId);
			((D2_CONTROL_TL*) (g_1015ea0))[idx].value_06c = 1;
			((D2_CONTROL_TL*) (g_1015ea0))[idx].width = stamp;
			inx++;
		}
		if (*(int *)((char *)person + 0x2c) & 0x1e000000) {
			io_FormatTextBuffer(buf12, 0x1626);
			idx = d2_ShowTxt(0, inx * 0x18 + 10, buf12, d2_CurrentWindowId);
			((D2_CONTROL_TL*) (g_1015ea0))[idx].value_06c = 1;
			((D2_CONTROL_TL*) (g_1015ea0))[idx].width = stamp;
		}
	}
	if (a1 != 0) {
		d2_SetForm(h, 4);
		r5 = d2_GetWindowListItem(h, 4, io_AppendText(0x1f50, *person));
	} else {
		if ((*((char *)g_7f4ca0 + 540 * g_774970 + 9) == 0 &&
		     *(int *)((char *)person + 0x60) == *(int *)(g_7f4ca0 + 540 * g_774970 + 4)) ||
		    (*((char *)g_7f4ca0 + 540 * g_774970 + 9) == 1 &&
		     *(int *)((char *)person + 0x64) == *(int *)(g_7f4ca0 + 540 * g_774970 + 4))) {
			if (!(*((char *)person + 0x164) != 0)) {
				if (he_StartHandlungSearch(2, 2, *person, 0, 0x5e) == 0) {
					if (person[5] + 4 >= *(float *)((char *)person + 0x20)) {
						if ((*((unsigned char *)g_7f4ca0 + 540 * g_774970 + 0x1c8) & 0x20) == 0) {
							int buttons[2];
							io_FormatTextBuffer(bufA, 0x1f4b, *person);
							io_FormatTextBuffer(bufB, 0x1a96);
							d2_SetForm(h, 4);
							fcn_00533a60(d2_CurrentWindowId, 0, buttons, 2, bufA, bufB);
							r1 = buttons[0];
							r2 = buttons[1];
						}
						goto label_2281;
					}
				}
				if ((*((unsigned char *)g_7f4ca0 + 540 * g_774970 + 0x1c8) & 0x20) == 0) {
					io_FormatTextBuffer(bufA, 0x1f4b, *person);
					d2_SetForm(h, 4);
					r1 = d2_GetWindowListItem(h, 4,
					    io_AppendText("%ia[%s]", bufA));
				}
			} else {
				if ((*(int *)((char *)person + 0x1c8) & 0x10000) == 0) {
					if ((*((unsigned char *)g_7f4ca0 + 540 * g_774970 + 0x1c8) & 0x20) == 0) {
						int buttons[2];
						io_FormatTextBuffer(bufB, 0x1f4b, *person);
						io_FormatTextBuffer(bufA, 0x1a97);
						d2_SetForm(h, 4);
						fcn_00533a60(d2_CurrentWindowId, 0, buttons, 2, bufB, bufA);
						r1 = buttons[0];
						r4 = buttons[1];
					}
				} else if ((*((unsigned char *)g_7f4ca0 + 540 * g_774970 + 0x1c8) & 0x20) == 0) {
					io_FormatTextBuffer(bufA, 0x1f4b, *person);
					d2_SetForm(h, 4);
					r1 = d2_GetWindowListItem(h, 4,
					    io_AppendText("%ia[%s]", bufA));
				}
			}
		} else if (*(int *)(g_7f4ca0 + 540 * g_774970 + 4) == *(int *)((char *)person + 4) &&
		    gm_HasActiveMission(*(int *)((char *)person + 4)) != 0) {
			d2_SetForm(h, 4);
			r3 = d2_GetWindowListItem(h, 4, io_AppendText(0x1f49));
		}
	}
label_2281:
	g_100f1dc = -1;
	d2_CurrentElementId = -1;
	do {
		if (r1 != -1) {
			if (gm_AccumulateTyped2(g_7f4ca0 + 540 * g_774970) <= 0) {
				fcn_00472640(r1, 0);
			} else {
				fcn_00472640(r1, 1);
			}
		}
		if (g_14ce8e0 != 0) {
			g_774654 = 1;
		}
		if (g_100f1dc != -1) {
			fcn_00471af0(h, 0);
			if (d2_CurrentElementId == r5) {
				io_FormatTextBuffer(bufB, 0x1f51, *person, *person);
				if (fcn_00526120(bufB, 1) != 0) {
					cm_SendChangePlayerIdentity(*(int *)(g_7f4ca0 + 540 * g_774970 + 4),
					    *(int *)((char *)person + 4));
					g_774654 = 2;
				}
			} else if (d2_CurrentElementId == r1) {
				if (d2_ShowGiftDialog(g_7f4ca0 + 540 * g_774970, person) != 0) {
					fcn_00472640(r1, 0);
				}
			} else if (d2_CurrentElementId == r2) {
				if (fcn_005db8e0(g_7f4ca0 + 540 * g_774970, person) != 0) {
					fcn_00472640(r2, 0);
				}
			} else if (d2_CurrentElementId == r4) {
				if (fcn_005dbb60(g_7f4ca0 + 540 * g_774970, person) != 0) {
					fcn_00472640(r4, 0);
				}
			} else if (d2_CurrentElementId == r3) {
				d2_ShowMissionForEntity(*(int *)((char *)person + 4));
			}
			fcn_00471af0(h, 1);
		}
	} while (main_RunFrameLoop((int)fcn_005d1790, msg) != 0);
	fcn_00471e30(h);
}
