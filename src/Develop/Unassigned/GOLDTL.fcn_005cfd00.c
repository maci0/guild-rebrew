/* Checks that an entity action is allowed: matches the action's class masks
 * against the entity type table and filters the action's entity-id selector. */

#include "Develop/DieGildeAddOn/game/building_prototype.h"
extern unsigned char* lpGebaeudePROT;
extern char* gm_CityEntity;
#define g_action_class_lo (*(unsigned int*) 0x666030)
#define g_action_class_hi (*(unsigned int*) 0x666034)

/* ADDRESS: GOLDTL 0x005cfd00 */
int __cdecl fcn_005cfd00(unsigned short* self, int* action, unsigned char* entity)
{
	unsigned char type;
	unsigned int lo;
	unsigned int hi;
	unsigned int masks;
	unsigned int other;
	int match;
	int allow;
	int unlisted;
	int i;
	unsigned short ent_id;

	if (action == 0) {
		return 1;
	}
	if (entity == 0) {
		return 0;
	}
	if (self == 0) {
		return 0;
	}
	masks = (unsigned int) action[2];
	if (masks == 0 && action[4] == 0) {
		return 1;
	}
	type = ((BUILDING_PROTOTYPE*) lpGebaeudePROT)[entity[0]].category;
	lo = 0;
	hi = 0;
	if (type > 0x1f) {
		hi = 1 << (type - 0x20);
	} else {
		lo = 1 << type;
	}
	if ((g_action_class_lo & lo) || (g_action_class_hi & hi)) {
		if (action[3] & 0x40000000) {
			return 0;
		}
	}
	match = 0;
	allow = 0;
	unlisted = 1;
	other = (unsigned int) action[3];
	if ((other & 0x80000000) && (entity[0x5a] & 1)) {
		return 0;
	}
	if ((masks == 0 && other == 0) || (masks & lo) || (other & hi)) {
		match = 1;
	}
	if (action[4] == 0) {
		allow = 1;
	} else {
		/* case 0 is unreachable here; the reference dispatch table still
		 * carries its entry, so the compiler's peeled test is reproduced. */
		switch (action[4]) {
		case 0:
			allow = 1;
			break;
		case 1:
			allow = (*(unsigned short*) (entity + 0x27) == 0xffff);
			break;
		case 2:
			allow = (*(unsigned short*) (entity + 0x27) != 0xffff);
			break;
		case 3:
			allow = (*(unsigned short*) (entity + 0x27) == *self
			    || *(unsigned short*) (entity + 0x27) == 0xffff);
			break;
		case 4:
			allow = (*(unsigned short*) (entity + 0x27) == *self);
			break;
		case 5:
			allow = (*(unsigned short*) (entity + 0x27) != *self);
			break;
		case 6:
			allow = (*(unsigned short*) (entity + 0x27) != *self
			    && *(unsigned short*) (entity + 0x27) != 0xffff);
			break;
		case 7:
			allow = (*(unsigned short*) (entity + 0x27) != *self
			    && *(unsigned short*) (entity + 0x27) != *(unsigned short*) gm_CityEntity
			    && *(unsigned short*) (entity + 0x27) != 0xffff);
			break;
		}
	}
	if ((action[5] & 1) && *(unsigned short*) (entity + 0x27) != 0xffff) {
		ent_id = *(unsigned short*) (entity + 0x27);
		for (i = 0; i < 4; i++) {
			if (ent_id == *(unsigned short*) ((char*) action + 0x1c + i * 2)) {
				if (*(unsigned short*) ((char*) action + 0x1c + i * 2) != 0xffff) {
					unlisted = 0;
					break;
				}
			}
		}
	}
	return (match && allow && unlisted) ? 1 : 0;
}
