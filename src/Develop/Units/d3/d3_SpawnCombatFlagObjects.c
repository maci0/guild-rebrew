#include <stdio.h>
#include <string.h>

extern int g_772f08;
extern char* g_9b9e40[];

void __cdecl d3_ApplyObjectAnimation(char* obj, char* name, int k);
char* __cdecl d3_CreateSceneModelObject(int parent, float* pos, float* dir, char* name);
char __cdecl SelectTextureSet(void* obj, void* ctx, unsigned char a, char b);
void __cdecl d3_TransformPoint(char* object, float* in, float* out);

/* ADDRESS: GOLDTL 0x004d1ad0 */
char __cdecl d3_SpawnCombatFlagObjects(char* dummy)
{
	float dir[3];
	float pos[4];
	char* obj;

	if (strstr(dummy, "dummy_sp_ESCAPE") != 0) {
		dir[0] = 0.0f;
		dir[1] = 0.0f;
		dir[2] = 0.0f;
		d3_TransformPoint(dummy, (float*) (dummy + 0x4c), pos);
		obj = d3_CreateSceneModelObject(0, pos, dir, "ub_FLUCHTFLAGGE");
		g_9b9e40[g_772f08] = obj;
		strcpy(obj, "sp_ESCAPE");
		*(int*) (g_9b9e40[g_772f08] + 0x220) = 4;
		*(int*) (g_9b9e40[g_772f08] + 0x224) = 1;
		*(unsigned char*) (g_9b9e40[g_772f08] + 0x216) =
			(*(unsigned char*) (g_9b9e40[g_772f08] + 0x216) & 0xfd) | 1;
		*(unsigned char*) (g_9b9e40[g_772f08] + 0x216) |= 0x10;
		d3_ApplyObjectAnimation(g_9b9e40[g_772f08],
		             "sonstiges/anim_FLUCHTFLAGGE.baf", 1);
		g_772f08++;
		return 1;
	}
	if (strstr(dummy, "dummy_CONQUER") != 0) {
		dir[0] = 0.0f;
		dir[1] = 0.0f;
		dir[2] = 0.0f;
		d3_TransformPoint(dummy, (float*) (dummy + 0x4c), pos);
		obj = d3_CreateSceneModelObject(0, pos, dir, "ub_CONQUER");
		g_9b9e40[g_772f08] = obj;
		SelectTextureSet(obj, *(void**) (obj + 0x1cc), 1, 1);
		sprintf(g_9b9e40[g_772f08], "sp_CONQUER_%i", g_772f08);
		*(int*) (g_9b9e40[g_772f08] + 0x204) = 0;
		*(int*) (g_9b9e40[g_772f08] + 0x220) = 4;
		*(int*) (g_9b9e40[g_772f08] + 0x224) = 1;
		*(unsigned char*) (g_9b9e40[g_772f08] + 0x216) =
			(*(unsigned char*) (g_9b9e40[g_772f08] + 0x216) & 0xfd) | 1;
		g_772f08++;
	}
	return 1;
}
unsigned char _dpad_9b0e20[16];
#if defined(REBREW_SERVER) || defined(REBREW_GOLD)
unsigned char _dpad_9b9e40[896];
#else
/* Reference gaps only; the emitted objects inside the span keep their own rows. */
unsigned char _dpad_9b9e48[120];
unsigned char _dpad_9b9f40[640];
#endif
