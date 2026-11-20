#include "Develop/DieGildeAddOn/game/entity_record.h"
/*
 * Production start for one building: probes the two crafting slots, resolves
 * the production goods record, then walks the building table in a random
 * order looking for a producer that can start.
 */
#include <string.h>
#include "Develop/DieGildeAddOn/game/goods_plan.h"
#include "Develop/DieGildeAddOn/game/object_prototype.h"
typedef struct {
	char pad0[0x16c];
	int x16c;          /* +0x16c: shared building state */
	char pad170[0x1b4 - 0x170];
	int f1b4;          /* +0x1b4: selection flags */
	int pad1b8;
	unsigned short id; /* +0x1bc: current goods record id */
} Bld;
#include "Develop/DieGildeAddOn/game/production_goods.h"












typedef struct {
	char pad0[0x1c];
	unsigned char x1c;
	unsigned char x1d;
} Craft;

typedef struct {
	int kind;          /* +0x00: request kind */
	int bld;           /* +0x04: owning building */
	int rec;           /* +0x08: building record */
	int craft;         /* +0x0c: crafting slot */
	int x10;           /* +0x10 */
	int flags;         /* +0x14: flagged record count */
	int count;         /* +0x18: scanned record count */
	int x1c;           /* +0x1c */
	int x20;           /* +0x20 */
} Req; /* 0x24 */

extern char* lpObjektePROT;  /* +0x41 stride goods records: type byte, name */
 
extern int g_100b0ac;       /* building count */
extern int g_100dc20;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern int g_100dc3c;
extern char g_100dc40[];
extern char g_100dc60[];
extern char g_100ddc0[];
extern char g_100df20[];
extern unsigned short g_7f4c04;
extern char g_7f4ca0[];

int __cdecl fcn_00502cd0(int, int, int, int, int);
void __cdecl fcn_004849b0(Bld*, int, int);
void __cdecl fcn_00487000(Bld*);
void __cdecl fcn_00487970(int, Bld*, int);
void __cdecl fcn_00487c00(int, Bld*, int);
void __cdecl fcn_00487470(Bld*);
int __cdecl fcn_00486640(Bld*, PRODUCTION_GOODS_RECORD*, int);
void __cdecl fcn_004868d0(Bld*, PRODUCTION_GOODS_RECORD*);
int __cdecl fcn_005b1e40(int);
int __cdecl fcn_00503d10(int);
int __cdecl gm_eval_SlotVoll(int, int, int);
int __cdecl gm_RandomMod(unsigned short);
void __cdecl fcn_0064d41a(char*, char*, ...);
void __cdecl fcn_0047e220(int);
void __cdecl fcn_0047e0e0(Bld*, int);
void __cdecl fcn_00529160(int, int, int, int);
void __cdecl fcn_00487e60(Bld*, int);
void __cdecl fcn_00487f90(Req*);
void __cdecl ai_MeisterCollectTrans(Bld*);
void __cdecl ai_MeisterTrade(Bld*, int);


/* Starts the production of the current goods if any producer in the building
 * table can run it in the current town. */
/* ADDRESS: GOLDTL 0x0047e270 */
void __cdecl fcn_0047e270(Bld* bld)
{
	char name[0x100];
	int order[0x20];
	Req put;
	int craft;
	int i;
	int j;
	int prod;
	int hit;
	int r;
	int n;
	PRODUCTION_GOODS_RECORD* rec;
	char* goods;

	prod = fcn_00502cd0(*(int*) (bld->x16c + 0x5d), 2, 6, 0, 0xff);
	if (prod == 0)
		return;
	craft = fcn_00502cd0(*(int*) (bld->x16c + 0x5d), 2, 6, 0, 0x2a);
	if (craft == 0)
		return;
	fcn_004849b0(bld, prod, craft);
	fcn_00487000(bld);
	fcn_00487970(craft, bld, 0x4b);
	fcn_00487c00(craft, bld, 0x19);
	fcn_00487470(bld);
	hit = 0;
	if (g_7f4c04 != 8 && g_7f4c04 != 0xd) {
		for (i = 0; i < g_100b0ac; i++) {
			rec = &((PRODUCTION_GOODS_RECORD*) g_100d0c0)[i];
			if (rec->goods_id != (int) bld->id)
				continue;
			goods = ((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[rec->goods_id]);
			if ((int) ((OBJECT_PROTOTYPE *)goods)->value_036 <= rec->unk_40 &&
			    fcn_00486640(bld, rec, 1)) {
				rec->flags = rec->flags | 8;
				fcn_004868d0(bld, rec);
				bld->id = (unsigned short) rec->goods_id;
				hit = 1;
			}
			break;
		}
		bld->f1b4 = bld->f1b4 & 0xfffffeff;
		if (hit)
			goto done;
	}
	else if (bld->f1b4 & 0x100) {
		if (bld->id != 0) {
			for (i = 0; i < g_100b0ac; i++) {
				rec = &((PRODUCTION_GOODS_RECORD*) g_100d0c0)[i];
				if (rec->goods_id != (int) bld->id)
					continue;
				goods = ((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[rec->goods_id]);
				if ((int) ((OBJECT_PROTOTYPE *)goods)->value_036 <= rec->unk_40 &&
				    fcn_00486640(bld, rec, 1)) {
					rec->flags = rec->flags | 8;
					fcn_004868d0(bld, rec);
					bld->id = (unsigned short) rec->goods_id;
					goto done;
				}
				break;
			}
		}
	}
	else {
		bld->id = 0;
		bld->f1b4 = bld->f1b4 | 0x100;
	}
pick:
	if (*(unsigned char*) (((char*)&((ENTITY_RECORD_VIEW*)g_7f4ca0)[*(unsigned short*) (bld->x16c + 0x27)]) + 2) == 6) {
		n = fcn_005b1e40(bld->x16c);
		if (n != 0) {
			for (rec = (PRODUCTION_GOODS_RECORD*) g_100d0c0; (char*) rec < (char*) g_100d0c0 + 0xb00; rec = (PRODUCTION_GOODS_RECORD*) ((char*) rec + 0x58)) {
				if (rec->goods_id != n)
					continue;
				goods = ((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[rec->goods_id]);
				if ((int) ((Craft*) craft)->x1c < rec->min_1)
					break;
				if ((int) ((Craft*) craft)->x1d < rec->min_2)
					break;
				if (rec->unk_40 < (int) ((OBJECT_PROTOTYPE *)goods)->value_036)
					break;
				n = fcn_00503d10(rec->goods_id);
				if (n == 0)
					break;
				if ((int) ((unsigned short) ((OBJECT_PROTOTYPE *)goods)->value_036 + rec->unk_3c) <= gm_eval_SlotVoll(n, rec->goods_id, 1000000)) {
					if (fcn_00486640(bld, rec, 1)) {
						rec->flags = rec->flags | 8;
						fcn_004868d0(bld, rec);
						bld->id = (unsigned short) rec->goods_id;
						fcn_0064d41a(name, "Produktion von %s starten, da Humanplayer es so will.", goods + 1);
						goto done;
					}
					if (fcn_00486640(bld, rec, 0)) {
						fcn_004868d0(bld, rec);
						bld->id = (unsigned short) rec->goods_id;
						fcn_0064d41a(name, "Produktion von %s starten obwohl Rohstoffe fehlen, da der spieler es so will", goods + 1);
						goto done;
					}
				}
				break;
			}
		}
	}
	for (i = 0; i < 0x20; i++)
		order[i] = i;
	for (i = 0; i < 0x20; i++) {
		r = gm_RandomMod(0x20) & 0xffff;
		j = order[i];
		order[i] = order[r];
		order[r] = j;
	}
	for (i = 0; i < g_100b0ac; i++) {
		rec = &((PRODUCTION_GOODS_RECORD*) g_100d0c0)[order[i]];
		goods = ((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[rec->goods_id]);
		if ((((OBJECT_PROTOTYPE *)goods)->kind == 0x17 || ((OBJECT_PROTOTYPE *)goods)->kind == 0x25) && rec->unk_3c >= 5)
			continue;
		if ((int) ((Craft*) craft)->x1c < rec->min_1)
			continue;
		if ((int) ((Craft*) craft)->x1d < rec->min_2)
			continue;
		if (rec->unk_40 < (int) ((OBJECT_PROTOTYPE *)goods)->value_036)
			continue;
		n = fcn_00503d10(rec->goods_id);
		if (n == 0)
			continue;
		if ((int) ((unsigned short) ((OBJECT_PROTOTYPE *)goods)->value_036 + rec->unk_3c) > gm_eval_SlotVoll(n, rec->goods_id, 1000000))
			continue;
		if (!fcn_00486640(bld, rec, 1))
			continue;
		rec = &((PRODUCTION_GOODS_RECORD*) g_100d0c0)[order[i]];
		rec->flags = rec->flags | 8;
		fcn_004868d0(bld, rec);
		bld->id = (unsigned short) rec->goods_id;
		fcn_0064d41a(name, "Produktion von %s starten", goods + 1);
		goto done;
	}
	for (i = 0; i < g_100b0ac; i++) {
		rec = &((PRODUCTION_GOODS_RECORD*) g_100d0c0)[order[i]];
		goods = ((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[rec->goods_id]);
		if ((((OBJECT_PROTOTYPE *)goods)->kind == 0x17 || ((OBJECT_PROTOTYPE *)goods)->kind == 0x25) && rec->unk_3c >= 5)
			continue;
		if ((int) ((Craft*) craft)->x1c < rec->min_1)
			continue;
		if ((int) ((Craft*) craft)->x1d < rec->min_2)
			continue;
		if (rec->unk_40 < (int) ((OBJECT_PROTOTYPE *)goods)->value_036)
			continue;
		n = fcn_00503d10(rec->goods_id);
		if (n == 0)
			continue;
		if ((int) ((unsigned short) ((OBJECT_PROTOTYPE *)goods)->value_036 + rec->unk_3c) > gm_eval_SlotVoll(n, rec->goods_id, 1000000))
			continue;
		if (!fcn_00486640(bld, rec, 0))
			continue;
		fcn_004868d0(bld, rec);
		bld->id = (unsigned short) rec->goods_id;
		fcn_0064d41a(name, "Produktion von %s starten obwohl Rohstoffe fehlen", goods + 1);
		goto done;
	}
	bld->id = 0;
done:
	fcn_0047e220(craft);
	fcn_0047e0e0(bld, craft);
	if (g_100dc20 == bld->x16c && g_100dc38 < 4) {
		i = 0;
		while (i < g_100b0ac) {
			rec = &((PRODUCTION_GOODS_RECORD*) g_100d0c0)[i];
			((PRODUCTION_GOODS_RECORD*) g_100dc60)[g_100dc38] = *rec;
			for (j = 0; j < 4; j++) {
				if (rec->building_indices[j] >= 0) {
					n = *(int*) (g_100dc40 + g_100dc38 * 4);
					memcpy(g_100df20 + (n + g_100dc38 * 4) * 0x40, &g_100b0c0[rec->building_indices[j]], 0x40);
					*(int*) (g_100dc40 + g_100dc38 * 4) = *(int*) (g_100dc40 + g_100dc38 * 4) + 1;
				}
			}
			g_100dc38 = g_100dc38 + 1;
			i = i + 1;
			if (g_100dc38 >= 4)
				break;
		}
	}
	fcn_00487e60(bld, 4);
	put.count = 0;
	for (n = 0x7f4ca2; n < 0x85a0a2; n += (int)sizeof(ENTITY_RECORD)) {
		if (*(unsigned char*) (n + 6) == 0)
			continue;
		if (*(unsigned short*) (n - 2) == 0xffff)
			continue;
		if (*(unsigned char*) n == 0xa)
			continue;
		if (*(int*) (n + 0x16a) != bld->x16c)
			continue;
		if (*(unsigned char*) (n + 0x163) == 0)
			continue;
		if (*(int*) (n + 0x182) == 0)
			continue;
		if (*(int*) (*(int*) (n + 0x182) + 0x2c) != *(int*) (*(int*) (n + 0x16a) + 1))
			continue;
		fcn_00529160(bld->x16c, 0, (int) *(unsigned short*) (n - 2), 0);
		put.count = put.count + 1;
	}
	if (g_100dc20 == bld->x16c)
		g_100dc34 = put.count;
	put.flags = 0;
	if (g_100b0ac > 0) {
		for (i = 0; i < g_100b0ac; i++) {
			rec = &((PRODUCTION_GOODS_RECORD*) g_100d0c0)[i];
			if (rec->flags & 8)
				put.flags = put.flags + 1;
			if (rec->flags & 0x10)
				put.flags = put.flags + 1;
		}
	}
	if (put.flags >= put.count)
		put.flags = put.count;
	if (put.count != 0 && put.flags != 0 && g_100b0ac > 0) {
		put.bld = (int) bld;
		put.craft = craft;
		put.x10 = 0;
		put.x20 = 0;
		put.x1c = 0;
		i = 0;
		for (; i < g_100b0ac; i++) {
			rec = &((PRODUCTION_GOODS_RECORD*) g_100d0c0)[i];
			if (rec->flags & 8) {
				put.kind = 4;
				put.rec = (int) rec;
				fcn_00487f90(&put);
			}
			else
				continue;
			if (g_100dc20 == bld->x16c && g_100dc3c < 4) {
				((PRODUCTION_GOODS_RECORD*) g_100ddc0)[g_100dc3c] = *(PRODUCTION_GOODS_RECORD*) put.rec;
				g_100dc3c = g_100dc3c + 1;
			}
		}
	}
	ai_MeisterCollectTrans(bld);
	ai_MeisterTrade(bld, craft);
}
unsigned char _dpad_100dc40[736];
