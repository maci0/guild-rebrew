


#include <string.h>

extern int g_774a40;
extern char** g_779148;

int __cdecl _strnicmp(const char*, const char*, size_t);
void __cdecl d3_TransformPoint(char* src, char* pos, float* out);
char* __cdecl gm_StartFilteredEntitySearch(int, int);
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);
#include "Develop/Units/d3/client_scene_transform.h"

/* ADDRESS: GOLDDE 0x0057d800 */
char __cdecl d3_CollectPrefixSceneObjects(char* e, char* pfx)
{
	float pa[4];
	float pb[4];
	char* p;
	char* q;

	if (pfx == 0) {
		if (_strnicmp(e, "bk_", 3) != 0 && _strnicmp(e + 1, "bk_", 3) != 0) {
			return 1;
		}
	} else {
		if (_strnicmp(e, pfx, strlen(pfx)) != 0 && _strnicmp(e + 1, pfx, strlen(pfx)) != 0) {
			return 1;
		}
	}
	d3_TransformPoint(e, e + 0x4c, pa);
	p = gm_StartFilteredEntitySearch(1, 6);
	while (p != 0) {
		q = *(char**) (p + 0x61);
		if (q != 0) {
			d3_TransformPoint(q, q + 0x4c, pb);
			if (CompareVector3WithinTolerance(pb, pa, 100.0f)) {
				return 1;
			}
		}
		p = gm_FindNextFilteredEntity();
	}
	g_779148[g_774a40] = e;
	g_774a40++;
	return 1;
}
