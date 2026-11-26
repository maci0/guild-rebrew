#include "Develop/DieGildeAddOn/game/building_prototype.h"


#pragma pack(1)
// SIZE 0x24d
struct good {
	unsigned char kind;
	char pad[0x24c];
};
#pragma pack()

// SIZE 0x21c
#include "Develop/DieGildeAddOn/game/entity_record.h"







#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern unsigned char* lpGebaeudePROT;

extern unsigned char g_773d75;
extern char g_6b5c60[];
extern char g_6a65a4[];

unsigned short __cdecl gm_RandomMod(int);
void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);
unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl fcn_004c5420(int, int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, ...);
void __cdecl he_MessageBoxQuickjump(int, int, char*, int, int, int, int, char*, char*);
int __cdecl fcn_0050d270(int);
void __cdecl fcn_004c5150(int, int, unsigned char, int);
void __cdecl he_FreeAction(char*);

void __cdecl he_StartAction0x1b(char* u)
{
	struct BUILDING_PROTOTYPE * gd;
	char text[0x800];
	ENTITY_RECORD* h;
	unsigned char* e;
	int i;
	int v;

	h = 0;
	*(pos14_7f4c00*) (u + 0x52) = gm_GameTime;
	gm_AddTime((pos14_7f4c00*) (u + 0x52), gm_RandomMod(3) + 4, 0, 0);
	e = gm_StartFilteredEntitySearch(1, 1, *(int*) (u + 0xac));
	if (e != 0) {
		gd = &((struct BUILDING_PROTOTYPE *)lpGebaeudePROT)[*e];
		if (gd->category != 0xd && gd->category != 0xc && gd->category != 0xb) {
			fcn_004c5420(*(int*) (e + 1), 0x5a, 2, 2, 0);
			*(int*) (u + 0xb8) = 0;
			if (*(unsigned short*) (e + 0x25) != 0xffff) {
				h = &((ENTITY_RECORD*)g_7f4ca0)[*(unsigned short*) (e + 0x25)];
				if (h != 0 && (u[0x78] & 2) != 0 && *e != 0x27) {
					for (i = 0; i < 768; i++) {
						if ((((ENTITY_RECORD*)g_7f4ca0)[i].entity_state == 6 || ((ENTITY_RECORD*)g_7f4ca0)[i].entity_state == 7) && ((ENTITY_RECORD*)g_7f4ca0)[i].entity_id != h->entity_id) {
							io_FormatTextBuffer(text, 0x17f4, h->entity_index, e, *(int*) (u + 0xb0));
							he_MessageBoxQuickjump(((ENTITY_RECORD*)g_7f4ca0)[i].entity_id, -1, text, 0, 0x5ec, *(int*) (e + 1), -1, g_6b5c60, g_6a65a4);
						}
					}
				}
			}
			if (gd->category == 5 && h != 0 && h->entity_state != 6 && h->entity_state != 7) {
				v = fcn_0050d270(*(int*) (e + 0x5d));
				if (v != 0) {
					fcn_004c5150(h->entity_id, *(int*) (e + 1), g_773d75, v);
				}
			}
			*(int*) (u + 0x84) = -1;
			return;
		}
	}
	he_FreeAction(u);
}
