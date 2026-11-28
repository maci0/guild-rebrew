#include "Develop/DieGildeAddOn/game/client_method_registry.h"















typedef struct Rate {
	float f;
	int x4;
	int x8;
} Rate;

typedef struct Actor {
	char pad0[0x90];
	Rate rate[13];
	char pad12c[4];
	unsigned char kind;
	char pad131[0x218 - 0x131];
	unsigned char flags;
} Actor;

extern AM_METHOD g_1008540[];

/* ADDRESS: GOLDTL 0x004a4410 */
int __cdecl ai_ComputeBaseActionScore(float* s1, float* s2, int idx, Actor* e)
{
	AM_METHOD* t;
	float k1;
	float k2;
	int found;
	int i;

	*s1 = 0;
	*s2 = 0;
	t = &g_1008540[idx];
	if (t->flags & e->flags) {
		k1 = 40.0f;
		k2 = 50.0f;
		found = 1;
	} else {
		k1 = 50.0f;
		k2 = 100.0f;
		found = 0;
	}
	for (i = 0; !found && i < 4; i++) {
		if (t->effects[i].type == e->kind && t->effects[i].value > 0.0f) {
			found = 1;
		}
	}
	for (i = 0; !found && i < 4; i++) {
		if (t->other_effects[i].type == e->kind && t->other_effects[i].value > 0.0f) {
			found = 1;
		}
	}
	for (i = 0; i < 4; i++) {
		*s1 += t->effects[i].type == e->kind ? t->effects[i].value / k1 * e->rate[t->effects[i].type].f : t->effects[i].value / k2 * e->rate[t->effects[i].type].f;
		*s2 += t->other_effects[i].type == e->kind ? t->other_effects[i].value / k1 * e->rate[t->other_effects[i].type].f : t->other_effects[i].value / k2 * e->rate[t->other_effects[i].type].f;
	}
	return found;
}
