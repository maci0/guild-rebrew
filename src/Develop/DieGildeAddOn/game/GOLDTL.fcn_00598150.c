

#include <string.h>

extern int g_774a40;
extern char** g_779148;
extern int g_67a370;

void __cdecl d3_VisitSceneObjects(int, int, int, void*, int);
char __cdecl d3_CollectPrefixSceneObjects(char* e, char* pfx);
void __cdecl d3_TransformPoint(char* src, char* pos, float* out);
char* __cdecl gm_StartFilteredEntitySearch(int, int);
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);
#include "client_scene_transform.h"

void __cdecl d3_CollectUnusedSceneObjects(int a1, char** list)
{
	float pa[4];
	float pb[4];
	int i;
	char* e;
	char* o;
	char* p;
	char* q;

	g_774a40 = 0;
	g_779148 = list;
	d3_VisitSceneObjects(g_67a370, 0, 0x180, (void*) d3_CollectPrefixSceneObjects, a1);
	for (i = 0; i < g_774a40; i++) {
		e = g_779148[i];
		if (e == 0) {
			continue;
		}
		o = *(char**) (e + 0x1fc);
		if (o != 0) {
			d3_TransformPoint(o, o + 0x4c, pa);
			p = gm_StartFilteredEntitySearch(1, 6);
			while (p != 0) {
				q = *(char**) (p + 0x61);
				if (q != 0) {
					d3_TransformPoint(q, q + 0x4c, pb);
					if (CompareVector3WithinTolerance(pb, pa, 100.0f)) {
						g_779148[i] = 0;
						break;
					}
				}
				p = gm_FindNextFilteredEntity();
			}
		}
		for (e = *(char**) (e + 0x200); e != 0; e = *(char**) (e + 0x1f4)) {
			if (strncmp(e, "bk_", 3) == 0) {
				d3_TransformPoint(e, e + 0x4c, pa);
				p = gm_StartFilteredEntitySearch(1, 6);
				while (p != 0) {
					q = *(char**) (p + 0x61);
					if (q != 0) {
						d3_TransformPoint(q, q + 0x4c, pb);
						if (CompareVector3WithinTolerance(pb, pa, 100.0f)) {
							g_779148[i] = 0;
							goto next;
						}
					}
					p = gm_FindNextFilteredEntity();
				}
			}
		}
	next:;
	}
}
