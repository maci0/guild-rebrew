#include "Develop/DieGildeAddOn/game/object_prototype.h"


#pragma pack(2)
// SIZE 0xe
struct pos14 {
	int a;
	int b;
	int c;
	short d;
};
#pragma pack()

#pragma pack(1)
// SIZE 0x41
struct rec {
	char pad0[0x22];
	unsigned int base;
	char pad26[0x1b];
};
#pragma pack()

// SIZE 0x21c
struct house {
	unsigned short id;
	unsigned char type;
	char pad3;
	int handle;
	char pad8[0x174];
	char* who;
	char pad180[0x9c];
};

#include "Develop/DieGildeAddOn/game/entity_record.h"
extern char* lpObjektePROT;

char* __cdecl gm_SearchTable67(int);
void __cdecl io_FormatTextBuffer(char*, char*, ...);
void __cdecl gm_AddTime(struct pos14*, int, int, int);
void __cdecl he_AssignActionSlot(char*, int, int, char*);
float __cdecl gm_CalcAvgEntityFavor(int, int, char*);

void __cdecl he_AllocProduktion(char* e)
{
	char buf[0x200];
	char* g;
	char* r;
	float v;
	int i;

	if (*(unsigned short*) (e + 8) == 0xffff) {
		g = gm_SearchTable67(*(int*) (e + 0xbc));
		if (g != 0) {
			io_FormatTextBuffer(buf, "he_AllocProduktion(): geb:%G", g);
		}
	}
	r = gm_SearchTable67(*(int*) (e + 0xbc));
	v = (float) ((OBJECT_PROTOTYPE*)lpObjektePROT)[*(unsigned short*) (e + 0xac)].value_022;
	*(struct pos14*) (e + 0x52) = *(struct pos14*) (e + 0x44);
	*(struct pos14*) (e + 0x60) = *(struct pos14*) (e + 0x44);
	*(float*) (e + 0xb4) = v;
	*(float*) (e + 0xb8) = v;
	gm_AddTime((struct pos14*) (e + 0x52), 0, 0, 1);
	*(int*) (e + 0xc4) = -1;
	*(int*) (e + 0xc8) = 0;
	for (i = 0; i < 768; i++) {
		if ((*(char**)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].ptr_17c) == e) {
			he_AssignActionSlot(r, 0, (*(unsigned short*)&((ENTITY_RECORD_VIEW*)gm_EntitySlotTable)[i].entity_index), e);
		}
	}
	*(float*) (e + 0xcc) = (gm_CalcAvgEntityFavor(*(unsigned short*) (e + 8), 8, e + 0x8c) - 0.5) * 0.25;
	*(float*) (e + 0xd4) = 1.0f;

}
