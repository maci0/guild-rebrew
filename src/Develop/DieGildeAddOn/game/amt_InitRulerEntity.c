

#include <string.h>

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"







// SIZE 0x1d0
typedef struct {
	unsigned short id;
	unsigned char state;
	char pad3;
	int handle;
	char pad8[2];
	unsigned short owner;
	unsigned char bc;
	unsigned char bd;
	char pade[2];
	float f10;
	float f14;
	float f18;
	float f1c;
	float f20;
	char pad24[0x0c];
	char name[0x10];
	char title[0x10];
	unsigned short w50;
	char pad52[6];
	unsigned char b58;
	char pad59[3];
	int f5c[8];
	int f7c;
	unsigned char b80[5];
	char pad85[0x16c - 0x85];
	int f16c;
	int f170;
	char pad174[0x18c - 0x174];
	int f18c;
	char pad190[0x1cc - 0x190];
	int flags;
} RULER_ENTITY;

#include "Develop/DieGildeAddOn/game/game_matrices.h"
#include "Develop/DieGildeAddOn/game/game_data.h"
extern unsigned char gm_ActiveTownIndex;

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl amt_SetType26OfficeHolder(int);
void __cdecl amt_SetOfficeType0x27Handle(int);
unsigned short __cdecl gm_RandomMod(int);
void __cdecl gm_AddObjekt(int a, int b, int c);
char* __cdecl gm_LookupHistoricalEntry(int, int*);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);
int __cdecl gm_PickRandomType26HeadPortrait(void);
int __cdecl gm_PickRandomHeadPortrait(void);
void __cdecl gm_AdvanceRulerHistoricalEntry(void);
void __cdecl gm_AdvanceHistoricalEntry(void);

void __cdecl amt_InitRulerEntity(int mode, int unused, unsigned short owner, RULER_ENTITY* g)
{
	char buf[0x100];
	char* p;
	unsigned short k;
	int i;
	int j;

	if (mode == 0x15) {
		g->flags |= 0x1000;
		amt_SetType26OfficeHolder(g->handle);
	} else {
		g->flags |= 0x2000;
		amt_SetOfficeType0x27Handle(g->handle);
	}
	g->owner = owner;
	g->bc = 0;
	for (i = 0; i < 0x300; i++) {
		for (j = 0; j < 0x300; j++) {
			gm_EntityRelationMatrix[i][j] = gm_RandomMod(0x40) - 0x20;
			gm_RelationDeltaMatrix[i][j] = 0;
		}
	}
	g->w50 = 0x7fff;
	g->f7c = 0;
	g->b58 = 0;
	for (i = 0; i < 8; i++) {
		g->f5c[i] = -1;
	}
	g->f170 = 0;
	g->f16c = 0;
	g->f1c = 1000.0f;
	g->f14 = 1.0f;
	g->f20 = 12.0f;
	g->f10 = 330.0f;
	g->f18 = 1000.0f;
	for (i = 0; i < 5; i++) {
		g->b80[i] = (unsigned char) (gm_RandomMod(0x2a) + 210.0f);
	}
	g->bd = 9;
	gm_AddObjekt(g->handle, *(unsigned short*) (g_8680b4 + gm_ActiveTownIndex * 0x2f4), 16000000);
	k = 0xffff;
	for (i = 0; i < 768 && k == 0xffff; i++) {
		if (((ENTITY_RECORD*)gm_EntitySlotTable)[i].entity_state == 6) {
			k = i;
		}
	}
	{
		int tmp;

		if (mode == 0x15) {
			p = gm_LookupHistoricalEntry(g_7728cc, &tmp);
		} else {
			p = gm_LookupHistoricalEntry(g_7728c4, &tmp);
		}
	}
	strcpy(g->name, p + 0xc);
	strcpy(g->title, p + 0x1c);
	if (mode == 0x15) {
		if ((*(int*)&gm_GameTime) > 0 && k != 0xffff) {
			io_FormatTextBuffer(buf, 0x42b3, g->id);
			he_PostEntityMessage(((ENTITY_RECORD*)gm_EntitySlotTable)[k].entity_id, -1, buf, 0, 0x602, "_NACHRICHTEN_NEU_01");
		}
		g->f18c = gm_PickRandomType26HeadPortrait();
		gm_AdvanceRulerHistoricalEntry();
	} else {
		if ((*(int*)&gm_GameTime) > 0 && k != 0xffff) {
			io_FormatTextBuffer(buf, 0x42b5, g->id);
			he_PostEntityMessage(((ENTITY_RECORD*)gm_EntitySlotTable)[k].entity_id, -1, buf, 0, 0x602, "_NACHRICHTEN_NEU_03");
		}
		g->f18c = gm_PickRandomHeadPortrait();
		gm_AdvanceHistoricalEntry();
	}
	g->state = 3;
}
