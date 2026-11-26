#include "client_packet_builder.h"
#include "Develop/DieGildeAddOn/game/season_slots.h"
#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char* g_773d78;
extern unsigned char g_773d75;
extern unsigned char* lpGebaeudePROT;
extern char* lpObjektePROT;
/* SIZE 0x80 */
typedef struct {
	unsigned short id;
	char pad2[2];
	int active;
	char pad8[0x28 - 8];
	unsigned char value;
	char pad29[0x3c - 0x29];
	unsigned short target;
	char pad3e[0x80 - 0x3e];
} Slot;

unsigned short* __cdecl gm_StartFilteredEntitySearch(int, ...);
void* __cdecl gm_FindNextFilteredEntity(void);
void* __cdecl gm_FindKind47ByOwner(int);
char* __cdecl fcn_00502cd0(int, int, ...);
void* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl cm_GetCommandStatus(int);
char* __cdecl cm_GetCommandResult(int);
void __cdecl cm_BeginCommandSync(void);
void __cdecl cm_EndCommandSync(void);
int __cdecl cm_AreQueuedCommandsDone(void);
void __cdecl cm_AppendPacketFieldValue(int, int, int, void*);
void __cdecl cm_RequestChangeAttribute(void);
int __cdecl cm_SendSellObjekt(int, int, int, int, char, int);
void __cdecl cm_SendUpdateSlot80(char*, char);
unsigned short __cdecl gm_RandomMod(unsigned short);
void __cdecl fcn_00535960(void);

/* ADDRESS: GOLDTL 0x005017a0 */
void __cdecl gm_UpdateMarketStockSlots(int player)
{
	Slot rec;
	MARKET_STOCK_SLOT* p;
	MARKET_STOCK_SLOT* s;
	MARKET_STOCK_SLOT* q;
	char* ent;
	char* ent2;
	char* o;
	unsigned char* e;
	unsigned short* item;
	unsigned short* item2;
	int* ip;
	int v;
	int n;
	int i;
	int codes[8] = { 0x92, 0x93, 0x94, 0x95, 0x96, 0x97, 0x2db, 0 };

	g_773d78 = (char*) gm_StartFilteredEntitySearch(1, 5, 10);
	if (g_773d78 == 0) {
		return;
	}
	s = (MARKET_STOCK_SLOT*) (g_85ab90 + player * 0x2a90);
	if (player == g_773d75) {
		p = s;
		for (n = 0x55; n != 0; n--) {
			p->active = 0;
			p = (MARKET_STOCK_SLOT*) ((char*) p + 0x80);
		}
		e = (unsigned char*) gm_StartFilteredEntitySearch(1, 6);
		while (e != 0) {
			if ((char)((BUILDING_PROTOTYPE*)lpGebaeudePROT)[*e].category != 0x0a) {
				ent = fcn_00502cd0(*(int*) (e + 0x5d), 1, 0, 0xff);
				i = 0;
				if (ent != 0) {
					for (p = s; i < 0x55; i++, p = (MARKET_STOCK_SLOT*) ((char*) p + 0x80)) {
						if (p->objekt_id != 0 &&
						    fcn_00502cd0(*(int*) (ent + 0x14), 1, 0, p->objekt_id) != 0) {
							p->active = 1;
							item = (unsigned short*) ((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[p->objekt_id] + 0x2e);
							for (q = s, n = 0x55; n != 0; n--) {
								for (v = 4, item2 = item; v != 0; v--) {
									if (q->objekt_id == *item2) {
										q->active = 1;
									}
									item2++;
								}
								q = (MARKET_STOCK_SLOT*) ((char*) q + 0x80);
							}
						}
					}
				}
			}
			e = (unsigned char*) gm_FindNextFilteredEntity();
		}
		p = s;
		for (n = 0x55; n != 0; n--) {
			rec = *(Slot*)s;
			ent = fcn_00502cd0(*(int*) (g_773d78 + 0x5d), 1, 0, p->target_id);
			if (ent != 0) {
				ent2 = fcn_00502cd0(*(int*) (ent + 0x14), 1, 0, 0xff);
				if (ent2 == 0) {
					v = cm_SendSellObjekt(*(int*) (ent + 2), -1, 0xff, 1, (char) g_773d75, 0);
					while (cm_GetCommandStatus(v) == 0) {
						fcn_00535960();
					}
					ent2 = cm_GetCommandResult(v);
				}
				if (p->active != 0) {
					if (fcn_00502cd0(*(int*) (ent2 + 0x14), 1, 0, p->objekt_id) == 0) {
						v = cm_SendSellObjekt(*(int*) (ent2 + 2), -1, p->objekt_id, 1, (char) g_773d75, 0);
						while (cm_GetCommandStatus(v) == 0) {
							fcn_00535960();
						}
					}
				} else {
					o = fcn_00502cd0(*(int*) (ent2 + 0x14), 1, 0, p->objekt_id);
					if (o != 0) {
						v = cm_SendSellObjekt(-1, *(int*) (ent2 + 2), p->objekt_id,
								 *(int*) (o + 0xe), (char) g_773d75, 0);
						while (cm_GetCommandStatus(v) == 0) {
							fcn_00535960();
						}
					}
				}
				cm_SendUpdateSlot80((char*) &rec, (char) player);
			}
			s = (MARKET_STOCK_SLOT*) ((char*) s + 0x80);
			p = (MARKET_STOCK_SLOT*) ((char*) p + 0x80);
		}
		ip = codes;
		for (v = *ip; v != 0; v = *++ip) {
			int count;
			count = 0;
			ent = fcn_00502cd0(*(int*) (g_773d78 + 0x5d), 1, 0, v);
			if (ent != 0) {
				ent2 = fcn_00502cd0(*(int*) (ent + 0x14), 1, 0, 0xff);
				if (ent2 != 0) {
					o = fcn_00502cd0(*(int*) (ent2 + 0x14), 1, 5);
					while (o != 0) {
						count++;
						o = (char*) gm_NextEntityQueryMatch();
					}
					o = fcn_00502cd0(*(int*) (ent + 0x14), 1, 4, 0x11);
					if (o != 0 && (int) *(unsigned char*) (o + 0x1c) < count) {
						count -= *(unsigned char*) (o + 0x1c);
						cm_BeginPacketFieldDelta(o, *(int*) (o + 2));
						cm_AppendPacketFieldValue(1, 1, o - g_aed32c + 0x1c, &count);
						cm_RequestChangeAttribute();
					}
				}
			}
		}
	} else {
		e = (unsigned char*) gm_FindKind47ByOwner(player);
		if (e == 0) {
			return;
		}
		ent = fcn_00502cd0(*(int*) (e + 0x5d), 2, 0, 0x1db, 6);
		if (ent == 0) {
			return;
		}
		ent2 = fcn_00502cd0(*(int*) (e + 0x5d), 2, 0, 0x1dc, 6);
		if (ent2 == 0) {
			return;
		}
		cm_BeginCommandSync();
		p = s;
		for (n = 0x55; n != 0; n--) {
			rec = *(Slot*)p;
			if (rec.id != 0) {
				if (fcn_00502cd0(*(int*) (ent + 0x14), 1, 0, rec.id) != 0 ||
				    fcn_00502cd0(*(int*) (ent2 + 0x14), 1, 0, rec.id) != 0) {
					if (rec.value == 0) {
						rec.value = (unsigned char) gm_RandomMod(0xff);
						rec.active = rec.value <= 0x80;
					} else {
						rec.value += (unsigned char) gm_RandomMod(8) + 0x18;
						rec.active = rec.value <= 0x80;
					}
				} else {
					rec.active = 0;
				}
				cm_SendUpdateSlot80((char*) &rec, (char) player);
			}
			p = (MARKET_STOCK_SLOT*) ((char*) p + 0x80);
		}
		cm_EndCommandSync();
		while (cm_AreQueuedCommandsDone() == 0) {
			fcn_00535960();
		}
	}
}
