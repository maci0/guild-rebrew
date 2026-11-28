#include "Develop/Units/d3/client_scene_resources.h"
#include "Develop/Units/d3/client_scene_loader.h"

/* ADDRESS: GOLD 0x00461080 */
void __cdecl d3_ReloadAllTextures(int selector, SCENE_PROGRESS progress)
{
	SCENE_RESOURCE* r;
	unsigned int i;
	int done;
	int total;

	total = 0;
	if (progress != 0) {
		total = 0;
		for (i = 0; i < d3_TextureBankCount; i++) {
			if (d3_TextureBank[i].level > 0 && (d3_TextureBank[i].flags & 2) == 0) {
				total++;
			}
		}
	}
	done = 0;
	r = d3_TextureBank;
	for (i = 0; i < d3_TextureBankCount; i++, r++) {
		if (r->level > 0 && (r->flags & 2) == 0) {
			d3_LoadTextureSurface(r, selector);
			if (progress != 0) {
				progress(1, done, total);
			}
			done++;
		}
	}
	g_6b8af0 = 0;
}
