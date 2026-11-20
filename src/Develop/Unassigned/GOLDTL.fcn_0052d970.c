


extern char g_7f4ca0[];
#include "Develop/DieGildeAddOn/game/entity_record.h"
int __cdecl fcn_0065f220(const char*, const char*);
void __cdecl SelectTextureSet(char*, int, char, int);

char __cdecl fcn_0052d970(char* e, char* o)
{
	if (fcn_0065f220(e, "sp_WIMPEL") == 0 && *(unsigned short*) (o + 0x27) != 0xffff) {
		SelectTextureSet(e, *(int*) (e + 0x1cc),
		    *(char*) &((ENTITY_RECORD_VIEW*) g_7f4ca0)[*(unsigned short*) (o + 0x27)].value_054 + 0x66, 1);
	}
	return 1;
}
