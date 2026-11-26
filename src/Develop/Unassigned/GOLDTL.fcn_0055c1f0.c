extern char* lpObjektePROT;
extern int g_774800;
#include "Develop/DieGildeAddOn/game/object_prototype.h"
#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;




void __cdecl gm_AddTime(pos14_7f4c00*, int, int, int);

void __cdecl fcn_0055c1f0(char* o)
{
	char* t;

	t = ((char *)&((OBJECT_PROTOTYPE *)lpObjektePROT)[*(unsigned short*) (o + 0xac)]);
	*(pos14_7f4c00*) (o + 0x52) = gm_GameTime;
	if (g_774800 != 0) {
		gm_AddTime((pos14_7f4c00*) (o + 0x52), 0, 0, 1);
	} else {
		gm_AddTime((pos14_7f4c00*) (o + 0x52), 0, *(int *)&((OBJECT_PROTOTYPE *)t)->value_022, 0);
	}
}
