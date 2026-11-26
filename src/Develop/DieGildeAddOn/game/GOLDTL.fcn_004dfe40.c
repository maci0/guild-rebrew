

typedef struct {
	char c[0x19];
} blk19;
// SIZE 0x19

extern blk19 g_68cb58;
#include "Develop/DieGildeAddOn/game/game_data.h"

double __cdecl gm_GetEntityHealthRatio(char*);
void __cdecl fcn_00417b50(char*, int, float, float, float, float);
#include "Develop/DieGildeAddOn/game/ch_queue.h"
char* __cdecl ch_CreateQueuedAction(char*, void*, int, int, int);
void __cdecl fcn_004dfd10(char*);

int __cdecl gm_CheckDuelKnockout(char* e)
{
	char* o;

	if (gm_GetEntityHealthRatio(e) < 0.2) {
		fcn_00417b50(*(char**) (*(char**) (e + 0x184) + 0x34), 0x40, 0.25f, 0.1f, 0.14f, 55.0f);
		ch_CancelActionQueue(*(char**) (e + 0x184));
		o = ch_CreateQueuedAction(*(char**) (e + 0x184), fcn_004dfd10, 0x12, 0x36, 1);
		*(blk19*) (o + 0xf0) = g_68cb58;
		*(int*) (*(char**) (*(char**) (e + 0x184) + 0x34) + 0x220) = 0;
		g_772f44 = 1;
		return 1;
	}
	return 0;
}
