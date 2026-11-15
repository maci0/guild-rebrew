#include "client_scene_resources.h"
#include "client_scene_loader.h"

/* ADDRESS: GOLD 0x00461080 */
void __cdecl fcn_00461080(int selector, SCENE_PROGRESS progress)
{
	SCENE_RESOURCE* r;
	unsigned int n;
	unsigned int i;
	int total;
	int done;

	n = g_10404a0;
	r = g_104049c;
	total = 0;
	if (progress != 0) {
		total = 0;
		for (i = 0; i < n; i++) {
			if (r[i].level > 0 && !(r[i].flags & 2)) {
				total++;
			}
		}
	}
	done = 0;
	for (i = 0; i < n; i++, r++) {
		if (r->level > 0 && !(r->flags & 2)) {
			fcn_00460e40(r, selector);
			if (progress != 0) {
				progress(1, done, total);
			}
			n = g_10404a0;
			done++;
		}
	}
	g_6b8af0 = 0;
}
