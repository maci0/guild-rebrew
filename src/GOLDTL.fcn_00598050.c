


#include <string.h>

extern int g_774a40;
extern char** g_779148;

int __cdecl _strnicmp(const char*, const char*, size_t);
void __cdecl fcn_00455350(char* src, char* pos, float* out);
char* __cdecl gm_StartFilteredEntitySearch(int, int);
char* __cdecl gm_AddObjekt(void);
#include "client_scene_transform.h"

char __cdecl fcn_00598050(char* e, char* pfx)
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
	fcn_00455350(e, e + 0x4c, pa);
	p = gm_StartFilteredEntitySearch(1, 6);
	while (p != 0) {
		q = *(char**) (p + 0x61);
		if (q != 0) {
			fcn_00455350(q, q + 0x4c, pb);
			if (fcn_00451840(pb, pa, 100.0f)) {
				return 1;
			}
		}
		p = gm_AddObjekt();
	}
	g_779148[g_774a40] = e;
	g_774a40++;
	return 1;
}
