extern char gm_EntitySlotTable[];
extern char gm_EntityIdField[];
extern unsigned char gm_ActiveTownIndex;
#include "Develop/DieGildeAddOn/game/entity_record.h"
unsigned short __cdecl gm_RandomMod(int n);
int __cdecl io_FormatTextBuffer(char* dst, int id, ...);
int __cdecl he_PostEntityMessage(int id, int arg, char* text1, unsigned char flags, int value, char* text2);
void __cdecl cm_RequestMoveCredits(int a1, int a2, char a3, int a4);
int __cdecl he_FreeAction(char* entity);

/* ADDRESS: GOLDTL 0x00550be0 */
/* ADDRESS: GOLDDE 0x00537010 */
void __cdecl he_RunGambleBet(char* entity)
{
	char buf[0x418];

	if (*(int*) (entity + 0x70) == -2)
		goto done;
	if (*(int*) (entity + 0x70) != 0)
		return;
	if (*(unsigned char*) (entity + 0xac) > 0) {
		*(unsigned char*) (entity + 0xac) = *(unsigned char*) (entity + 0xac) - 1;
		return;
	}
	if ((double) (gm_RandomMod(0x100) & 0xffff) <
	    (double) (((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (entity + 8)].unk_07c[4]) *
	        0.5 + 64.0) {

		io_FormatTextBuffer(buf, 0x10b5, *(unsigned int*) (entity + 0xb0) * 2);
		he_PostEntityMessage(((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (entity + 8)].entity_id,
		             ((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (entity + 8)].entity_id,
		             buf, 0, 0x5ff, 0);
		cm_RequestMoveCredits(((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (entity + 8)].entity_id,
		             -1, gm_ActiveTownIndex, *(unsigned int*) (entity + 0xb0) * 2);
	} else {		io_FormatTextBuffer(buf, 0x10b6,
		             (int) (*(unsigned int*) (entity + 0xb0) * 0.5f));
		he_PostEntityMessage(((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (entity + 8)].entity_id,
		             ((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (entity + 8)].entity_id,
		             buf, 0, 0x5ff, 0);
		cm_RequestMoveCredits(((ENTITY_RECORD*)gm_EntitySlotTable)[*(unsigned short*) (entity + 8)].entity_id,
		             -1, gm_ActiveTownIndex,
		             (int) (*(unsigned int*) (entity + 0xb0) * 0.5f));
	}
done:
	he_FreeAction(entity);
}
