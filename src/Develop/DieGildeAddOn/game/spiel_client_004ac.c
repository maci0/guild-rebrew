#define MAXV(a, b) ((a) < (b) ? (b) : (a))
#define MINV(a, b) ((b) < (a) ? (b) : (a))

void __cdecl gm_FindRichestEntity(short* a, int* b);
int __cdecl gm_AccumulateTyped2(unsigned short* e);
#include "Develop/DieGildeAddOn/game/spiel.h"
extern unsigned char gm_ActiveTownIndex;
#include "Develop/DieGildeAddOn/game/entity_record.h"

void __cdecl cm_RequestMoveCredits(int, int, unsigned char, int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
int* __cdecl gm_GetBardEventEntry(int);
unsigned short __cdecl gm_RandomMod(unsigned short);
#include "Develop/DieGildeAddOn/command/client_packet_builder.h"
void __cdecl cm_AppendPacketFieldValue(int, int, short, char*);
void __cdecl cm_RequestChangeAttribute(void);
void __cdecl cm_RequestCopyEntityData(int, int, int, int);

/* ADDRESS: GOLDTL 0x004ac320 */
int __cdecl gm_CalcBardPoemCost(unsigned short* e)
{
	short s;
	int n;
	int r;
	int x;

	gm_FindRichestEntity(&s, &n);
	r = gm_AccumulateTyped2(e);
	x = (int) MINV(MAXV(gm_WalkEntityChain(*e) * 500.0f / n, 1600.0f), 16000.0f);
	return r > x ? x : 0;
}

/* ADDRESS: GOLDTL 0x004ac410 */
void __cdecl gm_ApplyBardPoemEffect(unsigned char* entity, int a2, int a3)
{
	int* p;
	char c;
	int i;
	char* rec;

	cm_RequestMoveCredits(-1, *(int*) (entity + 4), gm_ActiveTownIndex, a2);
	cm_RequestChangeBits(*(int*) (entity + 4), 0x1c8, 4, 0x20000, 0);
	p = gm_GetBardEventEntry(a3);
	if (p == 0)
		return;
	if (p[0] == 0 && *(unsigned short*) (p + 1) <= 4) {
		c = gm_RandomMod(8) + 8;
		c = (char)(c < 252.0f - entity[*(unsigned short*) (p + 1) + 0x80] ? c : 252.0f - entity[*(unsigned short*) (p + 1) + 0x80]);
		cm_BeginPacketFieldDelta((char*) entity, *(int*) (entity + 4));
		cm_AppendPacketFieldValue(1, 1, *(unsigned short*) (p + 1) + 0x80, &c);
		cm_RequestChangeAttribute();
		return;
	}
	if (p[0] == 1) {
		for (i = 0; i < 768; i++) {
			rec = ((char*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i]);
			if (*(int*) (rec + 4) != *(int*) (entity + 4)
			    && gm_MapEntityStatRange(*(unsigned char*) (rec + 0x164)) == *(unsigned short*) (p + 1))
				cm_RequestCopyEntityData(*(int*) (entity + 4), *(int*) (rec + 4), gm_RandomMod(4) + 3, 0);
		}
	}
}
