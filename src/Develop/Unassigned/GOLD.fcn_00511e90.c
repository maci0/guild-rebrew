#include "Develop/DieGildeAddOn/game/game_data.h"
#include "Develop/DieGildeAddOn/game/building_prototype.h"
extern signed char g_76fa60[];
extern unsigned char* g_6f230c;

// SIZE 0x3e0
struct s_fd7ba0 {
	char name[0x3d5];
	char used;
	char pad[0xa];
};

extern struct s_fd7ba0 g_fd7ba0[];


/* Twin of GOLDTL 0x5155e0; the GOLD slot records are 0x3e0 bytes, not 0x3dc. */

#include <string.h>

int __cdecl fcn_00413160(void);
void __cdecl fcn_0050dc30(int);

int __cdecl fcn_00511e90(unsigned char* e)
{
	int k;
	int r;

	k = ((BUILDING_PROTOTYPE*)g_7e3f30)[*e].category;
	if (((signed char*)g_76fa60)[k] == -1) {
		if (e == g_6f230c || *e == 0x1e) {
			fcn_0050dc30(*e);
		} else {
			r = fcn_00413160();
			if (r == -1) {
				return r;
			}
			((signed char*)g_76fa60)[k] = (signed char) r;
			g_fd7ba0[r].used = 1;
			strcpy((char*)&g_fd7ba0[r],
				(char*)&((BUILDING_PROTOTYPE*)g_7e3f30)[*e] + 1);
		}
	}
	return ((signed char*)g_76fa60)[k];
}
