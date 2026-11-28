


#include <math.h>

extern int d3_ActiveScene;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern char* g_9b46c0[];

int __cdecl d3_CollectEnemyWareNode(char*, char*);
void __cdecl d3_VisitSceneObjects(char*, int, int, int(__cdecl*)(char*, char*), char*);
void __cdecl d3_TransformPoint(char*, char*, float*);

/* ADDRESS: GOLDDE 0x004c08f0 */
char* __cdecl d3_FindNearestEnemyWare(char* e)
{
	float best;
	float pos[4];
	char* res;
	char* c;
	float dx;
	float dy;
	float dz;
	float d;
	int i;

	res = 0;
	best = 1000000.0f;
	g_772f10 = 0;
	d3_VisitSceneObjects(((char*)d3_ActiveScene), 0, 0x40, d3_CollectEnemyWareNode, e);
	c = *(char**) (*(char**) (e + 0x184) + 0x34);
	d3_TransformPoint(c, c + 0x4c, pos);
	for (i = 0; i < g_772f10; i++) {
		c = g_9b46c0[i];
		dx = pos[0] - *(float*) (c + 0x4c);
		dy = pos[1] - *(float*) (c + 0x50);
		dz = pos[2] - *(float*) (c + 0x54);
		d = (float) sqrt(dz * dz + dy * dy + dx * dx);
		if (d < best) {
			best = d;
			res = c;
		}
	}
	return res;
}
