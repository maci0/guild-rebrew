#include "Develop/Units/d3/d3_object.h"



#include "client_types.h"
typedef Slot170_7731b8 Slot170;
// SIZE 0x170

extern int g_6b8010;
extern Slot170_7731b8 g_7731b8[8];

void __cdecl fcn_004432d0(int, int);


void __cdecl fcn_004efcd0(void)
{
	int save;
	int i;
	int j;

	save = g_6b8010;
	fcn_004432d0(0, 1);
	for (i = 0; i < 8; i++) {
		for (j = 0; j < 3; j++) {
			if (g_7731b8[i].h[j] != 0) {
				d3_DestroyObject((D3_OBJECT*) (g_7731b8[i].h[j]));
				g_7731b8[i].h[j] = 0;
			}
		}
	}
	fcn_004432d0(save, 1);
}
