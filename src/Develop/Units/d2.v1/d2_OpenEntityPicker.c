


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

extern __int64 gm_TargetPersonTypeMask;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d2_ShowTabbedSelectionDialog(Desc*, int, int, int);

void __cdecl d2_OpenEntityPicker(int unused, int title)
{
	Desc d;

	memset(&d, 0, sizeof(d));
	d.flags = 0x204;
	d.w = (*(int*)&gm_TargetPersonTypeMask);
	d.caps = 6;
	d.h = g_66601c;
	d2_ShowTabbedSelectionDialog(&d, title, 0, 0);
}
