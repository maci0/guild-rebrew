extern char g_7f4ca0[];
extern char g_7f4ca0[];
extern int g_774800;
extern int g_774800;
#include "Develop/DieGildeAddOn/game/entity_record.h"
/* ADDRESS: GOLD 0x004ce170 */
/* ADDRESS: GOLDTL 0x004cef70 */
int __cdecl gm_GetEntityControlMask(int entityIndex, char* entityRecord)
{
	int r;

	r = 0;
	if (*(int*) (entityRecord + 0x16c) == (int) (((char *)&((ENTITY_RECORD_VIEW *)g_7f4ca0)[entityIndex]))) {
		r = 0x800;
	}
	if (*(int*) ((char*)&g_774800) != 0) {
		r = 0x800;
	}
	return r;
}
