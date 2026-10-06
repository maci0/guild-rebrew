// FUNCTION: GOLDTL 0x5016c0

typedef struct
{
	char used;
	char pad[0x2f3];
} Rec2f4;
// SIZE 0x2f4

extern char g_868060[];
#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

void __cdecl fcn_005020e0(int, char*);

void __cdecl fcn_005016c0(void)
{
	int i;

	for (i = 0; i < 4; i++) {
		if (((Rec2f4*)g_868060)[i].used == 0) {
			break;
		}
		fcn_005020e0(i, ((char*)&g_7f4c00));
	}
}
