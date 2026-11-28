#include "Develop/DieGildeAddOn/game/game_data.h"
extern int cm_LastEntityId;
extern char gm_EntitySlotTable[];

int __cdecl rand(void);
void __cdecl srv_SeedRandom(int);
unsigned short __cdecl gm_AllocClientSpieler(unsigned int, int, int, unsigned short, int, unsigned int, unsigned int, unsigned int);
char* __cdecl strncpy(char*, const char*, unsigned int);
#include "Develop/DieGildeAddOn/game/spiel.h"
char* __cdecl gm_LookupEntityRecordById(int);


/* ADDRESS: GOLDTL 0x004c7870 */
int __cdecl fcn_004c7870(int cmd, char* result)
{
	unsigned int entity;
	short* entry;
	char* r2;
	int off;

	{
		char* c = (char*) cmd;
		unsigned int kind;

		if (nt_ClientSocket != -1)
			gm_NextEntityId = *(int*) (c + 0x10);
		else
			*(int*) (c + 0x45) = rand();
		srv_SeedRandom(*(int*) (c + 0x22));
		if (result)
			kind = 6;
		else
			kind = 7;
		entity = gm_AllocClientSpieler(kind,
			*(int*) (c + 0x14), *(int*) (c + 0x18),
			*(unsigned short*) (c + 0x1c), 0,
			(unsigned char) *(char*) (c + 0x1e), 0,
			(unsigned char) *(char*) (c + 0x23));
	}
	entity = entity & 0xffff;
	if (entity == 0xffff)
		return 1;
	off = entity * 0x21c;
	cm_LastEntityId = *(int*) (gm_EntitySlotTable + off + 4);
	strncpy(gm_EntitySlotTable + off + 0x30, (char*) cmd + 0x25, 0x10);
	entry = gm_GetEntityTableEntry((char*) (gm_EntitySlotTable + off));
	if (entry != 0) {
		*(unsigned short*) entry = *(unsigned short*) (gm_EntitySlotTable + off + 0x50);
		strncpy((char*) entry + 2, (char*) cmd + 0x35, 0x10);
		strncpy(gm_EntitySlotTable + off + 0x40, (char*) cmd + 0x35, 0x10);
		r2 = gm_LookupEntityRecordById(*(int*) (gm_EntitySlotTable + off + 0x60));
		if (r2 != 0)
			strncpy(r2 + 0x40, (char*) cmd + 0x35, 0x10);
		*(float*) ((char*) entry + 0x88) = -1.0f;
	}
	*(int*) (gm_EntitySlotTable + off + 0x54) = *(int*) (cmd + 0x1f);
	*(unsigned char*) (gm_EntitySlotTable + off + 0xc) = *(unsigned char*) (cmd + 0x24);
	if (result != (char*) 0) {
		result[0] = 1;
		result[1] = 1;
		*(char**) (result + 6) = gm_EntitySlotTable + off;
	}
	return 0;
}
