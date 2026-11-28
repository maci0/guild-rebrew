/* SIZE 0x38 */
typedef struct D2_AMT_TARGET_ROW {
	char* ent;		/* 0x00 */
	int h1;			/* 0x04 */
	int h2;			/* 0x08 */
	int text;		/* 0x0c */
	int pad10;		/* 0x10 */
	int pad14;		/* 0x14 */
	int pad18;		/* 0x18 */
	int text1;		/* 0x1c */
	int text2;		/* 0x20 */
	int text3;		/* 0x24 */
	int text4;		/* 0x28 */
	int pad2c[3];		/* 0x2c */
} D2_AMT_TARGET_ROW;

extern int d2_CurrentWindowId;
extern int d2_CurrentElementId;
#include "Develop/Units/d2.v1/client_dialog_state.h"
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int d2_DialogButtonAction;
extern int g_14ce8d8;
extern int io_RightButtonReleased;
extern int g_14ce8e8;
extern float flt_100_0;
extern float g_664e88;
extern float g_6660d4;

int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_ClearWindowChildren(int, int);
int __cdecl amt_FindOfficeSlotsByKind(int, int, char*);
int __cdecl amt_CollectOfficeGroup7(int, int, char*);
int __cdecl gm_LookupEntityRecordById(int);
char* __cdecl he_StartHandlungSearch(int, int, int);
char* __cdecl he_fn_Handlung(void);
int __cdecl CountMatchingStraftatEntries(int, unsigned short);
float __cdecl gm_GetEntityHealth(char*);
int __cdecl d2_DrawOfficeCandidateGrid(int, int, int, int, int, short*);
int __cdecl d2_DrawPersonCardGrid(int, int, int, int, int, int);
void __cdecl d2_SetFormVisibility(int, int);
int __cdecl main_RunFrameLoop(int, int);
void __cdecl d2_DestroyForm(int);

/* ADDRESS: GOLDTL 0x005cadc0 */
/* ADDRESS: GOLDDE 0x005ac850 */
char* __cdecl d2_RunOfficeListDialog(int officeKind, int arg1, int titleId, int fallbackTitleId, int (__cdecl* cb)(char*, int))
{
	D2_AMT_TARGET_ROW rec[8];
	short* p;
	char* res;
	int dlg;
	char* ent;
	char* q;
	int count;
	int again;
	int sel;
	int i;
	int j;
	float f;

	p = 0;
	res = 0;
	count = 0;
	sel = 0;
	dlg = d2_LoadForm(0, 0, "special\\amt2");
	d2_CenterDialogWindows(dlg);
	again = 1;
	for (;;) {
		if (again) {
			d2_SetForm(dlg, 2);
			io_AppendText(0x6811b0);
			if (sel)
				io_AppendText(0xa0, *(unsigned short*) p);
			else
				io_AppendText(0x6a9ac4, officeKind + 0x12b2);
			d2_SetForm(dlg, 3);
			io_AppendText(0x6811b0);
			if (titleId || fallbackTitleId)
				io_AppendText(titleId ? titleId : fallbackTitleId);
			d2_SetForm(dlg, 1);
			d2_ClearWindowChildren(d2_CurrentWindowId, 1);
			for (i = 0; i < 8; i++) {
				rec[i].ent = 0;
				rec[i].h1 = -1;
				rec[i].text = 0;
			}
			if (officeKind == 0) {
				for (count = 0, q = (char*) 0x7f4ca2; (int) q < 0x85a0a2 && count < 8; q += 0x21c) {
					if (*q == 6 || *q == 7 || *q == 5) {
						rec[count].ent = q - 2;
						count++;
					}
				}
			} else if (1 <= officeKind && officeKind <= 6) {
				char buf[0x90];
				count = amt_FindOfficeSlotsByKind(officeKind, 6, buf);
				if (count > 0) {
					for (i = 0; i < count; i++) {
						rec[i].ent = (char*) gm_LookupEntityRecordById(*(int*) (buf + i * 0x18 + 4));
						rec[i].text = *(unsigned char*) (buf + i * 0x18 + 8);
					}
				}
			} else if (officeKind == 7) {
				char buf[0x90];
				count = amt_CollectOfficeGroup7(0, 6, buf);
				if (count > 0) {
					for (i = 0; i < count; i++) {
						rec[i].ent = (char*) gm_LookupEntityRecordById(*(int*) (buf + i * 0x18 + 4));
						rec[i].text = *(unsigned char*) (buf + i * 0x18 + 8);
					}
				}
			} else if (officeKind == 8) {
				char buf[0x78];
				count = amt_FindOfficeSlotsByKind(officeKind, 5, buf);
				if (count > 0) {
					for (i = 0; i < count; i++) {
						rec[i].ent = (char*) gm_LookupEntityRecordById(*(int*) (buf + i * 0x18 + 4));
						rec[i].text = *(unsigned char*) (buf + i * 0x18 + 8);
					}
				}
			} else {
				goto fail;
			}
			if (count == 0)
				goto fail;
			for (i = 0; i < count; i++) {
				ent = rec[i].ent;
				if (!ent)
					continue;
				rec[i].text2 = 0;
				rec[i].text1 = *(unsigned char*) (ent + 0xc) != 0 ? 0x6c9 : 0x6ca;
				if ((*(unsigned char*) (gm_LocalPlayerSlot * 0x21c + 0x7f4ca9) != *(unsigned char*) (ent + 9))
				    && (*(unsigned int*) (ent + 0x1c8) & 0x800000)) {
					j = 0;
					for (j = he_StartHandlungSearch(1, 0, 0x6f); j; j = he_fn_Handlung()) {
						if ((*(int*) (j + 0xac) == *(int*) (gm_LocalPlayerSlot * 0x21c + 0x7f4ca4))
						    && (*(int*) (ent + 4) == *(int*) (j + 0xb0))) {
							rec[i].text2 = 0x6cc;
							break;
						}
					}
				}
				rec[i].text3 = 0;
				if (CountMatchingStraftatEntries(*(int*) (ent + 4), gm_LocalPlayerSlot) > 0) {
					rec[i].text3 = 0x6cd;
				} else {
					for (j = he_StartHandlungSearch(1, 0, 0x18); j; j = he_fn_Handlung()) {
						if ((*(unsigned short*) (j + 8) == gm_LocalPlayerSlot) && (*(int*) (ent + 4) == *(int*) (j + 0xc4))) {
							rec[i].text3 = 0x6ce;
							break;
						}
					}
				}
				rec[i].text4 = 0;
				for (j = he_StartHandlungSearch(1, 0, 0x45); j; j = he_fn_Handlung()) {
					if ((*(int*) (j + 0xac) == *(int*) (gm_LocalPlayerSlot * 0x21c + 0x7f4ca4))
					    && (*(int*) (ent + 4) == *(int*) (j + 0xb0))) {
						rec[i].text4 = 0x6cb;
						break;
					}
				}
				if (!rec[i].text4) {
					f = gm_GetEntityHealth(ent);
					if (f < flt_100_0)
						rec[i].text4 = 0x6d2;
					else if (f < g_664e88)
						rec[i].text4 = 0x6d1;
					else if (f < g_6660d4)
						rec[i].text4 = 0x6d0;
					else
						rec[i].text4 = 0x6cf;
				}
			}
			if (officeKind && (officeKind != 7))
				d2_DrawOfficeCandidateGrid(d2_CurrentWindowId, officeKind, arg1, count, (int) rec,
				    p ? p : (short*) (gm_LocalPlayerSlot * 0x21c + 0x7f4ca0));
			else
				d2_DrawPersonCardGrid(d2_CurrentWindowId, officeKind, arg1, count, (int) rec,
				    (int) (p ? p : (short*) (gm_LocalPlayerSlot * 0x21c + 0x7f4ca0)));
			again = 0;
		}
		if (io_RightButtonReleased) {
			d2_DialogCloseRequested = 1;
			goto loopend;
		}
		if (!(g_14ce8e8)) {
			if (sel == 0)
				goto select;
			sel = 0;
			p = 0;
			again = 1;
			goto loopend;
		} else {
			if (sel == 0) {
				res = 0;
				p = 0;
				j = 0;
				if (count > 0) {
					while (j < count) {
						if (rec[j].h2 == d2_CurrentElementId)
							break;
						j++;
					}
					if ((j > -1) && (j < count)) {
						ent = rec[j].ent;
						if (ent) {
							p = 0;
							again = 1;
							if (*(unsigned short*) ent != 0xffff) {
								p = (short*) ent;
								sel = 1;
							}
						}
					}
				}
				goto loopend;
			}
		}
select:
		if (g_14ce8d8 && (d2_DialogButtonAction != -1)) {
			res = 0;
			if (count > 0) {
				j = 0;
				while (j < count) {
					if (rec[j].h1 == d2_CurrentElementId)
						break;
					j++;
				}
				if ((j > -1) && (j < count)) {
					ent = rec[j].ent;
					if (*(unsigned short*) ent == 0xffff) {
						sel = 0;
						p = 0;
					} else if (cb) {
						d2_SetFormVisibility(dlg, 0);
						res = cb(ent, 0) ? ent : 0;
						d2_SetFormVisibility(dlg, 1);
					} else {
						d2_DialogCloseRequested = 1;
						res = ent;
					}
				}
			}
			again = 1;
		}
loopend:
		if (!main_RunFrameLoop((int) d2_RunOfficeListDialog, 0x657c7)) {
			d2_DestroyForm(dlg);
			return res;
		}
	}
fail:
	d2_DialogCloseRequested = 1;
	main_RunFrameLoop((int) d2_RunOfficeListDialog, 0x657c7);
	d2_DestroyForm(dlg);
	return 0;
}
