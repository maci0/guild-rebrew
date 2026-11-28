extern int d2_DialogButtonAction, io_RightButtonReleased, d2_CurrentElementId;
#include "Develop/Units/d2.v1/client_dialog_state.h"
/* Runs the town trade/settlement dialog: opens the window, collects the shop
   list, draws the goods rows and processes input until the player closes it. */
#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char* lpGebaeudePROT;
typedef struct { unsigned char kind; unsigned char unknown01[0x24c]; } BUILDING_ROW;
#include "Develop/DieGildeAddOn/game/building_prototype.h"

int __cdecl d2_CheckOwnerBlocked(void*);
void __cdecl d2_DispatchTutorialInput(int, int, int, int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterDialogWindows(int);
void __cdecl d2_InitPlayerBar(void*, unsigned int);
void __cdecl d2_SetForm(int, int);
int __cdecl io_AppendText(int, ...);
void __cdecl d2_ResetBuildingUiSlots(void);
void __cdecl d2_DrawPanelFrame(int, int, int);
int __cdecl d2_CreateWindowScrollbar(int, int, int, int, int, int*, int*, int*);
int __cdecl d2_GetFormWindow(int, int);
void __cdecl d2_SetOverlayAnimation(int, int);
int __cdecl gm_QueryEntities(int, int, int, ...);
int __cdecl gm_eval_SlotVoll(int, int, int);
int __cdecl he_StartHandlungSearch(int, int, int, int, int);
int __cdecl he_fn_Handlung(void);
int __cdecl d2_DispatchTutorialEvent(int, void*, int, unsigned int);
int __cdecl cm_SendCopyEntityData(void*);
int __cdecl cm_GetCommandStatus(int);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl cm_GetCommandResult(int);
void __cdecl d3snd_PlayWorkerOrderVoice(void);
void __cdecl he_AssignActionSlot(void*, int, int, int);
void __cdecl d2_ShowModalMessageBox(int, int);
int __cdecl d2_CanCloseWindowDuringTutorial(void);
void __cdecl d3_EndCameraAndUiMode(void);
int __cdecl gm_NextEntityQueryMatch(void);
int __cdecl gm_GetMsgField(int, int);
void __cdecl fcn_00657a73(int, int*, int);
void __cdecl d2_SetLabelText(int, int*);
void __cdecl d2_RenderProduktionStockRows(int, int, int, int, int);
void __cdecl d2_SyncWareProduktionSlotGrid(void*, int);
void __cdecl d2_RefreshWorkshopInventoryGrids(int, int, int, void*);
void __cdecl d2_DestroyForm(int);
void __cdecl d2_RestoreHudAfterDialog(void);

/* ADDRESS: GOLDTL 0x005944d0 */
/* ADDRESS: GOLDDE 0x00579f90 */
unsigned int __cdecl d2_RunProduktionDialog(unsigned char* building)
{
	unsigned char* p;
	int window;
	int saved;
	int item;
	int entry;
	int count;
	int idx;
	int limit;
	int i;
	int n;
	int row; int rowsLeft;
	unsigned int id;
	unsigned int v33;
	unsigned int v34;
	unsigned int v37;
	unsigned int v38;
	unsigned int v39;
	int listControl;
	int rect1;
	int rect2;
	int list[10];
	char tmpl[0xf8];
	unsigned short v3;

	p = building;
	idx = 1;
	item = d2_CheckOwnerBlocked(building);
	if (item) {
		return 0;
	}
	d2_DispatchTutorialInput(0x1f, 0, 0, 0);
	window = d2_LoadForm(0, 0, (char*) 0x6aa148);
	saved = window;
	d2_CenterDialogWindows(window);
	if (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*p].category == 0x1e) {
		d2_InitPlayerBar(p, 2);
	} else {
		d2_InitPlayerBar(p, 0);
	}
	d2_SetForm(window, 3);
	io_AppendText(0xb7);
	d2_ResetBuildingUiSlots();
	count = 0;
	d2_SetForm(window, 0);
	id = 0x70b;
	switch (((BUILDING_PROTOTYPE *)lpGebaeudePROT)[*p].category) {
	case 0x13:
	case 0x04:
	case 0x10:
		id = 0x72f;
		break;
	case 0x08:
	case 0x0e:
		id = 0x70f;
		break;
	case 0x06:
		id = 0x713;
		break;
	case 0x16:
		id = 0x717;
		break;
	case 0x0d:
	case 0x0c:
	case 0x0b:
		id = 0x717;
		break;
	}
	d2_DrawPanelFrame(d2_CurrentWindowId, id, 0x742);
	d2_CreateWindowScrollbar(0x270, 0x15e, d2_CurrentWindowId,
	             d2_GetFormWindow(window, 2), 0x78, &rect2, &rect1, &listControl);
	*(unsigned int*) ((int) d2_Controls + 0x84 + listControl * 0x2f4) = 0x54;
	d2_SetOverlayAnimation(0, 0);
	while (1) {
		int any;
		int* r;

		d2_SetForm(window, 2);
		limit = gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0xff);
		if (!limit) {
			return 0;
		}
		entry = gm_QueryEntities(*(int*) (p + 0x5d), 2, 6, 0, 0x2a);
		if (!entry) {
			return 0;
		}
		if (d2_DialogButtonAction != -1 && g_100f884 == window) {
			any = 0;
			r = (int*) 0x7e30e0;
			do {
				if ((int) r >= 0x7e35e0 || r[-4] == 0xffff) {
					break;
				}
				if (*r) {
					any = 1;
				}
				r += 10;
			} while (!any);
			if (1 <= count) {
				row = 0;
				rowsLeft = count;
				do {
					if (d2_CurrentElementId == *(int*) (row + 0x779194)) {
						if (!(any)) {
							int* r2;

							r2 = (int*) 0x7e30d0;
							do {
								int base;
								unsigned char* obj;

								if (*r2 == 0xffff) {
									break;
								}
								base = *r2 * 0x21c;
								obj = *(unsigned char**) (base + 0x7f4e1c);
								if (obj && *obj == 0x04 &&
								    *(int*) (obj + 0x10) == *(int*) (p + 1) &&
								    !(*(unsigned int*) (base + 0x7f4e68) & 0x800) &&
								    *(unsigned short*) (obj + 0xac) ==
								        *(unsigned int*) (row + 0x779160)) {
									*(unsigned char*) (base + 0x7f4e28) = 1;
								}
								r2 += 10;
							} while ((int) r2 < 0x7e35d0);
						} else {
							int ok;
							int rec;
							int handle;

							ok = 1;
							handle = *(int*) (row + 0x779160);
							rec = (int) lpObjektePROT + handle * 0x40;
							v3 = *(unsigned short*) (handle + 0x36 + rec);
							if (!(gm_eval_SlotVoll(entry, handle, v3))) {
								unsigned char kind;

								kind = *(unsigned char*) (handle + rec);
								if (kind != '%' && kind != 0x17) {
									d2_ShowModalMessageBox(*(int*) 0x14a561c, 0);
								} else {
									d2_ShowModalMessageBox(*(int*) 0x14a5618, 0);
								}
							} else {
								int k;
								unsigned short* q;

								k = 0;
								q = (unsigned short*) (handle + rec + 0x2e);
								do {
									unsigned short val;

									val = *q;
									if (!val) {
										break;
									}
									if (val != 0xffff) {
										int got;

										got = gm_QueryEntities(*(int*) (entry + 0x14), 1, 0, val);
										if (!got ||
										    *(int*) (got + 0xe) < (int) q[-4]) {
											ok = 0;
										}
									}
									k++;
									q++;
								} while (k < 4);
								if (!(ok)) {
									d2_ShowModalMessageBox(*(int*) 0x14a5620, 0);
								} else {
									int found;

									found = he_StartHandlungSearch(2, 0, 4, 3, *(int*) (p + 1));
									while (found) {
										if (*(unsigned short*) (found + 0xac) ==
										    *(unsigned int*) (row + 0x779160)) {
											goto found_row;
										}
										found = he_fn_Handlung();
									}
									if (d2_DispatchTutorialEvent(0x20, p, 0,
									                 *(unsigned int*) (row + 0x779160)) == 1) {
										for (i = 0; i < 0x3e; i++) {
											*(int*) (tmpl + i * 4) = 0;
										}
										if (*(unsigned short*) (p + 0x27) != 0xffff) {
											v33 = *(unsigned int*) (*(unsigned short*) (p + 0x27) * 0x21c + 0x7f4ca4);
										} else {
											v33 = *(unsigned int*) (gm_LocalPlayerSlot * 0x21c + 0x7f4ca4);
										}
										v34 = *(unsigned int*) (p + 1);
										*(char*) (tmpl + 0x04) = 4;
										*(unsigned int*) (tmpl + 0x08) = v33;
										*(int*) (tmpl + 0x0c) = v34;
										*(int*) (tmpl + 0x10) = 0;
										*(int*) (tmpl + 0x14) = 0;
										*(int*) (tmpl + 0x28) = *(int*) 0x7f4c00;
										*(int*) (tmpl + 0x2c) = *(int*) 0x7f4c04;
										*(int*) (tmpl + 0x30) = *(int*) 0x7f4c08;
										*(unsigned short*) (tmpl + 0x34) =
										    *(unsigned short*) 0x7f4c0c;
										*(char*) (tmpl + 0x36) = 1;
										*(unsigned short*) (tmpl + 0x58) =
										    *(unsigned short*) (row + 0x779160);
										*(int*) (tmpl + 0x5c) = 0xffffffff;
										*(int*) (tmpl + 0x68) = v34;
										*(int*) (tmpl + 0x6c) = *(int*) (entry + 2);
										found = cm_SendCopyEntityData(tmpl);
										if (found != -1) {
											while (!cm_GetCommandStatus(found)) {
												main_RunFrameLoop(0, 0x20007);
											}
										}
										found = cm_GetCommandResult(found);
										d2_DispatchTutorialInput(0x20, 0, 0, 0);
									}
found_row:
									d3snd_PlayWorkerOrderVoice();
									r = (int*) 0x7e30d0;
									do {
										if (*r == 0xffff) {
											break;
										}
										if (r[4]) {
											he_AssignActionSlot(p, *(int*) 0x7746cc, *r, found);
											*(unsigned char*) (*r * 0x21c + 0x7f4e28) = 0;
										}
										r += 10;
									} while ((int) r < 0x7e35d0);
									if (found && !*(int*) (found + 0x70)) {
										*(unsigned int*) (found + 0x70) = 1;
									}
								}
							}
						}
					}
					row += 0x58;
					rowsLeft--;
				} while (rowsLeft);
			}
		}
		if (io_RightButtonReleased) {
			any = 0;
			r = (int*) 0x7e30e0;
			do {
				if ((int) r >= 0x7e35e0 || r[-4] == 0xffff) {
					break;
				}
				if (*r) {
					any = 1;
				}
				r += 10;
			} while (!any);
			if (!any) {
				if (d2_CanCloseWindowDuringTutorial() == 1) {
					d2_DialogCloseRequested = 1;
					d3_EndCameraAndUiMode();
				}
				goto after_input;
			}
			r = (int*) 0x7e30d0;
			do {
				int slot;

				slot = *r;
				if (slot == 0xffff) {
					break;
				}
				r += 10;
				*(unsigned char*) (slot * 0x21c + 0x7f4e28) = 0;
			} while ((int) r < 0x7e35d0);
		}
after_input:
		{
			unsigned short* shop;
			int* cell;

			shop = (unsigned short*) gm_QueryEntities(*(int*) (limit + 0x14), 1, 5);
			n = count;
			if (shop) {
				cell = (int*) (count * 0x58 + 0x779160);
				do {
					int dup;

					dup = 1;
					if (2 <= *(int*) ((char*) shop + 14)) {
						int k;
						int* c;

						k = 0;
						c = (int*) 0x779160;
						do {
							if (count <= k) {
								if (dup && (int) cell <= 0x7796df) {
									count++;
									*cell = (int) *shop;
									cell += 0x16;
								}
								break;
							}
							if (*c == (int) *shop) {
								dup = 0;
							}
							k++;
							c += 0x16;
						} while (dup);
					}
					shop = (unsigned short*) gm_NextEntityQueryMatch();
				} while (shop);
				n = count;
			}
			if (1 <= n) {
				int* r3;
				int rows;

				r3 = (int*) 0x7791b0;
				rows = count;
				do {
					int* cells;
					int off;
					int got;

					cells = r3 - 0x13;
					*r3 = 0x7fffffff;
					off = 0x26;
					do {
						*cells = *(unsigned short*) (off + r3[-0x14] * 0x41 + 8 +
						                              (int) lpObjektePROT);
						cells[4] = *(unsigned short*) (off + r3[-0x14] * 0x41 +
						                               (int) lpObjektePROT);
						if (*cells) {
							got = gm_QueryEntities(*(int*) (entry + 0x14), 1, 0, *cells);
							if (!(got)) {
								*r3 = 0;
							} else {
								int best;
								int t;

								best = *r3;
								t = gm_GetMsgField(entry, got) /
								    *(unsigned short*) (off + r3[-0x14] * 0x41 +
								                        (int) lpObjektePROT);
								if (t <= best) {
									*r3 = t;
								}
							}
						}
						off += 2;
						cells++;
					} while (off < 0x2e);
					*r3 = *(unsigned short*) (r3[-0x14] * 0x41 + 0x36 +
					                          (int) lpObjektePROT) * *r3;
					got = gm_QueryEntities(*(int*) (entry + 0x14), 1, 0, r3[-0x14]);
					if (got) {
						r3[1] = gm_GetMsgField(entry, got);
					} else {
						r3[1] = 0;
					}
					r3 += 0x16;
					rows--;
				} while (rows);
			}
			fcn_00657a73(count, list, 10);
			d2_SetLabelText(listControl, list);
			window = saved;
			*(unsigned int*) ((int) d2_Controls + 0x6c + listControl * 0x2f4) = 1;
			*(unsigned int*) ((int) d2_Controls + 0x18 + listControl * 0x2f4) = 0x30;
			d2_RenderProduktionStockRows(saved, 2, count, entry, 0);
			if (idx) {
				d2_SetForm(saved, 2);
				idx = 0;
				*(int*) (d2_CurrentWindowId * 0x3cc + 0x1016198) =
				    *(int*) (d2_CurrentWindowId * 0x3cc + 0x10161b4) *
				    (signed char) building[0x59];
			}
			d2_SyncWareProduktionSlotGrid(building, entry);
			d2_RefreshWorkshopInventoryGrids(saved, 1, 0, building);
			if (!main_RunFrameLoop((void*) 0x5944d0, 0x677c7)) {
				d2_SetForm(saved, 2);
				building[0x59] = (unsigned char) ((*(int*) (d2_CurrentWindowId * 0x3cc + 0x10161a0) +
				                             *(int*) (d2_CurrentWindowId * 0x3cc + 0x1016198)) /
				                            *(int*) (d2_CurrentWindowId * 0x3cc + 0x10161b4));
				d2_DestroyForm(saved);
				d2_RestoreHudAfterDialog();
				d2_DispatchTutorialInput(0x1f, 0, 1, 0);
				return 0;
			}
		}
	}
}
