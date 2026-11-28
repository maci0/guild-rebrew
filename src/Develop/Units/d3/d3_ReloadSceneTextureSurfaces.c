
#include "Develop/Units/d3/client_scene_loader.h"

/* Both zero stores occur in the native callback count path. */

typedef struct D3_TEX_RELOAD_REC {
	char pad0[0x40];
	int level;
	char pad44[0x54 - 0x44];
	unsigned char flags;
	char pad55[0x70 - 0x55];
} D3_TEX_RELOAD_REC;
// SIZE 0x70


extern char* d3_TextureBank;
extern unsigned int d3_TextureBankCount;
extern int g_6b8af0;

void __cdecl d3_LoadTextureSurfaceTl(D3_TEX_RELOAD_REC* r);

/* ADDRESS: GOLDDE 0x00451f50 */
void __cdecl d3_ReloadSceneTextureSurfaces(SCENE_PROGRESS cb)
{
	D3_TEX_RELOAD_REC* r;
	unsigned int i;
	int done;
	int total;

	total = 0;
	if (cb != 0) {
		total = 0;
		for (i = 0; i < d3_TextureBankCount; i++) {
			if (((D3_TEX_RELOAD_REC*)d3_TextureBank)[i].level > 0 && (((D3_TEX_RELOAD_REC*)d3_TextureBank)[i].flags & 2) == 0) {
				total++;
			}
		}
	}
	done = 0;
	r = ((D3_TEX_RELOAD_REC*)d3_TextureBank);
	for (i = 0; i < d3_TextureBankCount; i++, r++) {
		if (r->level > 0 && (r->flags & 2) == 0) {
			d3_LoadTextureSurfaceTl(r);
			if (cb != 0) {
				cb(1, done, total);
			}
			done++;
		}
	}
	g_6b8af0 = 0;
}
