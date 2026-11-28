


// SIZE 0xc98
typedef struct {
	char name[0xc98];
} T426d00;

#include "Develop/DieGildeAddOn/game/game_data.h"
int __cdecl fcn_0065f220(char*, char*);

T426d00* __cdecl evt_FindScriptByName(char* name)
{
	int i;

	for (i = 0; i < 0x80; i++) {
		if (fcn_0065f220(((T426d00*)g_6b7e94)[i].name, name) == 0) {
			return &((T426d00*)g_6b7e94)[i];
		}
	}
	return 0;
}
