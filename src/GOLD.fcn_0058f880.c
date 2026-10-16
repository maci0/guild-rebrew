

#include <string.h>

extern int g_6f2688;
extern char** g_6f5308;
extern char* g_5fb5b0;

void __cdecl fcn_00438d40(int, int, int, void*, int);
char __cdecl fcn_0058f780(char* e, char* pfx);
void __cdecl fcn_00458a10(char* src, char* pos, float* out);
char* __cdecl fcn_00501190(int, int);
char* __cdecl fcn_00501030(void);
#include "client_scene_transform.h"

void __cdecl fcn_0058f880(int a1, char** list)
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
	fcn_00438d40((int) g_5fb5b0, 0, 0x180, (void*) fcn_0058f780, a1);
	for (i = 0; i < g_6f2688; i++) {
		e = g_6f5308[i];
		if (e == 0) {
			continue;
		}
		o = *(char**) (e + 0x1f8);
		if (o != 0) {
			fcn_00458a10(o, o + 0x4c, pa);
			p = fcn_00501190(1, 6);
			while (p != 0) {
				q = *(char**) (p + 0x61);
				if (q != 0) {
					fcn_00458a10(q, q + 0x4c, pb);
					if (fcn_00451840(pb, pa, 100.0f)) {
						g_6f5308[i] = 0;
						break;
					}
				}
				p = fcn_00501030();
			}
		}
		for (e = *(char**) (e + 0x1fc); e != 0; e = *(char**) (e + 0x1f0)) {
			if (strncmp(e, "bk_", 3) == 0) {
				fcn_00458a10(e, e + 0x4c, pa);
				p = fcn_00501190(1, 6);
				while (p != 0) {
					q = *(char**) (p + 0x61);
					if (q != 0) {
						fcn_00458a10(q, q + 0x4c, pb);
						if (fcn_00451840(pb, pa, 100.0f)) {
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
