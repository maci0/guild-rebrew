#include "client_types.h"
struct CUT_STATUS_SLOT {
	int f0;
	char* obj;
	unsigned char flag;
	char pad9[0x213];
};
// SIZE 0x21c

extern struct CUT_STATUS_SLOT g_9b4bc0[32];

void __cdecl d3_SetObjectColorRgb(char*, int, int, int);

void __cdecl d2_CloseAllEntityStatusPopups(void);
void __cdecl d2_DestroyHudForm(void);


/* ADDRESS: GOLDTL 0x004d1910 */
void __cdecl cut_ClearStatusOverlaySlots(void)
{
	int i;

	for (i = 0; i < 32; i++) {
		if (g_9b4bc0[i].flag != 0)
			g_9b4bc0[i].flag = 0;
		if (g_9b4bc0[i].obj != 0
		    && (*(unsigned char*) (*(char**) (g_9b4bc0[i].obj + 0x34) + 0x215) & 0x80) == 0x80)
			d3_SetObjectColorRgb(*(char**) (g_9b4bc0[i].obj + 0x34), 0, 0, 0);
	}
	ResetDisplayCounters();
	d2_CloseAllEntityStatusPopups();
	d2_DestroyHudForm();
}
