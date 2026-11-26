extern int d2_CurrentWindowId;
#include "Develop/DieGildeAddOn/game/game_data.h"
#include "client_dialog_state.h"
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int g_100f1dc;
extern float g_662cf8;
extern float g_664e88;
extern float g_6660d4;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
int __cdecl d2_ClearWindowChildren(int, int);
int __cdecl amt_FindOfficeSlotsByKind(int, int, char*);
int __cdecl amt_CollectOfficeGroup7(int, int, char*);
int __cdecl gm_LookupEntityRecordById(int);
int __cdecl he_StartHandlungSearch(int, int, ...);
int __cdecl he_fn_Handlung(void);
int __cdecl CountMatchingStraftatEntries(int, unsigned short);
float __cdecl gm_GetEntityHealth(char*);
int __cdecl fcn_005c9f10(int, int, int, int, int, short*);
int __cdecl fcn_005c99a0(int, int, int, int, int, int);
void __cdecl fcn_00472640(int, int);
void __cdecl fcn_00471af0(int, int);
void __cdecl d2_ShowAmtInfo(int, int);
int __cdecl main_RunFrameLoop(int, int);
void __cdecl fcn_00471e30(int);

typedef struct {
	int ent;
	int h1;
	int h2;
	int text;
	int pad10;
	int pad14;
	int pad18;
	int text1;
	int text2;
	int text3;
	int text4;
	int pad2c;
	int pad30;
	int pad34;
} Rec_5cd810;

/* ADDRESS: GOLDTL 0x005cd810 */
void __cdecl fcn_005cd810(int office)
{
	char src1[0x90];
	char src2[0x90];
	Rec_5cd810 rec[8];
	short* sel2;
	int sel;
	int dlg;
	char* ent;
	char* p;
	float f;
	int count;
	int again;
	int i;
	int j;

	count = 0;
	sel2 = 0;
	dlg = fcn_00470820(0, 0, "special\\amt2");
	d2_CenterDialogWindows(dlg);
	sel = 0;
	again = 1;
	for (;;) {
		if (again) {
			d2_SetForm(dlg, 2);
			io_AppendText(0x6811b0);
			if (sel)
				io_AppendText(0xa0, (unsigned short) *sel2);
			else
				io_AppendText(0x6a9ac4, office + 0x12b2);
			d2_SetForm(dlg, 3);
			io_AppendText(0x6811b0);
			d2_SetForm(dlg, 1);
			d2_ClearWindowChildren(d2_CurrentWindowId, 1);
			for (i = 0; i < 8; i++) {
				rec[i].ent = 0;
				rec[i].h1 = -1;
				rec[i].text = 0;
			}
			if (((0 < office) && (office < 7)) || (office == 8)) {
				count = amt_FindOfficeSlotsByKind(office, 6, src1);
				for (i = 0; i < count; i++) {
					rec[i].ent = gm_LookupEntityRecordById(*(int*) (src1 + i * 0x18 + 4));
					rec[i].text = *(unsigned char*) (src1 + i * 0x18 + 8);
				}
			} else if (office == 7) {
				count = amt_CollectOfficeGroup7(0, 6, src2);
				for (i = 0; i < count; i++) {
					rec[i].ent = gm_LookupEntityRecordById(*(int*) (src2 + i * 0x18 + 4));
					rec[i].text = *(unsigned char*) (src2 + i * 0x18 + 8);
				}
			} else {
				return;
			}
			if (!count)
				return;
			for (i = 0; i < count; i++) {
				ent = (char*) rec[i].ent;
				if (!ent)
					continue;
				rec[i].text2 = 0;
				rec[i].text1 = *(char*) (ent + 0xc) ? 0x6c9 : 0x6ca;
				if ((*(unsigned char*) (g_774970 * 0x21c + 0x7f4ca9) != *(unsigned char*) (ent + 9)) && (*(unsigned int*) (ent + 0x1c8) & 0x800000)) {
					j = he_StartHandlungSearch(1, 0, 0x6f);
					while (j) {
						if ((*(int*) (j + 0xac) == *(int*) (g_774970 * 0x21c + 0x7f4ca4)) && (*(int*) (ent + 4) == *(int*) (j + 0xb0))) {
							rec[i].text2 = 0x6cc;
							break;
						}
						j = he_fn_Handlung();
					}
				}
				rec[i].text3 = 0;
				if (CountMatchingStraftatEntries(*(int*) (ent + 4), g_774970) > 0) {
					rec[i].text3 = 0x6cd;
				} else {
					j = he_StartHandlungSearch(1, 0, 0x18);
					while (j) {
						if ((*(unsigned short*) (j + 8) == g_774970) && (*(int*) (ent + 4) == *(int*) (j + 0xc4))) {
							rec[i].text3 = 0x6ce;
							break;
						}
						j = he_fn_Handlung();
					}
				}
				rec[i].text4 = 0;
				j = he_StartHandlungSearch(1, 0, 0x45);
				while (j) {
					if ((*(int*) (j + 0xac) == *(int*) (g_774970 * 0x21c + 0x7f4ca4)) && (*(int*) (ent + 4) == *(int*) (j + 0xb0))) {
						rec[i].text4 = 0x6cb;
						break;
					}
					j = he_fn_Handlung();
				}
				if (!rec[i].text4) {
					f = gm_GetEntityHealth(ent);
					if (f < g_662cf8)
						rec[i].text4 = 0x6d2;
					else if (f < g_664e88)
						rec[i].text4 = 0x6d1;
					else if (f < g_6660d4)
						rec[i].text4 = 0x6d0;
					else
						rec[i].text4 = 0x6cf;
				}
			}
			if (office && (office != 7)) {
				p = (char*) sel2;
				if (!p)
					p = (char*) (g_774970 * 0x21c + 0x7f4ca0);
				fcn_005c9f10(d2_CurrentWindowId, office, 0, count, (int) rec, (short*) p);
			} else {
				p = (char*) sel2;
				if (!p)
					p = (char*) (g_774970 * 0x21c + 0x7f4ca0);
				fcn_005c99a0(d2_CurrentWindowId, office, 0, count, (int) rec, (int) p);
			}
			for (i = 0; i < count; i++) {
				fcn_00472640(rec[i].h1, 1);
				if (rec[i].h2 != -1)
					fcn_00472640(rec[i].h2, 1);
			}
			again = 0;
		}
		if (g_14ce8e0) {
			g_774654 = 1;
		} else {
			if (g_14ce8e8) {
				if (!sel) {
					sel2 = 0;
					for (i = 0; i < count; i++) {
						if (rec[i].h2 == d2_CurrentElementId)
							break;
					}
					if ((i > -1) && (i < count)) {
						ent = (char*) rec[i].ent;
						if (ent) {
							sel2 = 0;
							again = 1;
							if (*(unsigned short*) ent != 0xffff) {
								sel2 = (short*) ent;
								sel = 1;
							}
						}
					}
					goto loopend;
				}
			} else if (sel) {
				sel = 0;
				sel2 = 0;
				again = 1;
				goto loopend;
			}
			if (g_14ce8d8 && (g_100f1dc != -1)) {
				for (i = 0; i < count; i++) {
					if (rec[i].h1 == d2_CurrentElementId)
						break;
				}
				if ((i > -1) && (i < count)) {
					ent = (char*) rec[i].ent;
					if (!ent || (*(unsigned short*) ent == 0xffff)) {
						sel2 = 0;
						sel = 0;
					}
					fcn_00471af0(dlg, 0);
					d2_ShowAmtInfo(rec[i].text, (int) ent);
					fcn_00471af0(dlg, 1);
				}
				again = 1;
			}
		}
loopend:
		if (!main_RunFrameLoop((int) fcn_005cd810, 0x657c7)) {
			fcn_00471e30(dlg);
			return;
		}
	}
}
