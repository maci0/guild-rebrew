#include <stdio.h>
#include <string.h>
#include "Develop/DieGildeAddOn/game/building_prototype.h"
extern char str_empty[];
extern char gm_EntityIdField[];
extern char gm_EntitySlotTable[];
#include "Develop/DieGildeAddOn/game/game_player.h"
extern int g_68b79c;
extern char* g_772e98;
extern char* cut_CombatDefenderEntity;
extern char* cut_CombatCancelledEntity;
extern int io_RightButtonReleased;
extern int d2_DialogButtonAction;
#include "Develop/Units/d2.v1/client_dialog_state.h"
extern unsigned char* lpGebaeudePROT;
extern unsigned char gm_ActiveTownIndex;
extern int d2_CurrentWindowId;
extern int cm_PacketDeltaBase;
extern char* d2_ObjektNameTable[];
typedef struct { unsigned char kind; unsigned char unknown01[0x24c]; } COMBAT_BUILDING_STUB;

void __cdecl d2_SetMouseTooltip(char*);
void __cdecl d2_ShowStatusBanner(char*);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
char* __cdecl gm_QueryEntities(int, ...);
char* __cdecl gm_LookupEntityRecordById(int);
void __cdecl gm_CheckCombatGearWear(char*);
char* __cdecl gm_LookupEntityRecordIn32SlotTable(int);
int __cdecl d2_LoadForm(int, int, char*);
void __cdecl d2_CenterForm(int, int);
void __cdecl d2_SetForm(int, int);
void __cdecl io_AppendText(int, ...);
int __cdecl main_RunFrameLoop(void*, int);
int __cdecl gm_SearchTable67(int);
void __cdecl d2_DrawCombatParticipants(char*, int, int);
int __cdecl d2_DrawPartyStoreItems(int, int, int);
char* __cdecl gm_GetEntityTableEntry(char*);
void __cdecl fcn_0050d490(char*);
void __cdecl cm_SendSellObjekt(int, int, int, int, int, int);
float __cdecl gm_GetSeasonPrice(int, unsigned char);
char* __cdecl gm_NextEntityQueryMatch(void);
void __cdecl gm_IncrementMissionActionCount(char*, int);
void __cdecl cm_SendSetGebBesitzer(int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
int __cdecl d2_ShowMessageBox(char*, unsigned int);
void __cdecl io_ClearInputButtonFlags(int);
int __cdecl d2_DestroyForm(int);
int __cdecl cut_RandMod(int);
int __cdecl gm_AccumulateTyped2(char*);
void __cdecl cm_RequestMoveCredits(int, int, int, int);
int __cdecl gm_MapEntityStatRange(int);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);
void __cdecl d2_AddElementToWindow(int, int, int, int);
void __cdecl d2_DrawSegmentedBar(int, int, int, int);
int __cdecl gm_ConvertUnitsToAmount(int, int);
void __cdecl cm_BeginPacketFieldDelta(char*, int);
void __cdecl cm_AppendCommandSyncField(int, int, int, int*);
void __cdecl cm_RequestChangeAttribute(void);
#include "Develop/Units/d2.v1/d2_gui.h"
int __cdecl gm_MapBuildingCatToGuildSlot(int);
int __cdecl gm_CheckStatLevel(int, int);
int __cdecl gm_RandomMod(unsigned short);
void __cdecl gm_AdjustGebaeudeCondition(char*, int);

/* ADDRESS: GOLDTL 0x004d6170 */
int __cdecl d2_ShowCombatEndCutscene(char* ctx)
{
	int mode;
	char* side;
	char* rec;
	int pay;
	int screen;
	int qlo;
	int qhi;
	int flo;
	int fhi;
	char small[0x100];
	char buf[0x400];
	char cat[0x400];
	char msg[0x400];
	int* id;
	int n;
	int tally;
	char* ent;
	char* cur;
	int flags;
	unsigned char kind;
	char* row;
	int i;
	int col;
	int line;
	int bonus;
	int sum;
	int choice;
	char* p;
	int mask;
	char* looked;
	char looked_kind;
	char* self;

	self = ctx;
	mode = 0;
	rec = 0;
	d2_SetMouseTooltip(str_empty);
	d2_ShowStatusBanner(str_empty);
	if (*(int*) (self + 0x10c) != -1) {
		ent = gm_StartFilteredEntitySearch(1, 1, *(int*) (self + 0x10c));
		rec = gm_QueryEntities(*(int*) (ent + 0x5d), 2, 6, 0, 0x116);
		if (rec == 0) {
			rec = gm_QueryEntities(*(int*) (ent + 0x5d), 2, 6, 0, 0x2a);
		}
	}
	if (g_68b79c == *(int*) (gm_EntityIdField + gm_LocalPlayerSlot * 0x21c)) {
		for (id = (int*) (self + 0x80), n = 16; n != 0; n--, id++) {
			if (*id != -1) {
				ent = gm_LookupEntityRecordById(*id);
				if (ent != 0) {
					gm_CheckCombatGearWear(ent);
				}
			}
		}
		for (id = (int*) (self + 0xc0), n = 16; n != 0; n--, id++) {
			if (*id != -1) {
				ent = gm_LookupEntityRecordById(*id);
				if (ent != 0) {
					gm_CheckCombatGearWear(ent);
				}
			}
		}
	}
	if (cut_CombatCancelledEntity == 0) {
		tally = 0;
		for (id = (int*) (self + 0x80), n = 16; n != 0; n--, id++) {
			if (*id != -1) {
				looked = gm_LookupEntityRecordIn32SlotTable(*id);
				looked_kind = looked[8];
				if (looked_kind != 0 && looked_kind != 4 &&
					*(int*) (*(int*) (*(int*) (looked + 0x184) + 0x34) + 0x218) != 1) {
					tally++;
				}
			}
		}
		n = 0;
		for (id = (int*) (self + 0xc0), i = 16; i != 0; i--, id++) {
			if (*id != -1) {
				looked = gm_LookupEntityRecordIn32SlotTable(*id);
				looked_kind = looked[8];
				if (looked_kind != 0 && looked_kind != 4 &&
					*(int*) (*(int*) (*(int*) (looked + 0x184) + 0x34) + 0x218) != 1) {
					n++;
				}
			}
		}
		p = g_772e98;
		if (n > tally) {
			p = cut_CombatDefenderEntity;
		}
		side = p;
	} else {
		side = g_772e98;
		if (cut_CombatCancelledEntity != cut_CombatDefenderEntity) {
			side = cut_CombatDefenderEntity;
		}
	}
	screen = d2_LoadForm(0, 0, "cutscenes\\combat_end");
	d2_CenterForm(screen, 3);
	d2_SetForm(screen, 2);
	io_AppendText(0x7d);
	d2_SetForm(screen, 1);
	if (*(int*) (gm_EntityIdField + gm_LocalPlayerSlot * 0x21c) == *(int*) (side + 4)) {
		if (side == g_772e98) {
			if (self[0x7c] & 1) {
				io_AppendText(0x1189, *(unsigned short*) g_772e98, *(unsigned short*) cut_CombatDefenderEntity);
				io_AppendText(0x118a);
			} else {
				io_AppendText(0x1189, *(unsigned short*) g_772e98, *(unsigned short*) cut_CombatDefenderEntity);
			}
		} else {
			io_AppendText(0x118e, *(unsigned short*) cut_CombatDefenderEntity, *(unsigned short*) g_772e98);
		}
	} else if (side == cut_CombatDefenderEntity) {
		io_AppendText(0x118c, *(unsigned short*) g_772e98, *(unsigned short*) cut_CombatDefenderEntity);
		if (self[0x7c] & 1) {
			ent = gm_QueryEntities(0, 2, 7, 1, *(int*) (self + 0x100));
			if (*(int*) (ent + 0x24) != 0 && gm_SearchTable67(*(int*) (*(int*) (ent + 0x24) + 0xb4)) != 0) {
				io_AppendText(0x118d);
			}
		}
	} else {
		io_AppendText(0x118f, *(unsigned short*) cut_CombatDefenderEntity, *(unsigned short*) g_772e98);
	}
	while (main_RunFrameLoop(d2_ShowCombatEndCutscene, 0x7d6c6) != 0) {
		if (io_RightButtonReleased != 0 || d2_DialogButtonAction == 2) {
			d2_DialogCloseRequested = 1;
		}
	}
	d2_SetForm(screen, 1);
	io_AppendText((int) "$C");
	io_AppendText(0x1191);
	ent = gm_StartFilteredEntitySearch(1, 1, *(int*) (self + 0x10c));
	kind = ((BUILDING_PROTOTYPE*)lpGebaeudePROT)[(unsigned char) *ent].category;
	if (kind == 0x13) {
		mode = 0;
	} else if (kind == 0x10) {
		mode = 1;
	} else if (kind == 4) {
		mode = 2;
	}
	io_AppendText(0x1193, *(unsigned short*) cut_CombatDefenderEntity, mode + 0x1125);
	d2_DrawCombatParticipants(self + 0xc0, 0, 0x64);
	ent = gm_StartFilteredEntitySearch(1, 1, *(int*) (self + 0x14));
	if (ent == 0) {
		mode = 0;
	} else {
		kind = ((BUILDING_PROTOTYPE*)lpGebaeudePROT)[(unsigned char) *ent].category;
		if (kind == 0x13) {
			mode = 0;
		} else if (kind == 0x10) {
			mode = 1;
		} else if (kind == 4) {
			mode = 2;
		}
	}
	io_AppendText((int) "$7A");
	io_AppendText(0x1193, *(unsigned short*) g_772e98, mode + 0x1125);
	d2_DrawCombatParticipants(self + 0x80, 0, 0x12c);
	while (main_RunFrameLoop(d2_ShowCombatEndCutscene, 0x7d6c6) != 0) {
		if (io_RightButtonReleased != 0 || d2_DialogButtonAction == 2) {
			d2_DialogCloseRequested = 1;
		}
	}
	d2_SetForm(screen, 1);
	io_AppendText((int) "$C");
	io_AppendText(0x1197);
	flags = (unsigned char) self[0x7c];
	if (flags & 1) {
		if (*(unsigned short*) g_772e98 == gm_LocalPlayerSlot) {
			d2_DrawPartyStoreItems(0x24, 0x32, 2);
		} else if (*(unsigned short*) cut_CombatDefenderEntity == gm_LocalPlayerSlot) {
			pay = d2_DrawPartyStoreItems(0x24, 0x32, side == cut_CombatDefenderEntity ? 0 : 1);
			cur = gm_GetEntityTableEntry(cut_CombatDefenderEntity);
			if (cur != 0) {
				*(int*) (cur + 0x1c) += pay;
			}
			if (*(int*) (self + 0x10c) != -1) {
				ent = gm_StartFilteredEntitySearch(1, 1, *(int*) (self + 0x10c));
				*(int*) (ent + 0x4d) += pay;
			}
		}
		for (id = (int*) (self + 0x100), n = 3; n != 0; n--, id++) {
			if (*id == -1) {
				continue;
			}
			cur = gm_QueryEntities(0, 2, 7, 1, *id);
			cur = gm_QueryEntities(*(int*) (cur + 0x14), 1, 0, 0x1dd);
			cur = gm_QueryEntities(*(int*) (cur + 0x14), 1, 5);
			while (cur != 0) {
				if (side == cut_CombatDefenderEntity) {
					*(int*) (cur + 0xa) = *(unsigned short*) cut_CombatDefenderEntity;
				}
				if (*(int*) (cur + 0xa) == *(unsigned short*) cut_CombatDefenderEntity && rec != 0) {
					if (g_68b79c == *(int*) (gm_EntityIdField + gm_LocalPlayerSlot * 0x21c)) {
						fcn_0050d490(cur);
						cm_SendSellObjekt(*(int*) (rec + 2), *(int*) (cur + 6), *(unsigned short*) cur,
							*(int*) (cur + 0xe), gm_ActiveTownIndex, 0);
					}
					gm_GetSeasonPrice(*(unsigned short*) cur, gm_ActiveTownIndex);
				}
				cur = gm_NextEntityQueryMatch();
			}
		}
sync:
		while (main_RunFrameLoop(d2_ShowCombatEndCutscene, 0x7d6c6) != 0) {
			if (io_RightButtonReleased != 0 || d2_DialogButtonAction == 2) {
				d2_DialogCloseRequested = 1;
			}
		}
	} else if ((flags & 2) && side == cut_CombatDefenderEntity && *(unsigned short*) side == gm_LocalPlayerSlot) {
		ent = gm_StartFilteredEntitySearch(1, 1, *(int*) (self + 0x14));
		io_FormatTextBuffer(msg, 0x119f, ent, *(unsigned short*) cut_CombatDefenderEntity, ent);
		kind = (unsigned char) *ent;
		if (kind != 0x1e && kind != 0x20 && kind != 0x1f) {
			io_FormatTextBuffer(cat, 0x11a0, (int) kind * 14 + 0x48e);
			strcat(msg, cat);
		}
		io_FormatTextBuffer(cat, 0x11a1);
		strcat(msg, cat);
		io_FormatTextBuffer(cat, 0x11a2);
		strcat(msg, cat);
		io_FormatTextBuffer(cat, 0x11a3);
		strcat(msg, cat);
		choice = d2_ShowMessageBox(msg, 0x11);
		if (kind == 0x1e || kind == 0x20 || kind == 0x1f) {
			choice++;
		}
		if (choice == 1) {
			kind = ((BUILDING_PROTOTYPE*)lpGebaeudePROT)[(unsigned char) *ent].category;
			if (kind == 4 || kind == 0x10) {
				gm_IncrementMissionActionCount(cut_CombatDefenderEntity, 0x1c);
			}
			cm_SendSetGebBesitzer(*(int*) (ent + 1), *(int*) (cut_CombatDefenderEntity + 4), *(int*) (cut_CombatDefenderEntity + 4));
			io_FormatTextBuffer(msg, 0x11a4, *(unsigned short*) cut_CombatDefenderEntity, ent);
			d2_ShowMessageBox(msg, 0);
		} else if (choice == 2) {
			buf[0] = str_empty[0];
			memset(buf + 1, 0, 0x3ff);
			io_FormatTextBuffer(buf, 0x11a5, *(unsigned short*) cut_CombatDefenderEntity, ent);
			d2_ShowMessageBox(buf, 0);
			cur = gm_QueryEntities(*(int*) (ent + 0x5d), 2, 6, 0, 0x2a);
			if (cur == 0) {
				cur = gm_QueryEntities(*(int*) (ent + 0x5d), 2, 6, 0, 0x116);
			}
			pay = gm_AccumulateTyped2(g_772e98);
			if (pay >= 0x9c400) {
				pay = 0x9c400;
			}
			qhi = 0;
			qlo = cut_RandMod(0x32);
			if (pay < 0) {
				pay = 0;
			}
			sum = (int) (((double) qlo * 0.001 + 0.07) * pay);
			io_FormatTextBuffer(buf, (int) "$Z%T$A", sum);
			*(int*) &mode = sum;
			cm_RequestMoveCredits(*(int*) (cut_CombatDefenderEntity + 4), *(int*) (g_772e98 + 4), gm_ActiveTownIndex, sum);
			if (cur != 0 && rec != 0) {
				ent = gm_QueryEntities(*(int*) (cur + 0x14), 1, 5);
				while (ent != 0) {
					qlo = cut_RandMod(0x14) + 0x50;
					qhi = 0;
					n = (int) (*(int*) (ent + 0xe) * ((double) (unsigned) qlo * 0.01));
					if (n < 1) {
						n = 1;
					}
					sprintf(small, "%i %s$A", n, d2_ObjektNameTable[*(unsigned short*) ent * 2]);
					strcat(buf, small);
					if (g_68b79c == *(int*) (gm_EntityIdField + gm_LocalPlayerSlot * 0x21c)) {
						cm_SendSellObjekt(*(int*) (rec + 2), *(int*) (cur + 2), *(unsigned short*) ent, n, gm_ActiveTownIndex, 0);
					}
					sum = (int) (gm_GetSeasonPrice(*(unsigned short*) ent, gm_ActiveTownIndex) * (double) n + (double) sum);
					ent = gm_NextEntityQueryMatch();
				}
			}
			goto settle;
		} else if (choice == 3) {
reduce:
			buf[0] = str_empty[0];
			memset(buf + 1, 0, 0x3ff);
			io_FormatTextBuffer(buf, 0x11a6, *(unsigned short*) cut_CombatDefenderEntity, ent);
			d2_ShowMessageBox(buf, 0);
			if (g_68b79c == *(int*) (gm_EntityIdField + gm_LocalPlayerSlot * 0x21c)) {
				gm_AdjustGebaeudeCondition(ent, 0x14 - cut_RandMod(0x14));
			}
		} else if (choice == 0) {
			io_FormatTextBuffer(msg, 0x11a7, *(unsigned short*) cut_CombatDefenderEntity, *(unsigned short*) cut_CombatDefenderEntity);
			d2_ShowMessageBox(msg, 0);
			for (row = gm_EntitySlotTable + 0x164; row < gm_EntitySlotTable + 0x65564; row += 0x21c) {
				if (*(unsigned short*) (row - 0x164) == 0xffff || *(unsigned char*) (row - 0x15c) == 0) {
					continue;
				}
				i = gm_MapEntityStatRange(*(unsigned char*) row);
				if (i == 0xa || i == 0xb || i == 0xc) {
					cm_RequestCopyEntityData(*(int*) (cut_CombatDefenderEntity + 4), *(int*) (row - 0x160), 6, 1);
				}
			}
		}
	} else if (flags & 4) {
		ent = gm_StartFilteredEntitySearch(1, 1, *(int*) (self + 0x10c));
		if (((BUILDING_PROTOTYPE*)lpGebaeudePROT)[(unsigned char) *ent].category == 0x13) {
			sum = 0;
			for (id = (int*) (self + 0x80), i = 0; i < 16; i++, id++) {
				if (*id == -1) {
					continue;
				}
				cur = gm_LookupEntityRecordIn32SlotTable(*id);
				col = (i % 4) * 80 + 0x30;
				line = (i / 4 + 1) * 100;
				d2_AddElementToWindow(col, line, 0x5db, d2_CurrentWindowId);
				d2_AddElementToWindow(col + 2, line, *(int*) (cur + 0x18c), d2_CurrentWindowId);
				d2_DrawSegmentedBar(col, line + 0x3c, *(unsigned char*) (cur + 0x83), 0x4eb);
				bonus = 0;
				if (cur[8] == 0) {
					bonus = (int) (*(unsigned char*) (cur + 0x83) * (1.0f / 42.0f) + 1.0f);
					d2_AddElementToWindow(col + 6, line + 6, 0x3b, d2_CurrentWindowId);
					bonus = gm_ConvertUnitsToAmount(bonus * 40, gm_ActiveTownIndex);
				}
				if (side == cut_CombatDefenderEntity && cur[8] != 0) {
					cm_BeginPacketFieldDelta(cur, *(int*) (cur + 4));
					pay = 0;
					cm_AppendCommandSyncField(4, 1, (int) cur - cm_PacketDeltaBase + 0x16c, &pay);
					cm_RequestChangeAttribute();
				}
				io_FormatTextBuffer(small, (int) "%T", bonus);
				if (bonus != 0) {
					d2_ShowTxt(col, line + 0x50, small, d2_CurrentWindowId);
				}
				sum += bonus;
			}
			if (sum != 0) {
				cm_RequestMoveCredits(*(int*) (cut_CombatDefenderEntity + 4), -1, gm_ActiveTownIndex, sum);
			} else if (*(unsigned short*) cut_CombatDefenderEntity == gm_LocalPlayerSlot) {
				io_AppendText(0x11b6);
			}
			if (*(int*) (self + 0x10c) != -1) {
				ent = gm_StartFilteredEntitySearch(1, 1, *(int*) (self + 0x10c));
				*(int*) (ent + 0x4d) += sum;
			}
			goto sync;
		}
	} else if (self[0x7c] != 0 && side == cut_CombatDefenderEntity && cut_CombatDefenderEntity[2] != 6 && cut_CombatDefenderEntity[2] != 7) {
		i = gm_MapBuildingCatToGuildSlot((unsigned char) *ent);
		if (gm_CheckStatLevel(*(unsigned short*) cut_CombatDefenderEntity, i) == 0 || *ent == 0xd || *ent == 0xc || *ent == 0xb) {
			mask = 0xffff;
			choice = (gm_RandomMod(3) & mask) + 1;
			if (choice != 0) {
				if (choice == 2) {
					buf[0] = str_empty[0];
					memset(buf + 1, 0, 0x3ff);
					io_FormatTextBuffer(buf, 0x11a5, *(unsigned short*) cut_CombatDefenderEntity, ent);
					d2_ShowMessageBox(buf, 0);
					cur = gm_QueryEntities(*(int*) (ent + 0x5d), 2, 6, 0, 0x2a);
					if (cur == 0) {
						cur = gm_QueryEntities(*(int*) (ent + 0x5d), 2, 6, 0, 0x116);
					}
					pay = gm_AccumulateTyped2(g_772e98);
					if (pay >= 0x9c400) {
						pay = 0x9c400;
					}
					flo = cut_RandMod(0x32);
					fhi = 0;
					if (pay < 0) {
						pay = 0;
					}
					sum = (int) (((double) flo * 0.001 + 0.07) * pay);
					io_FormatTextBuffer(buf, (int) "$Z%T$A", sum);
					cm_RequestMoveCredits(*(int*) (cut_CombatDefenderEntity + 4), *(int*) (g_772e98 + 4), gm_ActiveTownIndex, sum);
					if (cur != 0 && rec != 0) {
						p = gm_QueryEntities(*(int*) (cur + 0x14), 1, 5);
						while (p != 0) {
							qlo = cut_RandMod(0x14) + 0x50;
							qhi = 0;
							n = (int) (*(int*) (p + 0xe) * ((double) (unsigned) qlo * 0.01));
							if (n < 1) {
								n = 1;
							}
							sprintf(small, "%i %s$A", n, d2_ObjektNameTable[*(unsigned short*) p * 2]);
							strcat(buf, small);
							if (g_68b79c == *(int*) (gm_EntityIdField + gm_LocalPlayerSlot * 0x21c)) {
								cm_SendSellObjekt(*(int*) (rec + 2), *(int*) (cur + 2), *(unsigned short*) p, n, gm_ActiveTownIndex, 0);
							}
							sum = (int) (gm_GetSeasonPrice(*(unsigned short*) p, gm_ActiveTownIndex) * (double) n + (double) sum);
							p = gm_NextEntityQueryMatch();
						}
					}
					goto settle;
				} else if (choice == 3) {
					goto reduce;
				} else if (choice == 1) {
					io_FormatTextBuffer(cat, 0x11a7, *(unsigned short*) cut_CombatDefenderEntity, *(unsigned short*) cut_CombatDefenderEntity);
					d2_ShowMessageBox(cat, 0);
					for (row = gm_EntitySlotTable + 0x164; row < gm_EntitySlotTable + 0x65564; row += 0x21c) {
						if (*(unsigned short*) (row - 0x164) == 0xffff || *(unsigned char*) (row - 0x15c) == 0) {
							continue;
						}
						i = gm_MapEntityStatRange(*(unsigned char*) row);
						if (i == 0xa || i == 0xb || i == 0xc) {
							cm_RequestCopyEntityData(*(int*) (cut_CombatDefenderEntity + 4), *(int*) (row - 0x160), 6, 1);
						}
					}
				}
			}
		} else {
			io_FormatTextBuffer(cat, 0x11a4, *(unsigned short*) cut_CombatDefenderEntity, ent);
			d2_ShowMessageBox(cat, 0);
		}
	}
	goto done;
settle:
	d2_SetForm(screen, 1);
	io_AppendText((int) buf);
	cur = gm_GetEntityTableEntry(cut_CombatDefenderEntity);
	if (cur != 0) {
		*(int*) (cur + 0x1c) += sum;
	}
	if (*(int*) (self + 0x10c) != -1) {
		ent = gm_StartFilteredEntitySearch(1, 1, *(int*) (self + 0x10c));
		*(int*) (ent + 0x4d) += sum;
	}
	goto sync;
done:
	io_ClearInputButtonFlags(0x10);
	return d2_DestroyForm(screen);
}
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_772d14[392];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_772d54[4];
unsigned char _dpad_772d5c[252];
unsigned char _dpad_772e78[4];
unsigned char _dpad_772e90[4];
#endif
