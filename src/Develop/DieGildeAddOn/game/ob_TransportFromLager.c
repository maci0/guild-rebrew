/*
 * Move the selected goods from the warehouse for every stock slot that covers
 * the requested amount, refresh the slot display and report the remainder.
 */

#include <stdlib.h>

extern char* g_entity_type_table;    /* 0x00868050 */
#include "Develop/DieGildeAddOn/game/game_player.h"      /* 0x00774970 */
#include "GOLDTL.ob_TransportFromLager_gconf.h"
extern float flt_1;                  /* 0x006628a0 */
extern float g_6628a8;               /* 0x006628a8 */
extern double dbl_1_0;               /* 0x006629c8 */

unsigned short* __cdecl fcn_00502cd0(int, int, ...);
void __cdecl ReportClientMessage(const char*);
void __cdecl cm_BeginCommandSync(void);
void __cdecl cm_EndCommandSync(void);
int __cdecl cm_AreQueuedCommandsDone(void);
void __cdecl cm_StepCommandQueue(void);
int __cdecl d2_GetControlValue(int);
int __cdecl gm_CheckInventoryCapacity(char*, int, int);
int __cdecl gm_GetFreeStorageSlotCapacity(int, int, int);
float __cdecl gm_GetSeasonPrice(int id, unsigned char a);
int __cdecl gm_CheckEntityStock(void*, int, int);
int __cdecl gm_ConvertUnitsToAmount(int, int);
int __cdecl d2_DispatchTutorialEvent(int, int, int, int);
void __cdecl d2_DispatchTutorialInput(int, int, int, int);
int __cdecl cm_SendSellObjekt(int, int, int, int, int, int);
void __cdecl d2_SetElementValue(int, ...);
void __cdecl io_FormatTextBuffer(char*, int, int);
void __cdecl d2_ShowStatusBanner(char*);
void __cdecl sb_PlayVoice(int, char*, int, int, int, int, int);

/* ADDRESS: GOLDTL 0x005ba0e0 */
int __cdecl ob_TransportFromLager(int a0, char* a1, char* a2, int a3, int a4,
                                  float a5, int a6, int a7)
{
	int* stockSlot;

	int query;
	char* type;
	int n;
	char buf[0x100];

	query = 0;
	type = 0;
	if (a2) {
		type = g_entity_type_table + (unsigned char)*a2 * 0x24d;
	}
	if (!a4) {
		query = (int)fcn_00502cd0(0, 2, 7, 1, a0);
		if (!query) {
			ReportClientMessage((const char*)0x6ac37c);
			return 0;
		}
	}
	cm_BeginCommandSync();
	{
		int count;
		float unitPrice;
		float countf;
		float prod;
		float scale;
	stockSlot = (int*)0x7796e0;
	do {
		if (stockSlot[4] != -1 && d2_GetControlValue(stockSlot[4])) {
			count = d2_GetControlValue(stockSlot[4]);
			if (!a4) {
				if (query) {
					count = gm_GetFreeStorageSlotCapacity(query, *stockSlot, count);
				}
			} else {
				count = gm_CheckInventoryCapacity((char*)a4, *stockSlot, count);
			}
			if (count > 0) {
				if (a3) {
					if (*type == '\n') {
						unitPrice = gm_GetSeasonPrice(*stockSlot, a6) * *(double*)0x664ef8;
					} else {
						unitPrice = gm_GetSeasonPrice(*stockSlot, a6) * *(float*)(a2 + 0x49);
					}
					if (a7 == 2 || a7 == 4) {
						unitPrice = gm_GetSeasonPrice(*stockSlot, *(char*)(a2 + 0x65));
					}
				} else {
					unitPrice = 0.0f;
				}
				countf = (float)count;
				prod = countf * unitPrice;
				scale = flt_1 / a5;
				if (gm_CheckEntityStock(g_slot_table + g_774970 * 0x21c,
				                 (int)(scale * prod), a6) && stockSlot[0xc] >= 0) {
					n = gm_ConvertUnitsToAmount(1, a6);
					if (abs((int)(scale * countf * unitPrice - prod)) < n) {
						a5 = 1.0f;
					}
					if (a7 & 8) {
						if (a4) {
							if (!d2_DispatchTutorialEvent(0x29, (int)a2, 0, *stockSlot)) {
								goto next;
							}
							d2_DispatchTutorialInput(0x29, (int)a2, 0, *stockSlot);
						} else {
							if (!d2_DispatchTutorialEvent(0x27, (int)a2, 0, *stockSlot)) {
								goto next;
							}
							d2_DispatchTutorialInput(0x27, (int)a2, 0, *stockSlot);
						}
					} else if (a7 & 1) {
						if (a4) {
							if (!d2_DispatchTutorialEvent(0x2a, (int)a2, 0, *stockSlot)) {
								goto next;
							}
							d2_DispatchTutorialInput(0x2a, (int)a2, 0, *stockSlot);
						} else {
							if (!d2_DispatchTutorialEvent(0x25, (int)a2, 0, *stockSlot)) {
								goto next;
							}
							d2_DispatchTutorialInput(0x25, (int)a2, 0, *stockSlot);
						}
					}
					cm_SendSellObjekt(a0, *(int*)(a1 + 2), *stockSlot, count, a6,
					             (int)(unitPrice / a5));
					if (unitPrice != g_6628a8 && a5 != dbl_1_0) {
						io_FormatTextBuffer(buf, 0xec, (int)(prod * a5 - prod));
						d2_ShowStatusBanner(buf);
						sb_PlayVoice(0, (char*)0x68aed0, 1, 0x3f, 0x7f, 0, 0);
					}
					d2_SetElementValue(stockSlot[4], 0, stockSlot[0xc],
					                   d2_GetControlValue(stockSlot[4]) - count, 0);
				}
			}
		}
next:
		stockSlot += 0xe;
	} while ((int)stockSlot < 0x7798a0);
	stockSlot = (int*)0x778da0;
	do {
		if (stockSlot[4] != -1 && d2_GetControlValue(stockSlot[4])) {
			count = d2_GetControlValue(stockSlot[4]);
			if (!a4) {
				count = gm_GetFreeStorageSlotCapacity(query, *stockSlot, count);
			} else {
				count = gm_CheckInventoryCapacity((char*)a4, *stockSlot, count);
			}
			if (count > 0) {
				if (a3) {
					unitPrice = gm_GetSeasonPrice(*stockSlot, a6) * *(float*)(a2 + 0x49);
				} else {
					unitPrice = 0.0f;
				}
				countf = (float)count;
				prod = countf * unitPrice;
				scale = flt_1 / a5;
				if (gm_CheckEntityStock(g_slot_table + g_774970 * 0x21c,
				                 (int)(scale * prod), a6) && stockSlot[0xc] >= 0) {
					n = gm_ConvertUnitsToAmount(1, a6);
					if (abs((int)(scale * countf * unitPrice - prod)) < n) {
						a5 = 1.0f;
					}
					if (a7 & 8) {
						if (a4) {
							if (!d2_DispatchTutorialEvent(0x29, (int)a2, 0, *stockSlot)) {
								goto next2;
							}
							d2_DispatchTutorialInput(0x29, (int)a2, 0, *stockSlot);
						} else {
							if (!d2_DispatchTutorialEvent(0x27, (int)a2, 0, *stockSlot)) {
								goto next2;
							}
							d2_DispatchTutorialInput(0x27, (int)a2, 0, *stockSlot);
						}
					} else if (a7 & 1) {
						if (a4) {
							if (!d2_DispatchTutorialEvent(0x2a, (int)a2, 0, *stockSlot)) {
								goto next2;
							}
							d2_DispatchTutorialInput(0x2a, (int)a2, 0, *stockSlot);
						} else {
							if (!d2_DispatchTutorialEvent(0x25, (int)a2, 0, *stockSlot)) {
								goto next2;
							}
							d2_DispatchTutorialInput(0x25, (int)a2, 0, *stockSlot);
						}
					}
					cm_SendSellObjekt(a0, *(int*)(a1 + 2), *stockSlot, count, a6,
					             (int)(unitPrice / a5));
					if (unitPrice != g_6628a8 && a5 != dbl_1_0) {
						io_FormatTextBuffer(buf, 0xec, (int)(prod * a5 - prod));
						d2_ShowStatusBanner(buf);
						sb_PlayVoice(0, (char*)0x68aed0, 1, 0x3f, 0x7f, 0, 0);
					}
					d2_SetElementValue(stockSlot[4], 0, stockSlot[0xc],
					                   d2_GetControlValue(stockSlot[4]) - count, 0);
				}
			}
		}
next2:
		stockSlot += 0xe;
	} while ((int)stockSlot < 0x779120);
	}
	cm_EndCommandSync();
	while (!cm_AreQueuedCommandsDone()) {
		cm_StepCommandQueue();
	}
	return 1;
}
