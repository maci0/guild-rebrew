#include "Develop/DieGildeAddOn/game/game_data.h"
extern char cm_LastBuildingId[];
extern char gm_EntitySlotTable[];
#include "Develop/DieGildeAddOn/game/entity_record.h"
// SIZE 0x30
typedef struct {
	int d[12];
} copy_12_dwords;

int __cdecl cm_ResolveSpecialEntityId(char*, int);
char* __cdecl gm_AllocGebaeude(unsigned char, int);


/* ADDRESS: GOLD 0x004c6b20 */
/* ADDRESS: GOLDTL 0x004c76c0 */
/* ADDRESS: GOLDDE 0x004b4ea0 */
int __cdecl cm_CreateGebaeude(int cmd, char* result)
{
	char* building;
	int field_id;
	int i;

	if (nt_ClientSocket != -1)
		gm_NextEntityId = *(int*) (cmd + 0x10);
	if (*(int*) (cmd + 0x16) == -1) {
		i = 0xffff;
	}
	else {
		field_id = cm_ResolveSpecialEntityId((char*) cmd, *(int*) (cmd + 0x16));
		*(int*) (cmd + 0x16) = field_id;
		i = 0;
		while ((unsigned short) i < 0x300) {
			if (*(unsigned short*) ((unsigned char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[(unsigned int)(unsigned short)i]) != (unsigned short) 0xffff &&
				*(int*) ((unsigned char*)&((ENTITY_RECORD*)gm_EntitySlotTable)[(unsigned int)(unsigned short)i] + 4) == field_id) {
				break;
			}
			i = i + 1;
		}
		if ((unsigned short) i >= 0x300)
			return 1;
	}
	building = gm_AllocGebaeude(*(unsigned char*) (cmd + 0x14), i);
	if (building == (char*) 0)
		return 1;
	(*(int*)cm_LastBuildingId) = *(int*) (building + 1);
	*(unsigned short*) (building + 0x5a) = *(unsigned short*) (cmd + 0x1a);
	if (*(int*) (cmd + 0x1c) != 0) {
		*(copy_12_dwords*) (building + 0x65) = *(copy_12_dwords*) (cmd + 0x20);
	}
	if (result != (char*) 0) {
		*result = '\x01';
		result[1] = '\x02';
		*(char**) (result + 6) = building;
	}
	return 0;
}
