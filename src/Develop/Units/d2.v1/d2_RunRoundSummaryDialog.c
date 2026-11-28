#include <string.h>

extern int g_774970;
extern int g_774968;
extern int g_774978;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern int g_7e2700;
extern int main_LoopFlags;
extern int g_6a3420;
extern int d3_ActiveCamera;
extern int d2_CurrentWindowId;
extern int g_77250c;
extern int g_77255c;
extern int g_1040480;
extern int g_1040484;
extern int g_1040488;
extern int g_104048c;
extern int d2_ScreenHeight;
extern int g_1040494;
extern int g_100f1dc;
extern char g_14cf950;
extern char gm_GameTime[];
extern char g_7f4ca0[];
extern double g_6640e8;

int __cdecl io_AppendText(int, ...);
char* __cdecl d2_StartScreenFade(int, int, int, int, char*, int, int);
void __cdecl d2_ReleaseOverlaySprite(unsigned char*);
int __cdecl main_RunFrameLoop(int, int);
int __cdecl fcn_00509570(int);
void __cdecl d3_SetNodePosition(char*, int*);
void __cdecl d3_SetObjectRotation(char*, int*);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_DestroyHudOverlay(void);
void __cdecl d2_UpdateViewportCenter(int);
int __cdecl d2_CreateScrollPerga(void);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
void __cdecl gm_PackGameTime(void*, void*);
int __cdecl fcn_00503fe0(int, int);
int __cdecl fcn_00503e80(void);
int __cdecl fcn_00504bd0(int);
int __cdecl gm_CalcBuildingRoundBalance(char*, int, int*);
int __cdecl he_GetActiveKrediteByLender(int, int, int, int*);
int __cdecl he_GetActiveKrediteByBorrower(int, char*, int*);
int __cdecl fcn_0050d2a0(int);
int __cdecl amt_ProcessPrivilegeIncome(unsigned short, int, int*);
int __cdecl gm_CalcEntityTaxSlots(unsigned short, int*, int);
void __cdecl d2_ToggleActionPopupBar(int);
void __cdecl d2_ClearSurface(int);
void __cdecl d2_SetBackdropResource(int);
void __cdecl d2_AddWindowScrollButtons(int, int, int, int, int);
void __cdecl sb_PlayVoice(char*, char*, int, int, int, int, int);
void __cdecl d2_UpdateScrollPerga(void);
void __cdecl d2_DestroyScrollPerga(void);
int __cdecl gm_CheckAndCollectEntityDebt(char*, int);
void __cdecl cut_ExecuteCutscene(void*);
void __cdecl gm_ResetDynastySlot(int);


/* Black editor panel for the current 0x7f4ca0 entity: prints the building
 * and unit counters, then runs the modal 0x24087 message loop. */
/* ADDRESS: GOLDTL 0x00541620 */
void __cdecl d2_RunRoundSummaryDialog(void)
{
	unsigned char panel[0x114];
	struct { unsigned char names[6]; int vals[6]; int vals2[6]; } revenue;

	int dlg;
	int info[0x15];
	int v1d0[10];
	int stamp[10];
	unsigned char* win;
	char* ent;

	unsigned char b;
	int runningTotal;
	int b200;
	int c1fc;
	int d1f8;
	int e1ec;
	int f1e8;
	int g1f4;
	int h1f0;
	int n;
	int i;
	int k;
	int sel;
	int kind;
	double dbl;

	b200 = 0;
	runningTotal = 0;
	f1e8 = 0;
	g1f4 = 0;
	e1ec = 0;
	*(int*) (char*) &g_7e2700 = 0;
	if (g_6a3420 != 0) {
		win = (unsigned char*) d2_StartScreenFade(0, 0, g_1040494, d2_ScreenHeight, "BLACK", 0x1e, 1);
		while ((*win & 4) == 0) {
			main_RunFrameLoop(0, main_LoopFlags);
		}
		g1f4 = (int) win;
	}

	sel = (int) fcn_00509570((((unsigned short)g_774970) & 0xffff) * 0x21c + (int) (char*) g_7f4ca0);
	k = (((unsigned short)g_774970) & 0xffff) * 0x21c;
	*(int*) (sel + 0x3c) += *(int*) (k + 0x7f4e44) + *(int*) (k + 0x7f4e40);
	d3_SetNodePosition((char*) d3_ActiveCamera, (int*) (sel + 0x8c));
	d3_SetObjectRotation((char*) d3_ActiveCamera, (int*) (sel + 0x9c));
	if (g_6a3420 == 0) {
		goto fold;
	}
	d1f8 = 0;
	d2_SetOverlayAnimation(0, 0);
	d2_DestroyHudOverlay();
	d2_UpdateViewportCenter(0x24087);
	dlg = d2_CreateScrollPerga();
	d2_CenterDialogWindows(dlg);
	if (g1f4 != 0) {
		d2_ReleaseOverlaySprite((unsigned char*) g1f4);
		g1f4 = 0;
	}
	d2_StartScreenFade(0, 0, g_1040494, d2_ScreenHeight, "BLACK", 0x1e, 10);
	d2_SetForm(dlg, 2);
	io_AppendText(0x7d);
	gm_PackGameTime((void*) (char*) gm_GameTime, stamp);
	d2_SetForm(dlg, 1);
	io_AppendText(0x2007);
	k = (((unsigned short)g_774970) & 0xffff) * 0x21c;
	runningTotal = *(int*) (k + 0x7f4e3c);
	c1fc = runningTotal - *(int*) (k + 0x7f4e38);
	if (runningTotal != 0) {
		io_AppendText(0x2008, runningTotal);
	}
	runningTotal = *(int*) ((((unsigned short)g_774970) & 0xffff) * 0x21c + 0x7f4e38);
	if (runningTotal != 0) {
		io_AppendText(0x2009, runningTotal);
	}
	runningTotal = c1fc;
	if (*(int*) (sel + 0x40) != 0) {
		io_AppendText(0x2014, *(int*) (sel + 0x40));
		b200 = *(int*) (sel + 0x40);
		runningTotal = c1fc - b200;
	}
	if (*(int*) (sel + 0x44) != 0) {
		io_AppendText(0x2016, *(int*) (sel + 0x44));
		runningTotal -= *(int*) (sel + 0x44);
		b200 += *(int*) (sel + 0x44);
	}
	if (*(int*) (sel + 0x48) != 0) {
		io_AppendText(0x201b, *(int*) (sel + 0x48));
		runningTotal -= *(int*) (sel + 0x48);
		b200 += *(int*) (sel + 0x48);
	}
	if (*(int*) (sel + 0x4c) != 0) {
		io_AppendText(0x201a, *(int*) (sel + 0x4c));
		runningTotal -= *(int*) (sel + 0x4c);
		b200 += *(int*) (sel + 0x4c);
	}
	if (*(int*) (sel + 0x54) != 0) {
		io_AppendText(0x2015, *(int*) (sel + 0x54));
		runningTotal -= *(int*) (sel + 0x54);
		b200 += *(int*) (sel + 0x54);
	}
	if (*(int*) (sel + 0x28) != 0) {
		io_AppendText(0x201c, *(int*) (sel + 0x28));
		runningTotal -= *(int*) (sel + 0x28);
		b200 += *(int*) (sel + 0x28);
	}
	if (*(int*) (sel + 0x14) != 0) {
		io_AppendText(0x200d, *(int*) (sel + 0x14));
		runningTotal += *(int*) (sel + 0x14);
		c1fc += *(int*) (sel + 0x14);
	}
	if (*(int*) (sel + 0x18) != 0) {
		io_AppendText(0x200c, *(int*) (sel + 0x18));
		runningTotal += *(int*) (sel + 0x18);
		c1fc += *(int*) (sel + 0x18);
	}
	if (*(int*) (sel + 0x1c) != 0) {
		io_AppendText(0x200b, *(int*) (sel + 0x1c));
		runningTotal += *(int*) (sel + 0x1c);
		c1fc += *(int*) (sel + 0x1c);
	}
	if (*(int*) (sel + 0x20) != 0) {
		io_AppendText(0x2010, *(int*) (sel + 0x20));
		runningTotal += *(int*) (sel + 0x20);
		c1fc += *(int*) (sel + 0x20);
	}
	if (*(int*) (sel + 0x50) != 0) {
		io_AppendText(0x201d, *(int*) (sel + 0x50));
		runningTotal -= *(int*) (sel + 0x50);
		b200 += *(int*) (sel + 0x50);
	}
	if (runningTotal == 0) {
		io_AppendText(0x201e);
	} else {
		io_AppendText(0x204c, runningTotal);
	}
	d2_SetForm(dlg, 3);
	*(int*) ((char*) g_77255c + 0x28c) = 0x55;
	io_AppendText(0x2005);
	d2_SetForm(dlg, 1);
	io_AppendText(0x68112c);
	ent = (char*) fcn_00503fe0(1, 6);
	while (ent != 0) {
		if (*(short*) (ent + 0x27) == (short) (((unsigned short)g_774970) & 0xffff) ||
		    *(short*) (ent + 0x25) == (short) (((unsigned short)g_774970) & 0xffff)) {
			b = *(unsigned char*) ent;
			kind = fcn_00504bd0((int) b);
			n = gm_CalcBuildingRoundBalance(ent, (int) (((unsigned short)g_774970) & 0xffff), info);
			if (n != 0 || (kind != 5 && kind != 6)) {
				c1fc += *(int*) ((char*) info + 0x44);
				e1ec += *(int*) ((char*) info + 0xc);
				b200 += *(int*) ((char*) info + 0x40);
				d1f8 += *(int*) ((char*) info + 0x50);
			}
		}
		ent = (char*) fcn_00503e80();
	}
	n = he_GetActiveKrediteByLender(((unsigned short)g_774970) & 0xffff, 0, 0xffff, v1d0);
	i = 0; k = 0;
	if (n > 0) {
		do {
			dbl = (double) *(int*) ((char*) (int) v1d0[i] + 0xc0) * 0.01
				* *(int*) ((char*) (int) v1d0[i] + 0xb4);
			c1fc = (int) (c1fc + dbl);
			k = (int) (k + dbl);
			d1f8 = (int) (d1f8 + dbl);
			i++;
		} while (i < n);
		if (k != 0) {
			io_AppendText(0x2048, k);
		}
	}
	k = (((unsigned short)g_774970) & 0xffff) * 0x21c;
	if (*(char*) (k + 0x7f4e06) != 0 || *(char*) (k + 0x7f4e09) != 0) {
		amt_ProcessPrivilegeIncome(((unsigned short)g_774970), 0, v1d0);
		k = (((unsigned short)g_774970) & 0xffff) * 0x21c;
		h1f0 = (-(*(char*) (k + 0x7f4ca9) != 0) & 0x28) + 0x253;
		b = *(unsigned char*) (k + 0x7f4e06);
		if (b != 0) {
			io_AppendText(0x2049, (int) b + h1f0, v1d0[1]);
		}
		b = *(unsigned char*) ((((unsigned short)g_774970) & 0xffff) * 0x21c + 0x7f4e09);
		if (b != 0) {
			io_AppendText(0x2049, (int) b + h1f0, v1d0[2]);
		}
		d1f8 += v1d0[1] + v1d0[2];
		c1fc += v1d0[1] + v1d0[2];
	}
	n = gm_CalcEntityTaxSlots(((unsigned short)g_774970), (int*)&revenue, 0);
	if (n != 0) {
		i = 0;
		do {

			if (revenue.names[i] == 0) {
				break;
			}
			io_AppendText(0x6a4340, (unsigned char) revenue.names[i] + 0x1f64,
				revenue.vals2[i], revenue.vals[i]);
			b200 += revenue.vals[i];
			d1f8 -= revenue.vals[i];
			f1e8 += revenue.vals[i];
			i++;

		} while (i < 6);
	}
	if (e1ec != 0) {
		io_AppendText(0x204a, e1ec);
	}
	n = he_GetActiveKrediteByBorrower(((unsigned short)g_774970) & 0xffff, 0, v1d0);
	runningTotal = 0;
	i = 0;
	if (n > 0) {
		do {
			dbl = (double) *(int*) ((char*) (int) v1d0[i] + 0xc0) * 0.01
				* *(int*) ((char*) (int) v1d0[i] + 0xb4);
			b200 = (int) (b200 + dbl);
			runningTotal = (int) (runningTotal + dbl);
			d1f8 = (int) (d1f8 - dbl);
			i++;
		} while (i < n);
	}
	if (b200 != 0 && runningTotal != 0) {
		io_AppendText(0x204b, runningTotal);
	}
	io_AppendText(0x204c, d1f8);
	c1fc -= b200;
	if (c1fc > 0) {
		io_AppendText(0x204d, c1fc);
	} else if (c1fc < 0) {
		io_AppendText(0x204e, c1fc);
	}
	n = fcn_0050d2a0((((unsigned short)g_774970) & 0xffff) * 0x21c + (int) (char*) g_7f4ca0);
	io_AppendText(0x2029, ((n - f1e8) - e1ec) - runningTotal);
	d2_ToggleActionPopupBar(0xffff);
	d2_ClearSurface(g_77250c);
	d2_SetBackdropResource(0x79d);
	g_774978 = 1;
	g_1040488 = 0;
	g_1040480 = g_1040494;
	g_1040484 = 0;
	g_104048c = d2_ScreenHeight;
	d2_SetForm(dlg, 1);
	k = d2_CurrentWindowId;
	d2_SetForm(dlg, 2);
	io_AppendText(0x7d);
	d2_AddWindowScrollButtons(-1, -1, d2_CurrentWindowId, k, 0x767);
	*(int*) (k * 0x3cc + 0x10161b4) = 0x18;
	sb_PlayVoice(0, "RollenKurz_s_01", 1, 0x3f, 0x7f, 0, 0);
	i = main_RunFrameLoop((int) d2_RunRoundSummaryDialog, 0x24087);
	while (i != 0) {
		d2_UpdateScrollPerga();
		if (g_100f1dc == 2 || g_14cf950 == 0x1c) {
			g_774654 = 1;
		}
		i = main_RunFrameLoop((int) d2_RunRoundSummaryDialog, 0x24087);
	}
	d2_DestroyScrollPerga();
fold:
	*(int*) (sel + 0x2c) += *(int*) (sel + 0x14) + *(int*) (sel + 0x18);
	*(int*) (sel + 0x14) = 0;
	*(int*) (sel + 0x30) += *(int*) (sel + 0x1c);
	*(int*) (sel + 0x18) = 0;
	*(int*) (sel + 0x34) += *(int*) (sel + 0x20);
	*(int*) (sel + 0x1c) = 0;
	*(int*) (sel + 0x38) += *(int*) (sel + 0x24);
	*(int*) (sel + 0x20) = 0;
	*(int*) (sel + 0x24) = 0;
	*(int*) (sel + 0x28) = 0;
	*(int*) (sel + 0x40) = 0;
	*(int*) (sel + 0x44) = 0;
	*(int*) (sel + 0x48) = 0;
	*(int*) (sel + 0x4c) = 0;
	*(int*) (sel + 0x50) = 0;
	*(int*) (sel + 0x54) = 0;
	if (g1f4 != 0) {
		d2_ReleaseOverlaySprite((unsigned char*) g1f4);
		g1f4 = 0;
	}
	n = gm_CheckAndCollectEntityDebt((char*) ((((unsigned short)g_774970) & 0xffff) * 0x21c + (int) (char*) g_7f4ca0),
		-(f1e8 + e1ec + runningTotal));
	if (n != 0) {
		memset(panel, 0, 0x114);
		*(unsigned char*) (panel + 8) = 9;
		*(unsigned char*) (panel + 0x26) = 0x60;
		*(int*) (panel + 0x14) = -1;
		*(unsigned char*) (panel + 0x30) = 1;
		*(int*) (panel + 0xc) = *(int*) ((((unsigned short)g_774970) & 0xffff) * 0x21c + 0x7f4ca4);
		*(int*) (panel + 0x34) = *(int*) (panel + 0xc);
		if (g1f4 != 0) {
			d2_ReleaseOverlaySprite((unsigned char*) g1f4);
		}
		cut_ExecuteCutscene(panel);
		if (g_774968 != 0) {
			gm_ResetDynastySlot(((unsigned short)g_774970) & 0xffff);
		}
		g_774968 = 0;
	}
}
