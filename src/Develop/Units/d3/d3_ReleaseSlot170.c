


typedef struct
{
	int id;
	int flags;
	char pad[0x168];
} Slot170;
// SIZE 0x170

#include "Develop/client_types.h"
extern Slot170_7731b8 gm_CannonTowers[8];

/* ADDRESS: GOLDDE 0x004dccd0 */
int __cdecl d3_ReleaseSlot170(int id)
{
	int i;
	int j;

	if (id != -1) {
		for (i = 0; i < 8; i++) {
			if (((Slot170*)gm_CannonTowers)[i].id == id) {
				((Slot170*)gm_CannonTowers)[i].flags = 4;
				for (j = 0; j < 3; j++) {
					if (*(int*) ((char*) &((Slot170*)gm_CannonTowers)[i] + 0x74 + j * 0x68) != 0) {
						return 1;
					}
				}
				((Slot170*)gm_CannonTowers)[i].id = -1;
				((Slot170*)gm_CannonTowers)[i].flags = 0;
				return 1;
			}
		}
	}
	return 0;
}
