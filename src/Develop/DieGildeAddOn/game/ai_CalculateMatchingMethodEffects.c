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

/* ADDRESS: GOLDTL 0x004a4550 */
int __cdecl ai_CalculateMatchingMethodEffects(float* s1, float* s2, int idx, Actor* e)
{
	AM_METHOD* t;
	float k;
	int found;
	int i;

	*s1 = 0;
	*s2 = 0;
	t = &g_1008540[idx];
	if (t->flags & e->flags) {
		k = 40.0f;
		found = 1;
	} else {
		k = 50.0f;
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
		*s1 += t->effects[i].type == e->kind ? t->effects[i].value / k * e->rate[t->effects[i].type].f : 0.0f;
		*s2 += t->other_effects[i].type == e->kind ? t->other_effects[i].value / k * e->rate[t->other_effects[i].type].f : 0.0f;
	}
	return found;
}
