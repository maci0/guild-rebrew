#include <string.h>

extern char* g_9b0dc0[];

int __cdecl fcn_0064d41a(char*, char*, ...);
char* __cdecl d3_FindSceneObject(int, int, int, char*);
void __cdecl d3_TransformPoint(char*, char*, float*);
char* __cdecl gm_SelectEntityHeadSet(int);
int __cdecl cut_RandMod(int);
#include "Develop/DieGildeAddOn/game/ch_motion.h"
void __cdecl ch_SetToDummy(char*, char*);


/* ADDRESS: GOLDTL 0x004da2b0 */
char* __cdecl cut_SpawnCutsceneSpectator(unsigned short* entity, char* prefix, int idx)
{
	float pos[4];
	char name[0x80];
	char* w;
	char* r;
	char* o;
	int k;

	pos[0] = 0.0f;
	pos[1] = 0.0f;
	pos[2] = 0.0f;
	pos[3] = 0.0f;
	fcn_0064d41a(name, "%s_%02i", prefix, idx + 1);
	w = d3_FindSceneObject(0, 0x100, 0, name);
	if (w == 0)
		goto fail;
	d3_TransformPoint(w, w + 0x4c, pos);
	r = gm_SelectEntityHeadSet(*entity);
	if (r == 0) {
		k = cut_RandMod(3);
		if (k == 1)
			strcpy(name, "buerger_MANN");
		else if (k == 2)
			strcpy(name, "buerger2_MANN");
		else
			strcpy(name, "handwerker3_MANN");
	} else {
		strcpy(name, r + 4);
	}
	o = fcn_004e4a80(name, pos);
	g_9b0dc0[idx] = o;
	if (o != 0) {
		ch_SetToDummy(o, w);
		fcn_0064d41a(name, "sp_%i", *(int*) (entity + 2));
		strcpy(*(char**) (o + 0x34), name);
		strcpy(o + 8, name);
		return o;
	}
fail:
	return 0;
}
