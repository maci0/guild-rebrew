


#include "Develop/client_types.h"
extern pos14_7f4c00 gm_GameTime;

char* __cdecl gm_StartFilteredEntitySearch(int, ...);
char* __cdecl gm_QueryEntities(int, int, int, int, int);

int __cdecl cm_ChkClientElectionOrTrade(char* x)
{
	char* e;
	char* r;
	int i;

	if (*(int*) (x + 0x10) == 0x636c6572) {
		e = gm_StartFilteredEntitySearch(1, 1, *(int*) (x + 0x18));
		if (e == 0)
			return 1;
		r = gm_QueryEntities(*(int*) (e + 0x5d), 2, 6, 0, 0x12c);
		if (r == 0)
			return 1;
		return (*(int*)&gm_GameTime) - *(int*) (r + 0x28) <= 1;
	}
	if (*(int*) (x + 0x10) == 0x62757920) {
		e = gm_StartFilteredEntitySearch(1, 1, *(int*) (x + 0x18));
		if (e == 0)
			return 1;
		r = gm_QueryEntities(*(int*) (e + 0x5d), 2, 6, 0, 0x12c);
		if (r == 0)
			return 1;
		for (i = 0; i < 3; i++) {
			if (*(int*) (r + 0x1c + i * 4) == *(int*) (x + 0x1c))
				return 0;
		}
	}
	return 1;
}
