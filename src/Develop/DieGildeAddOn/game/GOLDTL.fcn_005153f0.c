#include "Develop/DieGildeAddOn/game/spiel.h"



// SIZE 0x21c
typedef struct {
	short slot;
	unsigned char type;
	char pad3;
	int id;
	char pad8[0x21c - 8];
} Entity;

#pragma pack(push, 1)
// SIZE 0xa9
typedef struct {
	unsigned char office;
	int id;
	char pad5[0xa4];
} Player;

// SIZE 0x24d
typedef struct {
	unsigned char kind;
	char pad1[0x222];
	unsigned char level;
	char pad224[0x29];
} Office;
#pragma pack(pop)

extern char g_7f4ca0[];
extern unsigned char* lpGebaeudeINST;
extern unsigned char* lpGebaeudePROT;
#include "client_packet_builder.h"
extern unsigned char g_773d75;



void __cdecl fcn_004c4570(int, int, int, void*);
void __cdecl fcn_004c5360(void);
void __cdecl fcn_004c5f60(int, int, int);
int __cdecl fcn_004c6090(Player*, int, int, int);
int __cdecl fcn_004c51f0(int, int, int, int, char, int);

void __cdecl fcn_005153f0(void)
{
	int i;
	Entity* e;
	Player* p;

	e = ((Entity*)g_7f4ca0);
	for (i = 0; i < 0x300; i++) {
		if (e->type == 6) {
			break;
		}
		e++;
	}
	for (p = ((Player*)lpGebaeudeINST);; p++) {
		if (p->office == 0) {
			continue;
		}
		if (gm_GetBuildingTypeCategory(p->office) == 1 || gm_GetBuildingTypeCategory(p->office) == 4 || gm_GetBuildingTypeCategory(p->office) == 2
			|| ((Office*)lpGebaeudePROT)[p->office].kind == 0x13 || ((Office*)lpGebaeudePROT)[p->office].kind == 4
			|| ((Office*)lpGebaeudePROT)[p->office].kind == 0x10 || ((Office*)lpGebaeudePROT)[p->office].kind == 5
			|| ((Office*)lpGebaeudePROT)[p->office].kind == 9) {
			if (((Office*)lpGebaeudePROT)[p->office].kind != 0xb) {
				int value = 0xfa00;

				fcn_004c4510((char*) p, p->id);
				fcn_004c4570(4, 1, (char*) p - g_aed32c + 0x39, &value);
				fcn_004c5360();
				fcn_004c5f60(p->id, e->id, e->id);
				fcn_004c6090(p, 1, 0, ((Office*)lpGebaeudePROT)[p->office].level);
				fcn_004c51f0(p->id, -1, 0x135, 1, (*(char*)&g_773d75), 0);
			}
		}
	}
}
