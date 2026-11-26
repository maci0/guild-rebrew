


#include <string.h>

// SIZE 0x50
typedef struct {
	int size;
	int flags;
	int w;
	int h;
	int caps;
	int rest[15];
} Desc;

extern int g_14ab080;
extern __int64 g_666018;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl fcn_005cd440(Desc*, int, int, void*);
void __cdecl fcn_005c06e0(void);

void __cdecl d2_OpenStraftatAccusePicker(void)
{
	Desc d;

	memset(&d, 0, sizeof(d));
	d.flags = 0x400;
	d.w = (*(int*)&g_666018);
	d.caps = 6;
	d.h = g_66601c;
	fcn_005cd440(&d, g_14ab080, 0, fcn_005c06e0);
}
