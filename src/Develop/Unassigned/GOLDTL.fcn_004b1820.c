


#include <string.h>

#include "Develop/DieGildeAddOn/game/game_timestamp.h"


// SIZE 0xe

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;
extern char g_7f4ca4[];

int __cdecl fcn_004ae170(int);
void __cdecl cm_SendCopyEntityData(void*);

int __cdecl hst_CmdSoeldnerMarodieren(void)
{
	GAME_TIMESTAMP st;
	char m[0xf8];
	int i;

	st = (*(GAME_TIMESTAMP*)&gm_GameTime);
	memset(m, 0, sizeof(m));
	*(int*) ((char*) &st + 6) = 0;
	for (i = 0; i < 0x300; i++) {
		if (fcn_004ae170(i) != 0) {
			memset(m, 0, sizeof(m));
			st.hour = i % 4 + 0xd;
			m[4] = 0x58;
			*(int*) (m + 8) = *(int*) (g_7f4ca4 + i * 0x21c);
			*(int*) (m + 0xc) = *(int*) (g_7f4ca4 + i * 0x21c);
			m[0x36] = 1;
			*(GAME_TIMESTAMP*) (m + 0x28) = st;
			cm_SendCopyEntityData(m);
		}
	}
	return 1;
}
