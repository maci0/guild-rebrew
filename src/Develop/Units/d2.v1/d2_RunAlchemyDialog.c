extern int d2_CurrentWindowId;
extern int d2_DialogButtonAction;
extern int io_RightButtonReleased;
extern int d2_DialogCloseRequested;
#include <string.h>
#include "Develop/Units/d2.v1/d2_gui.h"

extern unsigned char gm_ActiveTownIndex;
int __cdecl gm_FindOrAllocHeadSet(int, int);
void * __cdecl ahm_GetDrawSlot(int);
int __cdecl ahm_CalcRecipeScore(void *);
void * __cdecl d2_LoadForm(int, int, void *);
void __cdecl d2_SetOverlayAnimation(int, int);
void __cdecl d2_CenterDialogWindows(void *);
void __cdecl d2_SetForm(void *, int);
void __cdecl d2_InitWindowBounds(int);
void __cdecl io_AppendText(int);
int __cdecl d2_CreateRadioGroup(int);
int __cdecl d2_AddElementToWindow(int, int, int, int);
int __cdecl d2_EqualizeWindowButtonWidths(int, int, char *, int);
void __cdecl d2_AddToRadioGroup(int, int);
int __cdecl io_FormatTextBuffer(char *, int, ...);
void __cdecl d2_SetElementFont(int, int);
void __cdecl d2_DrawSegmentedBar(int, int, int, int);
void __cdecl d2_CreateButtonRow(int, int, void *, int, int, int);
void __cdecl d2_SetElementEnabled(void *, int);
int __cdecl main_RunFrameLoop(int, int);
void __cdecl d2_ClearRadioGroup(int);
void __cdecl d2_DestroyForm(void *);
void __cdecl d3_EndCameraAndUiMode(void);
int __cdecl d2_DispatchAlchemyOrder(int, void *, int);
void __cdecl d2_ShowGreenMessageBox(void *, char *, int);

/* ADDRESS: GOLDTL 0x5848b0 */
/* ADDRESS: GOLDDE 0x0056a570 */
void __cdecl d2_RunAlchemyDialog(int a0)
{
	char msg[992];
	char buf[256];
	unsigned int pt[2];
	void *rec[3];
	int val[3];
	int item[3];
	int count;
	int i;
	int off;
	int y;
	int id;
	int idx;
	int keep;
	int last;
	int base;
	void *r;
	void *w;
	unsigned int exp;
	int *fields;
	int *ent;
	char *rp;

	memset(rec, 0, sizeof(rec));
	count = 0;
	pt[0] = (unsigned int)gm_FindOrAllocHeadSet(0, 0x52);
	for (i = 0; i < 3; i++) {
		r = ahm_GetDrawSlot(i);
		if (*(int *)r != 0) {
			rec[count] = r;
			val[count] = ahm_CalcRecipeScore(r);
			count++;
		}
	}
	if (count == 0) {
		io_FormatTextBuffer(msg, 0x404a, 0x868060 + gm_ActiveTownIndex * 0x2f4);
		d2_ShowGreenMessageBox(*(void **)0x14b5404, msg, 0);
		d3_EndCameraAndUiMode();
		return;
	}
	w = d2_LoadForm(0, 0, (void *)0x6a9380);
	d2_SetOverlayAnimation(0, 0);
	d2_CenterDialogWindows(w);
	d2_SetForm(w, 0);
	d2_InitWindowBounds(d2_CurrentWindowId);
	d2_SetForm(w, 1);
	d2_SetForm(w, 2);
	keep = d2_CurrentWindowId;
	d2_SetForm(w, 3);
	last = d2_CurrentWindowId;
	d2_SetForm(w, 1);
	io_AppendText(0x4039);
	d2_SetForm(w, 2);
	idx = d2_CreateRadioGroup(0);
	y = 0x31;
	i = 0;
	off = 0;
	if (count > 0) {
		do {
			item[i] = d2_AddElementToWindow(5, y - 0x19, 0x6c7, keep);
			fields = (int *)((char *)pt[0] + 0x34);
			item[i] = d2_AddElementToWindow(7, y - 0x17, fields[i % 2] + 0x639, keep);
			ent = (int *)((unsigned int)d2_Controls + item[i] * 0x2f4);
			ent[0x5c / 4] = 1;
			d2_AddToRadioGroup(idx, item[i]);
			r = rec[off / 4];
			rp = (char *)r;
			io_FormatTextBuffer(buf, 0x68b3f8, *(unsigned int *)(0x14b5908 + *(int *)(rp + 0x10) * 4), *(unsigned int *)(0x14b596c + *(int *)(rp + 0x14) * 4));
			id = d2_EqualizeWindowButtonWidths(0, y - 0x30, buf, keep);
			base = *(int *)(0x1015f4c + keep * 0x3cc);
			ent = (int *)((unsigned int)d2_Controls + id * 0x2f4);
			ent[0x18 / 4] = base;
			ent[0x6c / 4] = 1;
			d2_SetElementFont(id, 0x54);
			io_FormatTextBuffer(buf, 0x679060, *(unsigned int *)0x14b58e8);
			id = d2_EqualizeWindowButtonWidths(0x50, y - 0x1a, buf, keep);
			ent = (int *)((unsigned int)d2_Controls + id * 0x2f4);
			ent[0x18 / 4] = *(int *)(0x1015f4c + keep * 0x3cc) - 0x50;
			d2_SetElementFont(id, 0x54);
			d2_DrawSegmentedBar(0x8c, y - 0x1a, *(unsigned char *)(rp + 4), 0x4df);
			io_FormatTextBuffer(buf, 0x679060, *(unsigned int *)0x14b58ec);
			id = d2_EqualizeWindowButtonWidths(0x50, y - 0xd, buf, keep);
			ent = (int *)((unsigned int)d2_Controls + id * 0x2f4);
			ent[0x18 / 4] = *(int *)(0x1015f4c + keep * 0x3cc) - 0x50;
			d2_SetElementFont(id, 0x54);
			d2_DrawSegmentedBar(0x8c, y - 0xd, *(unsigned char *)(rp + 5), 0x4df);
			io_FormatTextBuffer(buf, 0x679060, *(unsigned int *)0x14b58f0);
			id = d2_EqualizeWindowButtonWidths(0x50, y, buf, keep);
			ent = (int *)((unsigned int)d2_Controls + id * 0x2f4);
			ent[0x18 / 4] = *(int *)(0x1015f4c + keep * 0x3cc) - 0x50;
			d2_SetElementFont(id, 0x54);
			d2_DrawSegmentedBar(0x8c, y, *(unsigned char *)(rp + 6), 0x4df);
			io_FormatTextBuffer(buf, 0x679060, *(unsigned int *)0x14b58f4);
			id = d2_EqualizeWindowButtonWidths(0x50, y + 0xd, buf, keep);
			ent = (int *)((unsigned int)d2_Controls + id * 0x2f4);
			ent[0x18 / 4] = *(int *)(0x1015f4c + keep * 0x3cc) - 0x50;
			d2_SetElementFont(id, 0x54);
			d2_DrawSegmentedBar(0x8c, y + 0xd, *(unsigned char *)(rp + 7), 0x4df);
			io_FormatTextBuffer(buf, 0x403f, *(unsigned char *)(rp + 8));
			id = d2_EqualizeWindowButtonWidths(0xfa, y - 0x1b, buf, keep);
			ent = (int *)((unsigned int)d2_Controls + id * 0x2f4);
			ent[0x18 / 4] = *(int *)(0x1015f4c + keep * 0x3cc) - 0xfa;
			io_FormatTextBuffer(buf, 0x4040, ahm_CalcRecipeScore(r));
			id = d2_EqualizeWindowButtonWidths(0xfa, y - 0xe, buf, keep);
			ent = (int *)((unsigned int)d2_Controls + id * 0x2f4);
			ent[0x18 / 4] = *(int *)(0x1015f4c + keep * 0x3cc) - 0xfa;
			io_FormatTextBuffer(buf, 0x4041, *(int *)(rp + 0xc) * 2 + 0x9a8);
			id = d2_EqualizeWindowButtonWidths(0xfa, y - 1, buf, keep);
			ent = (int *)((unsigned int)d2_Controls + id * 0x2f4);
			ent[0x18 / 4] = *(int *)(0x1015f4c + keep * 0x3cc) - 0xfa;
			off += 4;
			y += 0x64;
			i++;
		} while (i < count);
	}
	d2_SetForm(w, 3);
	d2_CreateButtonRow(last, 0, pt, 2, *(int *)0x14b5428, *(int *)0x14b542c);
	d2_DialogButtonAction = -1;
	do {
		r = (void *)pt[0];
		exp = *(unsigned int *)(0x102cbc8 + idx * 0x8c);
		d2_SetElementEnabled(r, (exp != 0xffffffff) && (i != 0));
		if (io_RightButtonReleased) {
			d2_DialogCloseRequested = 1;
		} else if (d2_DialogButtonAction != -1) {
			if (*(unsigned int *)0x67d370 == pt[0]) {
				for (id = 0; id < 3; id++) {
					if (exp == (unsigned int)id) {
						if (d2_DispatchAlchemyOrder(a0, rec[id], val[id])) {
							d2_DialogCloseRequested = 1;
						}
					}
				}
			} else if (*(unsigned int *)0x67d370 == pt[1]) {
				d2_DialogCloseRequested = 1;
			}
		}
	} while (main_RunFrameLoop(0x5848b0, 0x677c7));
	d2_ClearRadioGroup(idx);
	d2_DestroyForm(w);
	d3_EndCameraAndUiMode();
}
