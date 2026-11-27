
#include "client_scene_loader.h"

/* Both zero stores occur in the native callback count path. */

typedef struct D3_TEX_RELOAD_REC {
	char pad0[0x40];
	int level;
	char pad44[0x54 - 0x44];
	unsigned char flags;
	char pad55[0x70 - 0x55];
} D3_TEX_RELOAD_REC;
// SIZE 0x70


extern char* g_104049c;
extern unsigned int g_10404a0;
extern int g_6b8af0;

void __cdecl fcn_0045ce90(D3_TEX_RELOAD_REC* r);

void __cdecl fcn_0045cfa0(SCENE_PROGRESS cb)
{
	D3_TEX_RELOAD_REC* r;
	unsigned int i;
	int done;
	int total;

	total = 0;
	if (cb != 0) {
		total = 0;
		for (i = 0; i < g_10404a0; i++) {
			if (((D3_TEX_RELOAD_REC*)g_104049c)[i].level > 0 && (((D3_TEX_RELOAD_REC*)g_104049c)[i].flags & 2) == 0) {
				total++;
			}
		}
	}
	done = 0;
	r = ((D3_TEX_RELOAD_REC*)g_104049c);
	for (i = 0; i < g_10404a0; i++, r++) {
		if (r->level > 0 && (r->flags & 2) == 0) {
			fcn_0045ce90(r);
			if (cb != 0) {
				cb(1, done, total);
			}
			done++;
		}
	}
	g_6b8af0 = 0;
}
