#include "client_scene_resources.h"
#include "client_scene_loader.h"

/* ADDRESS: GOLD 0x00461080 */
void __cdecl fcn_00461080(int selector, SCENE_PROGRESS progress)
{
	SCENE_RESOURCE* r;
	unsigned int i;
	int done;
	int total;

	total = 0;
	if (progress != 0) {
		total = 0;
		for (i = 0; i < g_10404a0; i++) {
			if (g_104049c[i].level > 0 && (g_104049c[i].flags & 2) == 0) {
				total++;
			}
		}
	}
	done = 0;
	r = g_104049c;
	for (i = 0; i < g_10404a0; i++, r++) {
		if (r->level > 0 && (r->flags & 2) == 0) {
			fcn_00460e40(r, selector);
			if (progress != 0) {
				progress(1, done, total);
			}
			done++;
		}
	}
	g_6b8af0 = 0;
}
