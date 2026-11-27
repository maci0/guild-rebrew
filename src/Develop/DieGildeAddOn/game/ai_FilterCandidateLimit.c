


#include "Develop/DieGildeAddOn/game/game_timestamp.h"






// SIZE 0xe


typedef struct {
	int f0;
	int f4;
	GAME_TIMESTAMP st;
} holder;
// SIZE 0x18

#include "client_types.h"
extern pos14_7f4c00 gm_GameTime;

void __cdecl sim_SetSyncParams(GAME_TIMESTAMP*, unsigned char, unsigned char, unsigned char);
int __cdecl gm_GetElapsedMinutes(GAME_TIMESTAMP*, GAME_TIMESTAMP*);

int __cdecl ai_FilterCandidateLimit(holder* p, int flag, int limit)
{
	if (flag != 0) {
		if (p->st.unit_0 == 0 && p->st.hour == 0 && p->st.minute == 0 && p->st.second == 0) {
			p->st.unit_0 = (*(GAME_TIMESTAMP*)&gm_GameTime).unit_0;
			sim_SetSyncParams(&p->st, (unsigned char) (*(GAME_TIMESTAMP*)&gm_GameTime).hour, (unsigned char) (*(GAME_TIMESTAMP*)&gm_GameTime).minute,
			    (unsigned char) (*(GAME_TIMESTAMP*)&gm_GameTime).second);
		}
		return gm_GetElapsedMinutes(&p->st, &(*(GAME_TIMESTAMP*)&gm_GameTime)) >= limit;
	}
	p->st.unit_0 = 0;
	sim_SetSyncParams(&p->st, 0, 0, 0);
	return 0;
}
