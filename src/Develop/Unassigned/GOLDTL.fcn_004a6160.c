#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d3_SelectSceneContext(int mode, int a2);
void __cdecl d3_TransformPoint(char* obj, char* pos, float* out);
void __cdecl d3_ComputeObjectWorldBounds(float* n, float* m, char* obj);

/* ADDRESS: GOLDTL 0x004a6160 */
int __cdecl gm_GetCannonShotEndpoints(char* a, float* pa, char* b, float* pb)
{
	struct {
		float m[4];
		float n[4];
	} v;
	int saved;

	saved = d3_CurrentContextIndex;
	if (!a || !b || !*(char**) (a + 0x61) || !*(char**) (b + 0x61) || a == b) {
		return -1;
	}
	d3_SelectSceneContext(0, 1);
	d3_TransformPoint(*(char**) (a + 0x61), *(char**) (a + 0x61) + 0x4c, pa);
	d3_ComputeObjectWorldBounds(&v.n[0], &v.m[0], *(char**) (a + 0x61));
	pa[1] += (v.m[1] - v.n[1]) * 0.8f;
	d3_TransformPoint(*(char**) (b + 0x61), *(char**) (b + 0x61) + 0x4c, pb);
	d3_SelectSceneContext(saved, 1);
	return 0;
}
