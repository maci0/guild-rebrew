#include <string.h>

extern char s_67ade8[];
extern char* g_1042efc;
#include "Develop/DieGildeAddOn/game/game_data.h"

char* __cdecl d3_AppendVfsAssetPath(char* s, char* sub);
void __cdecl d3_LoadTextureSet(char* name, int* a, int* b, int* c);
char* __cdecl d3_LoadAGF(char* buf, char* name, int a, int b, int c);
void __cdecl m_FreeTracked(int p);
void __cdecl d3_ReleaseAGFMesh(void);
void __cdecl d3_ComputeNodeBoundsBox(void);
float __cdecl d3_GetModelRadius(int, char*);

/* ADDRESS: GOLDTL 0x0044c0e0 */
char* __cdecl d3_LoadCachedModel(char* path, char* name)
{
	char* r;
	char* p;
	int x;
	int a;
	int c;
	int b;
	char buf[0x100];

	r = 0;
	p = d3_AppendVfsAssetPath(path, s_67ade8);
	if (p != 0) {
		b = 0;
		c = 0;
		a = 0;
		strcpy(buf, p);
		d3_LoadTextureSet(name, &a, &b, &c);
		if (a == 0) {
			d3_LoadTextureSet(path, &a, &b, &c);
		}
		x = a;
		r = d3_LoadAGF(buf, name, x, b, c);
		if (r != 0) {
			if (x != 0 && *(int*) (r + 0x200) != x) {
				m_FreeTracked(x);
			}
			*(void**) (r + 0x1ec) = (void*) d3_ReleaseAGFMesh;
			*(void**) (r + 0x1f0) = (void*) d3_ComputeNodeBoundsBox;
			*(void**) (r + 0x1f4) = (void*) d3_GetModelRadius;
		} else if (x != 0) {
			m_FreeTracked(x);
		}
		if (r != 0) {
			*(char**) (r + 0x1fc) = g_1042efc;
			g_1042efc = r;
			*(char**) (r + 0x1f8) = g_1042d00;
			*(char**) (*(char**) (r + 0x1fc) + 0x1f8) = r;
		}
	}
	return r;
}
