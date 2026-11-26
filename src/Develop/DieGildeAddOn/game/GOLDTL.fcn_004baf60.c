extern double g_664e78;
extern double g_664e78;
extern float g_662cf8;
extern float g_662cf8;
/* Owned (both targets) by src/GOLDTL.fcn_004b6f00.c. */
#include "Develop/DieGildeAddOn/game/game_data.h"

#include <string.h>

int __cdecl gm_RandomMod(int);
void* __cdecl gm_LookupEntityRecordById(int);
int __cdecl gm_HasActiveSpecialObject(void*, int);
int __cdecl gm_DeductRandomBuildingGood(void*, int*, float);
void* __cdecl gm_StartFilteredEntitySearch(int, int, int);
void __cdecl io_FormatTextBuffer(void*, int, int, void*);
void __cdecl he_MessageBoxQuickjump(int, int, void*, int, int, int, int, int, void*);


/* ADDRESS: GOLD 0x004bab90 */
/* ADDRESS: GOLDTL 0x004baf60 */
int __cdecl gm_NotifyEntityEventTarget(void* request)
{
	float scale;
	int target_id;
	char buf[0x200];
	int roll;
	unsigned char* entity;
	void* target;
	int scaled_val;
	unsigned int len;

	roll = gm_RandomMod(0x14) & 0xffff;
	scale = (float) (((double) roll + g_664e78) * 0.01);
	entity = gm_LookupEntityRecordById(*(int*) request);
	if (entity == 0) {
		return 1;
	}
	if (gm_HasActiveSpecialObject(entity, 0x290) == 0) {
		if (gm_DeductRandomBuildingGood(entity, &target_id, scale) != 0) {
			target = gm_StartFilteredEntitySearch(1, 1, target_id);
			if (target != 0) {
				float cur_scale;

				cur_scale = scale;
				scaled_val = (int) (cur_scale * g_662cf8);
				io_FormatTextBuffer(buf, *(unsigned short*) ((char*) request + 4) + 0x12e7, scaled_val, target);
				len = strlen(buf);
				he_MessageBoxQuickjump(*(int*) ((char*) entity + 4), *(int*) ((char*) entity + 4),
				    buf, 0x100 < len, 0x603, *(int*) ((char*) target + 1), -1, 0, 0);
				return 0;
			}
		}
	}
	return 0x400;
}
