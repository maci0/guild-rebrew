


extern char g_7f4ca0[];
#include "Develop/DieGildeAddOn/game/entity_record.h"
int __cdecl fcn_0065f220(const char*, const char*);
void __cdecl SelectTextureSet(char*, int, char, int);

char __cdecl d3_ApplyWimpelTextureCallback(char* obj, char* building)
{
	if (fcn_0065f220(obj, "sp_WIMPEL") == 0 && *(unsigned short*) (building + 0x27) != 0xffff) {
		SelectTextureSet(obj, *(int*) (obj + 0x1cc),
		    *(char*) &((ENTITY_RECORD_VIEW*) g_7f4ca0)[*(unsigned short*) (building + 0x27)].value_054 + 0x66, 1);
	}
	return 1;
}
