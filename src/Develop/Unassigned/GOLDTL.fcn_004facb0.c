

#include <string.h>

typedef struct
{
	int a;
	int b;
	int c;
	int d;
	int e;
} Hist14;
// SIZE 0x14

#include "client_types.h"
extern GRAPH_SAMPLE g_99ec20[16];
extern int g_99f5e4;
extern int g_99f5e8;
extern int g_99f5ec;
extern int g_99f604;
#include "Develop/DieGildeAddOn/game/game_data.h"
/* ADDRESS: GOLD 0x4f88c0 */

void __cdecl fcn_004facb0(void)
{
	memmove(((Hist14*)g_99ec20), ((Hist14*)g_99ec20) + 1, 15 * sizeof(Hist14));
	((Hist14*)g_99ec20)[15].a = g_99f5e4;
	((Hist14*)g_99ec20)[15].b = g_99f5e8;
	((Hist14*)g_99ec20)[15].c = g_99f5ec;
	((Hist14*)g_99ec20)[15].d = g_99f604;
	((Hist14*)g_99ec20)[15].e = (int) g_773d4c;
}
