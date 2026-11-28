#include <string.h>
#include <math.h>

extern int* g_104336c;
extern int* g_1005900;
extern char* g_1005904;
extern int g_1005908;
extern int g_100590c;
extern int g_1006110;
extern int g_1006914;
extern unsigned char g_1005910[];
extern unsigned char g_1006114[];
extern int g_1043698;
extern int g_773ddc;
extern int d3_ActiveScene;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char s_681664[];
extern char s_681658[];
extern char s_68149c[];

char* __cdecl d3sm_CreateMap(int* a1, int n, int a3);
void __cdecl gv_Free3Fields(char* p);
void __cdecl rd_AddUnusedBauplatzToSupermap(int a);
int __cdecl lc_GetBauplatzPrefix(int a1, char* out);
void __cdecl d3_TransformToObjectSpace(char* object, float* position, float* result);
int __cdecl d3_TransformPoint(char* object, char* pos, float* result);
char __cdecl d3_VisitSceneObjects(char* scene, char* node, unsigned int flags, char (__cdecl* cb)(char*, char*), char* ctx);
char* __cdecl rd_GetBKSize(char* name);
void __cdecl rd_ProjectWorldToSupermap(float* ox, float* oy, float* position, char* object, char** context);
int __cdecl ai_FindPathFromNearestWalkable(int obj, int x, int y, int i, int j);
char* __cdecl d3_FindSceneObject(char* o, int flags, char* ptr, char* name);
char __cdecl d3sm_3D2SuperMap(char* map, float* pos, int* x, int* y, int* z);
char __cdecl d3_MatchObjectByNameAndPos(char* e, char* obj);
/* ADDRESS: GOLDTL 0x004bd4e0 */
int __cdecl rd_ConnectBuildingToSupermap(int sceneObjectArg, int typeIdArg)
{
	char name[0x40];
	char ctx[0x54];


	float pos[4];
	float ox1;
	float oy1;
	float ox2;
	float oy2;
	float dx;
	float dy;
	float rate;
	float step;
	int count;
	int i;
	int j;
	int k;
	char* box;
	char* map;
	char* dst;
	char* p;
	char c;
	int n;
	int d;

	g_1005900 = g_104336c;
	if (g_104336c == 0) {
		return 0;
	}
	g_1005904 = d3sm_CreateMap(g_104336c, *g_104336c, 2);
	if (g_1005904 == 0) {
		return 0;
	}
	g_100590c = -1;
	g_1005908 = -1;
	k = 0;
	n = 0;
	do {
		p = (char*) (g_1005900) + 0x7e24 + n;
		d = name - p;
		do {
			c = *p;
			p[d] = c;
			p++;
		} while (c);
		_strupr(name);
		if (strstr(name, s_681664) != 0) {
			g_1005908 = k;
		}
		if (strstr(name, s_681658) != 0) {
			g_100590c = k;
		}
		n += 0x40;
		k++;
	} while (n < 0x200);
	if (g_100590c == -1) {
		g_100590c = 1;
	}
	if (g_1005908 == -1) {
		g_1005908 = 2;
	}
	rd_AddUnusedBauplatzToSupermap((int) &g_1005900);
	i = lc_GetBauplatzPrefix(typeIdArg, ctx);
	if (i == 0) {
		gv_Free3Fields(g_1005904);
		return 0;
	}
	pos[0] = 0.0f;
	pos[1] = 0.0f;
	pos[2] = 0.0f;
	d3_TransformToObjectSpace((char*) sceneObjectArg, pos, (float*)(ctx + 0x40));
	*(int*) (ctx + 0x50) = 0;
	d3_VisitSceneObjects((char*) d3_ActiveScene, 0, 0x180, d3_MatchObjectByNameAndPos, ctx);
	if (*(int*) (ctx + 0x50) == 0) {
		gv_Free3Fields(g_1005904);
		return 0;
	}
	box = rd_GetBKSize(*(char**) (ctx + 0x50));
	if (box == 0) {
		gv_Free3Fields(g_1005904);
		return 0;
	}
	pos[0] = *(float*) (g_1005900 + 0x18) + *(float*) (box + 0x40);
	pos[1] = *(float*) (box + 0x44);
	pos[2] = *(float*) (g_1005900 + 0x1e) + *(float*) (box + 0x48);
	rd_ProjectWorldToSupermap(&oy1, &ox1, pos, *(char**)(ctx + 0x50), (char**) &g_1005900);
	pos[0] = *(float*) (box + 0x50) - *(float*) (g_1005900 + 0x18);
	pos[1] = *(float*) (box + 0x44);
	pos[2] = *(float*) (g_1005900 + 0x1e) + *(float*) (box + 0x48);
	rd_ProjectWorldToSupermap(&oy2, &ox2, pos, *(char**)(ctx + 0x50), (char**) &g_1005900);
	if (ai_FindPathFromNearestWalkable((int)&g_1005900, (int)oy1, (int)ox1, -1, -1) == 0) {
        gv_Free3Fields(g_1005904);
        return 0;
    }
	memcpy((char*) g_1006114, (char*) g_1005910, 0x800);








	g_1006110 = g_1006914;
	if (ai_FindPathFromNearestWalkable((int) &g_1005900, (int) oy2, (int) ox2, -1, -1) == 0) {
		gv_Free3Fields(g_1005904);
		return 0;
	}
	if (g_1006110 > g_1006914) {
		if (g_1006110 >= 5) {
			memcpy((char*) g_1006114, (char*) g_1005910, 0x800);
			g_1006110 = g_1006914;
		} else {
			memcpy((char*) g_1006114 + g_1006110 * 2, (char*) g_1005910, 0x800);
			g_1006110 += g_1006914;
		}
	} else if (g_1006110 < 5) {
		memcpy((char*) g_1006114 + g_1006110 * 2, (char*) g_1005910, 0x800);
		g_1006110 += g_1006914;
	}
	dy = oy2 - oy1;
	dx = ox2 - ox1;
	if (fabs(dy) > fabs(dx)) {
		rate = (float) (dx / fabs(dy));
		step = (dy > 0.0f) ? 1.0f : -1.0f;
		if ((int) oy1 != (int) oy2) {
			do {
				g_1006114[g_1006110 * 2] = (unsigned char) (int) oy1;
				g_1006114[g_1006110 * 2 + 1] = (unsigned char) (int) ox1;
				g_1006110++;
				map = *(char**) (g_1005904 + 0x24);
				*(int*) (map + ((int) ox1 * *g_1005900 + (int) oy1) * 0x1c) = 6;
				oy1 += step;
				ox1 += rate;
			} while ((int) oy1 != (int) oy2);
		}
	} else {
		rate = (float) (dy / fabs(dx));
		step = (dx > 0.0f) ? 1.0f : -1.0f;
		if ((int) ox1 != (int) ox2) {
			do {
				g_1006114[g_1006110 * 2] = (unsigned char) (int) oy1;
				g_1006114[g_1006110 * 2 + 1] = (unsigned char) (int) ox1;
				g_1006110++;
				map = *(char**) (g_1005904 + 0x24);
				*(int*) (map + ((int) ox1 * *g_1005900 + (int) oy1) * 0x1c) = 6;
				ox1 += step;
				oy1 += rate;
			} while ((int) ox1 != (int) ox2);
		}
	}
	dst = d3_FindSceneObject((char*) sceneObjectArg, 0x100, 0, s_68149c);
	if (dst == 0) {
		dst = (char*) sceneObjectArg;
	}
	d3_TransformPoint(dst, dst + 0x4c, pos);
	i = 0;
	j = 0;
	if (d3sm_3D2SuperMap(g_1005904, pos, &i, &j, 0) != 0) {
		if (ai_FindPathFromNearestWalkable((int) &g_1005900, i, j, -1, -1) != 0) {
			gv_Free3Fields(g_1005904);
			if (g_778d24 >= 0x780) {
					for (n = 0; n < g_1006110; n++) {
						map = *(char**) (g_1005900 + 5);
						*(map + (unsigned int) g_1006114[n * 2 + 1] * *g_1005900 + (unsigned int) g_1006114[n * 2]) = (unsigned char) g_1005908;
					}
					for (n = 0; n < g_1006914; n++) {
						map = *(char**) (g_1005900 + 5);
						*(map + (unsigned int) g_1005910[n * 2 + 1] * *g_1005900 + (unsigned int) g_1005910[n * 2]) = (unsigned char) g_1005908;
					}
				} else {
					p = (char*) g_1006114;
					for (n = 0; n < g_1006110; n++, p += 2) {
						for (k = -1; k < 2; k++) {
							for (i = -1; i < 2; i++) {
								map = *(char**) (g_1005900 + 5);
								*(map + ((unsigned int) (unsigned char) p[1] + k) * *g_1005900 + (unsigned int) (unsigned char) p[0] + i) = (unsigned char) g_1005908;
							}
						}
					}
					p = (char*) g_1005910;
					for (n = 0; n < g_1006914; n++, p += 2) {
						for (k = -1; k < 2; k++) {
							for (i = -1; i < 2; i++) {
								map = *(char**) (g_1005900 + 5);
								*(map + ((unsigned int) (unsigned char) p[1] + k) * *g_1005900 + (unsigned int) (unsigned char) p[0] + i) = (unsigned char) g_1005908;
							}
						}
					}
				}
			if ((g_1043698 & 2) == 0) {
				g_773ddc = 1;
			}
			return 1;
		}
	}
	gv_Free3Fields(g_1005904);
	return 0;
}
