#include "Develop/DieGildeAddOn/game/game_data.h"

char __cdecl d3_FormatModelVariantName(int a, int b, int mode, char* key, char* val);
int __cdecl d3_FindCachedModel(char* s);
char* __cdecl d3_LoadCachedModel(char* key, char* val);

/* ADDRESS: GOLDTL 0x0044c310 */
/* ADDRESS: GOLDDE 0x004427b0 */
char* __cdecl d3_AcquireModel(int baseName, int altName)
{
	int i;
	char* r;
	char* t;
	char val[0x100];
	char key[0x100];

	d3_FormatModelVariantName(baseName, altName, 0, key, val);
	r = (char*) d3_FindCachedModel(val);
	if (r != 0) {
		return r;
	}
	r = (char*) d3_FindCachedModel(key);
	if (r != 0) {
		return r;
	}
	r = d3_LoadCachedModel(key, val);
	if (r != 0) {
		(*(int*) (r + 0x1e0))++;
	}
	if (d3_FormatModelVariantName(baseName, altName, -1, key, val)) {
		t = d3_LoadCachedModel(key, val);
		if (t != 0) {
			(*(int*) (t + 0x1e0))++;
		}
	}
	if ((d3_LODMode & 0x7f) == 1) {
		for (i = 1; i < 3; i++) {
			if (d3_FormatModelVariantName(baseName, altName, i, key, val)) {
				t = d3_LoadCachedModel(key, val);
				if (t != 0) {
					(*(int*) (t + 0x1e0))++;
				}
			}
		}
		return r;
	}
	return r;
}
