#include <string.h>

unsigned short* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_HasActiveSpecialObject(void*, int);
unsigned short __cdecl gm_RandomMod(unsigned short);
int __cdecl gm_DeductRandomBuildingGood(unsigned short*, int*, float);
char* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl io_FormatTextBuffer(void*, int, ...);
void __cdecl he_PostEntityMessage(int, int, char*, int, int, int);


/* ADDRESS: GOLDTL 0x004bad30 */
/* ADDRESS: GOLDDE 0x004a8dd0 */
int __cdecl gm_HandleMsg32DeductGood(int* request)
{
	float ratio;
	int id;
	char buf[0x200];
	unsigned short* entity;
	char* building;

	ratio = (float)((gm_RandomMod(0xd) + 13.0) * 0.01);
	entity = gm_LookupEntityRecordById(request[0]);
	if (entity == 0)
		return 1;
	if (gm_HasActiveSpecialObject(entity, 0x290) != 0)
		goto fail;
	if (gm_DeductRandomBuildingGood(entity, &id, ratio) == 0)
		goto fail;
	building = gm_StartFilteredEntitySearch(1, 1, id);
	if (building != 0) {
		io_FormatTextBuffer(buf, *(unsigned short*) (request + 1) + 0x12e7, building, (int) (ratio * 100.0f));
		he_PostEntityMessage(*(int*) (entity + 2), *(int*) (entity + 2), buf, strlen(buf) > 0x100, 0x603, 0);
		return 0;
	}
fail:
	return 0x400;
}
