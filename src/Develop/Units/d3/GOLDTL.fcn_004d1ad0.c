#include <stdio.h>
#include <string.h>

extern int g_772f08;
extern char* g_9b9e40[];

void __cdecl fcn_00412f10(char* obj, char* name, int k);
char* __cdecl fcn_00442910(int parent, float* pos, float* dir, char* name);
char __cdecl SelectTextureSet(void* obj, void* ctx, unsigned char a, char b);
void __cdecl fcn_00455350(char* object, float* in, float* out);

/* ADDRESS: GOLDTL 0x004d1ad0 */
char __cdecl fcn_004d1ad0(char* a0)
{
	float dir[3];
	float pos[4];
	char* obj;

	if (strstr(a0, "dummy_sp_ESCAPE") != 0) {
		dir[0] = 0.0f;
		dir[1] = 0.0f;
		dir[2] = 0.0f;
		fcn_00455350(a0, (float*) (a0 + 0x4c), pos);
		obj = fcn_00442910(0, pos, dir, "ub_FLUCHTFLAGGE");
		g_9b9e40[g_772f08] = obj;
		strcpy(obj, "sp_ESCAPE");
		*(int*) (g_9b9e40[g_772f08] + 0x220) = 4;
		*(int*) (g_9b9e40[g_772f08] + 0x224) = 1;
		*(unsigned char*) (g_9b9e40[g_772f08] + 0x216) =
			(*(unsigned char*) (g_9b9e40[g_772f08] + 0x216) & 0xfd) | 1;
		*(unsigned char*) (g_9b9e40[g_772f08] + 0x216) |= 0x10;
		fcn_00412f10(g_9b9e40[g_772f08],
		             "sonstiges/anim_FLUCHTFLAGGE.baf", 1);
		g_772f08++;
		return 1;
	}
	if (strstr(a0, "dummy_CONQUER") != 0) {
		dir[0] = 0.0f;
		dir[1] = 0.0f;
		dir[2] = 0.0f;
		fcn_00455350(a0, (float*) (a0 + 0x4c), pos);
		obj = fcn_00442910(0, pos, dir, "ub_CONQUER");
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
unsigned char _dpad_9b0e20[36896];
unsigned char _dpad_9b9e40[896];
