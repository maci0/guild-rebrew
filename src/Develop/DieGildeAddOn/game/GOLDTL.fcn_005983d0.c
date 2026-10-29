

#include <string.h>

void __cdecl fcn_00455350(char* src, char* pos, float* out);
char* __cdecl gm_StartFilteredEntitySearch(int, int);
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);
#include "client_scene_transform.h"
#include "client_placement.h"

void __cdecl fcn_005983d0(char* e)
{
	float pa[4];
	float pb[4];
	int ok;
	char* o;
	char* s;
	char* p;
	char* q;

	ok = 1;
	o = *(char**) (e + 0x1fc);
	if (o != 0) {
		fcn_00455350(o, o + 0x4c, pa);
		p = gm_StartFilteredEntitySearch(1, 6);
		while (p != 0) {
			q = *(char**) (p + 0x61);
			if (q != 0) {
				fcn_00455350(q, q + 0x4c, pb);
				if (fcn_00451840(pb, pa, 100.0f)) {
					ok = 0;
					break;
				}
			}
			p = gm_FindNextFilteredEntity();
		}
	}
	for (s = *(char**) (e + 0x200); s != 0; s = *(char**) (s + 0x1f4)) {
		if (strncmp(s, "bk_", 3) == 0 || strncmp(s, "!bk_", 4) == 0) {
			fcn_00455350(s, s + 0x4c, pa);
			p = gm_StartFilteredEntitySearch(1, 6);
			while (p != 0) {
				q = *(char**) (p + 0x61);
				if (q != 0) {
					fcn_00455350(q, q + 0x4c, pb);
					if (fcn_00451840(pb, pa, 100.0f)) {
						ok = 0;
						goto done;
					}
				}
				p = gm_FindNextFilteredEntity();
			}
		}
	}
done:
	fcn_00598330(e, ok);
}
