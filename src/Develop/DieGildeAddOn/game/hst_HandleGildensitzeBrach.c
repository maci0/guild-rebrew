#include <string.h>




// SIZE 0xe

#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern char* gm_CityEntity;

int __cdecl amt_FindOfficeSlotByType(int, void*);
#include "Develop/DieGildeAddOn/game/aemter.h"
int __cdecl atoi(char*);
void __cdecl cm_SendCopyEntityData(void*);

struct slot_4b11a0 {
	int kind;
	int id;
	int pad[4];
};
// SIZE 0x18


/* ADDRESS: GOLDTL 0x004b11a0 */
int __cdecl hst_HandleGildensitzeBrach(int unused1, int unused2, char* arg)
{
	struct slot_4b11a0 s;
	char m[0xf8];

	if (*arg != '-')
		return 0;
	if (amt_FindOfficeSlotByType(0x1e, &s) != 0 && s.id != -1)
		amt_SendOfficeCommand(s.kind, 0, 0, 4, 0xff);
	if (amt_FindOfficeSlotByType(0x1f, &s) != 0 && s.id != -1)
		amt_SendOfficeCommand(s.kind, 0, 0, 4, 0xff);
	if (amt_FindOfficeSlotByType(0x20, &s) != 0 && s.id != -1)
		amt_SendOfficeCommand(s.kind, 0, 0, 4, 0xff);
	if (amt_FindOfficeSlotByType(0x21, &s) != 0 && s.id != -1)
		amt_SendOfficeCommand(s.kind, 0, 0, 4, 0xff);
	atoi(arg + 1);
	memset(m, 0, sizeof(m));
	m[4] = (char) 0x80;
	*(int*) (m + 8) = *(int*) (gm_CityEntity + 4);
	*(int*) (m + 0xc) = -1;
	m[0x36] = 2;
	*(int*) (m + 0x58) = 4;
	*(pos14_7f4c00*) (m + 0x28) = (*(pos14_7f4c00*)&gm_GameTime);
	*(short*) (m + 0x2c) = 8;
	*(int*) (m + 0x2e) = 0;
	cm_SendCopyEntityData(m);
	return 1;
}
