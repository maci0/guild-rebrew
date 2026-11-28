#include <string.h>

extern int g_6f2688;
extern char** g_6f5308;
extern int g_774a40;
extern char** g_779148;
extern int g_67a370;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d3_VisitSceneObjectsUntilStopped(int, int, int, void*, int);
char __cdecl fcn_0058f780(char* e, char* pfx);
void __cdecl d3_TransformPoint(char* src, char* pos, float* out);
char* __cdecl fcn_00501190(int, int);
char* __cdecl fcn_00501030(void);
void __cdecl d3_VisitSceneObjects(int, int, int, void*, int);
char __cdecl d3_CollectPrefixSceneObjects(char* e, char* pfx);
char* __cdecl gm_StartFilteredEntitySearch(int, int);
char* __cdecl gm_AddObjekt(void);
char* __cdecl gm_FindNextFilteredEntity(void);
#include "Develop/Units/d3/client_scene_transform.h"

#if defined(REBREW_GOLD)
/* ADDRESS: GOLD 0x0058f880 */
void __cdecl d3_CollectUnusedSceneObjects(int a1, char** list)
{
	float pa[4];
	float pb[4];
	int i;
	char* e;
	char* o;
	char* p;
	char* q;

	g_6f2688 = 0;
	g_6f5308 = list;
	d3_VisitSceneObjectsUntilStopped((int) g_5fb5b0, 0, 0x180, (void*) fcn_0058f780, a1);
	for (i = 0; i < g_6f2688; i++) {
		e = g_6f5308[i];
		if (e == 0) {
			continue;
		}
		o = *(char**) (e + 0x1f8);
		if (o != 0) {
			d3_TransformPoint(o, o + 0x4c, pa);
			p = fcn_00501190(1, 6);
			while (p != 0) {
				q = *(char**) (p + 0x61);
				if (q != 0) {
					d3_TransformPoint(q, q + 0x4c, pb);
					if (CompareVector3WithinTolerance(pb, pa, 100.0f)) {
						g_6f5308[i] = 0;
						break;
					}
				}
				p = fcn_00501030();
			}
		}
		for (e = *(char**) (e + 0x1fc); e != 0; e = *(char**) (e + 0x1f0)) {
			if (strncmp(e, "bk_", 3) == 0) {
				d3_TransformPoint(e, e + 0x4c, pa);
				p = fcn_00501190(1, 6);
				while (p != 0) {
					q = *(char**) (p + 0x61);
					if (q != 0) {
						d3_TransformPoint(q, q + 0x4c, pb);
						if (CompareVector3WithinTolerance(pb, pa, 100.0f)) {
							g_6f5308[i] = 0;
							goto next;
						}
					}
					p = fcn_00501030();
				}
			}
		}
	next:;
	}
}
#else
/* ADDRESS: GOLDTL 0x00598150 */
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
#endif
