


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
extern __int64 gm_TargetPersonTypeMask;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d2_OpenTargetPicker(Desc*, int, int, void*);
void __cdecl d2_RunStraftatAccuseDialog(void);

/* ADDRESS: GOLDDE 0x005a2e70 */
void __cdecl d2_OpenStraftatAccusePicker(void)
{
	Desc d;

	memset(&d, 0, sizeof(d));
	d.flags = 0x400;
	d.w = (*(int*)&gm_TargetPersonTypeMask);
	d.caps = 6;
	d.h = g_66601c;
	d2_OpenTargetPicker(&d, g_14ab080, 0, d2_RunStraftatAccuseDialog);
}
