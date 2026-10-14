typedef struct
{
	char pad0[0xa];
	unsigned short id;
	char padc;
	char state;
	char pade[6];
	void* obj;
} fcn_004bceb0_Entry;
// SIZE 0x18

void __cdecl fcn_00442be0(void* obj);
#include "Develop/DieGildeAddOn/auxillary/plant.h"
void __cdecl fcn_004bd150(fcn_004bceb0_Entry* tab);

/* ADDRESS: GOLDTL 0x004bceb0 */
void __cdecl fcn_004bceb0(fcn_004bceb0_Entry* tab)
{
	unsigned char* r;
	int i;
	int id;
	char c;

	for (i = 0; i < 64; i++) {
		if (tab[i].state != -1) {
			if (tab[i].obj != 0) {
				fcn_00442be0(tab[i].obj);
				tab[i].obj = 0;
			}
			id = tab[i].id;
			r = (unsigned char*) plt_FindPlantInfo(id);
			if (r == 0)
				r = (unsigned char*) plt_FindPlantInfo(id);
			c = tab[i].state;
			if (c < r[0x44])
				tab[i].state = c + 1;
		}
	}
	fcn_004bd150(tab);
}
