

#define MIN(a, b) ((b) < (a) ? (b) : (a))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

typedef struct {
	unsigned short id;
	char pad2[0x2c - 2];
	unsigned int skills;
	char pad30[0x80 - 0x30];
	unsigned char level[5];
	char pad85[0x1cc - 0x85];
	unsigned int flags;
} Unit;
// SIZE 0x1d0

typedef struct {
	char pad0[0xac];
	unsigned char slot_a;
	unsigned char slot_b;
	char padae[2];
	float bonus_a;
	float bonus_b;
} Mod;
// SIZE 0xb8

Mod* __cdecl fcn_005463a0(int, int, int, ...);
Mod* __cdecl he_fn_Handlung(void);
int __cdecl fcn_005c6270(void*, int);
int __cdecl fcn_00577ab0(Unit*);

#include "Develop/DieGildeAddOn/game/spiel.h"

/* ADDRESS: GOLDTL 0x00507f10 */
float __cdecl gm_GetEntitySkill(char* entity, int skill_index)
{
	Unit* entity_view;
	float skill_value;
	float bonus;
	float penalty;
	Mod* modifier;

	entity_view = (Unit*) entity;
	penalty = 0.0f;
	if (entity_view == 0 || skill_index >= 5) {
		return -1.0f;
	}
	skill_value = entity_view->level[skill_index] * 0.003968254f;
	if (skill_index != 1) {
		bonus = 0.0f;
		for (modifier = fcn_005463a0(2, 2, entity_view->id, 0, 0x82); modifier != 0; modifier = he_fn_Handlung()) {
			if (modifier->slot_a == skill_index) {
				bonus += modifier->bonus_a;
			} else if (modifier->slot_b == skill_index) {
				bonus += modifier->bonus_b;
			}
		}
		if (fcn_005c6270(entity_view, 0x2c4) == 1) {
			bonus *= 0.5f;
		}
		skill_value += bonus;
	}
	if (skill_index == 3) {
		skill_value += fcn_005c6270(entity_view, 0x15a) * 0.16666667f;
	}
	switch (skill_index) {
	case 0:
		penalty = ((entity_view->skills >> 20) & 7) * 0.0555f + ((entity_view->skills >> 4) & 0xf) * 0.03333333432674408;
		break;
	case 1:
		penalty = ((entity_view->skills >> 8) & 0xf) * 0.03333333432674408;
		penalty += ((entity_view->skills >> 20) & 7) * 0.0555f;
		break;
	case 2:
		penalty = ((entity_view->skills >> 17) & 7) * 0.055500001654028894;
		penalty += ((entity_view->skills >> 25) & 0xf) * 0.03333333432674408;
		break;
	case 3:
		penalty = ((entity_view->skills >> 8) & 0xf) * 0.03333333432674408;
		penalty += ((entity_view->skills >> 25) & 0xf) * 0.03333333432674408;
		break;
	case 4:
		penalty = ((entity_view->skills >> 12) & 3) * 0.16666667f + ((entity_view->skills >> 4) & 0xf) * 0.03333333432674408;
		break;
	}
	skill_value -= penalty;
	if (skill_index == 4) {
		if (entity_view->flags & 0x400) {
			skill_value += 0.5f;
		}
	} else if (skill_index == 3) {
		if (entity_view->flags & 0x200) {
			skill_value += 0.5f;
		}
	} else if (skill_index == 2) {
		if (entity_view->flags & 0x800) {
			skill_value += 0.5f;
		}
	}
	skill_value = MAX(MIN(skill_value, 1.0f), 0.0f);
	if (fcn_00577ab0(entity_view) == 0) {
		if (fcn_005c6270(entity_view, 0x2c4) == 0) {
			return skill_value * 0.5f;
		}
		return skill_value * 0.75f;
	}
	return skill_value;
}
