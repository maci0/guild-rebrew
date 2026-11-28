extern int d3_ActiveScene;
extern volatile int gm_GameTicks;

// SIZE 0x10c
struct s_7e6060 {
	int a;
	int t;
	char* o;
	char name[0x100];
};

extern struct s_7e6060 g_7e6060[64];




#include <string.h>

void __cdecl d2_ClearHoverTooltipSlot(void);

void __cdecl d2_SetHoverTooltip(char* obj, int text_id, char* name)
{
	int i;
	int k;
	struct s_7e6060* slot;

	if (obj == 0) {
		return;
	}
	if (*(char**) (obj + 0x88) != ((char*)d3_ActiveScene)) {
		return;
	}
	for (i = 0; i < 64; i++) {
		if (g_7e6060[i].o == obj) {
			return;
		}
	}
	for (k = 0; k < 64; k++) {
		if (g_7e6060[k].o == 0) {
			break;
		}
	}
	if (k >= 64) {
		int now;

		now = gm_GameTicks;
		k = -1;
		for (i = 0; i < 64; i++) {
			if (g_7e6060[i].t < now) {
				k = i;
			}
		}
		if (k == -1) {
			return;
		}
	}
	slot = &g_7e6060[k];
	slot->t = gm_GameTicks;
	slot->o = obj;
	slot->a = text_id;
	*(void**) (obj + 0x228) = (void*) d2_ClearHoverTooltipSlot;
	if (name != 0) {
		strcpy(slot->name, name);
	} else {
		slot->name[0] = 0;
	}
}
