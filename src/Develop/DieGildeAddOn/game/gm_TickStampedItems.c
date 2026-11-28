#include "Develop/DieGildeAddOn/game/client_data.h"
#include "Develop/DieGildeAddOn/game/game_player.h"
int __cdecl gm_GetElapsedMinutes(void*, void*);
unsigned short* __cdecl gm_QueryEntities(int, int, int);
int __cdecl gm_LookupSpecialObject(int);
unsigned short* __cdecl gm_NextEntityQueryMatch(void);
int __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl cm_RequestChangeBits(int, int, int, int, int);
int __cdecl gm_IsLocalSimEntity(char*);
void __cdecl cm_SendSellObjekt(int, int, int, int, int, int);
void __cdecl io_FormatTextBuffer(char*, int, int);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, char*);

extern char gm_EntitySlotTable[];
extern int g_775320;
extern int g_775324;
extern int g_775328;
extern unsigned short g_77532c;
extern int g_775330;
extern unsigned char gm_ActiveTownIndex;

/* Ages the transient scene objects of one 32-slot block of the object table:
 * each stamped object counts down, and expired ones are released with their
 * effect and sound. */

/* ADDRESS: GOLDTL 0x005c6310 */
void __cdecl gm_TickStampedItems(void)
{
	char text[0x400];
	unsigned short* item;
	char* rec;
	int off;
	int n;
	int stamp;
	int left;
	int obj;

	if (gm_LocalPlayerSlot >= 0x300) {
		return;
	}
	gm_GetElapsedMinutes((void*) 0x775320, &gm_GameTime);
	n = g_775330;
	off = n * 0x21c;
	for (; n < g_775330 + 0x20; n++) {
		if (off >= 0x65400) {
			break;
		}
		if (*(unsigned short*) (gm_EntitySlotTable + off) != 0xffff) {
			item = gm_QueryEntities(*(int*) (gm_EntitySlotTable + 376 + off), 1, 5);
			while (item != 0) {
				obj = gm_LookupSpecialObject(*item);
				if (obj != 0) {
					if (*(int*) (obj + 4) > 0) {
						rec = (char*) item;
						if (*(int*) (rec + 0x21) != 0) {
							stamp = gm_GetElapsedMinutes(rec + 0x2d, &gm_GameTime);
							left = *(int*) (rec + 0x1c) - stamp;
							*(int*) (rec + 0x1c) = left;
							*(pos14_7f4c00*) (rec + 0x2d) = gm_GameTime;
							if (left < 0) {
								*(int*) (rec + 0x21) = 0;
								if (*(char*) (gm_EntitySlotTable + 2 + off) == 6) {
									io_FormatTextBuffer(text, 0x1bc9, *item * 2 + 0x9a8);
									he_PostEntityMessage(*(int*) (gm_EntitySlotTable + 4 + off),
										-1, text, 0, 0x5ec, (char*) 0x6ac758);
								}
								if (*item == 0x178) {
									obj = gm_StartFilteredEntitySearch(1, 1, *(int*) (rec + 0x25));
									if (obj != 0) {
										cm_RequestChangeBits(*(int*) (obj + 1), 0x5a, 2, 0, 0x20);
									}
								}
								obj = gm_IsLocalSimEntity(gm_EntitySlotTable + off);
								if (obj != 0 && *(char*) (gm_EntitySlotTable + 2 + off) != 7) {
									cm_SendSellObjekt(-1, *(int*) (rec + 6), *item, 1,
										gm_ActiveTownIndex, 0);
								}
							}
						}
					} else if (*(int*) ((char*) item + 0x21) != 0) {
						*(int*) ((char*) item + 0x21) = 0;
					}
				}
				item = gm_NextEntityQueryMatch();
			}
		}
		off += 0x21c;
	}
	g_775320 = gm_GameTime.a;
	g_775324 = gm_GameTime.b;
	g_775328 = gm_GameTime.c;
	g_77532c = gm_GameTime.d;
	g_775330 = (n + 1) % 0x300;
}
