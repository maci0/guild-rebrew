extern char d3_UnitAxisVectors[];
#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_665ea0;

void __cdecl d3_SelectSceneContext(int, int);
int __cdecl gm_ResolveEntityById(int*, int, int, int);
void __cdecl d3_TransformPoint(void*, void*, float*);
void __cdecl d3_TransformDirection(void*, void*, float*);
float __cdecl d3_WrapYawDelta(float*, float*);
void __cdecl d3_AnimateObjectTransform(void*, float*, float*, int, int);

/* Places the camera at the referenced entity's aim point once both the
 * camera chain and the resolved entity expose a view target. The aim vector
 * is rotated by the view direction and sent as a placement message. */
/* ADDRESS: GOLDTL 0x00558b70 */
/* ADDRESS: GOLDDE 0x0053eed0 */
unsigned int __cdecl he_PlaceSensenmannCamera(char* eventRecord)
{
	float from[4];
	float to[4];
	float aim[4];
	float delta[4];
	float angle;
	int saved;
	char* ent;
	char* view;

	saved = d3_CurrentContextIndex;
	d3_SelectSceneContext(0, 1);

	view = *(char**) (eventRecord + 0xc8);
	if (view == 0) {
		goto fail;
	}
	view = *(char**) (view + 0x1cc);
	if (view == 0) {
		goto fail;
	}
	if (*(int*) (view + 0x318) == 0) {
		goto fail;
	}
	gm_ResolveEntityById((int*) &ent, 0, 0, *(int*) (eventRecord + 0xb4));


	if (ent == 0) {
		goto fail;
	}
	view = *(char**) (ent + 0x61);
	if (view == 0) {
		goto fail;
	}
	view = *(char**) (view + 0x1cc);
	if (view == 0) {
		goto fail;
	}
	if (*(int*) (view + 0x318) == 0) {
		goto fail;
	}
	view = *(char**) (ent + 0x61);
	d3_TransformPoint(view, view + 0x4c, from);

	from[1] = from[1] + *(float*) (*(char**) (*(char**) (*(char**) (ent + 0x61) + 0x1cc) + 0x318) + 0x1d4);
	from[1] = from[1] + g_665ea0;

	d3_TransformPoint(*(char**) (eventRecord + 0xc8), *(char**) (eventRecord + 0xc8) + 0x4c, to);
	delta[0] = from[0] - to[0];
	delta[1] = from[1] - to[1];
	delta[2] = from[2] - to[2];
	d3_TransformDirection(*(char**) (eventRecord + 0xc8), (char*) &d3_UnitAxisVectors, aim);
	angle = d3_WrapYawDelta(aim, delta);
	view = *(char**) (eventRecord + 0xc8);
	if (view == 0) {
		goto fail;
	}
	aim[0] = *(float*) (view + 0x84);
	aim[1] = *(float*) (view + 0x88);
	aim[2] = *(float*) (view + 0x8c);
	aim[1] = aim[1] + angle;
	d3_AnimateObjectTransform(view, to, aim, 0x78, 8);
	d3_SelectSceneContext(saved, 1);
	return 1;
fail:
	d3_SelectSceneContext(saved, 1);
	return 0;
}
