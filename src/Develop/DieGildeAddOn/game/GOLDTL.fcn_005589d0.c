#include "Develop/DieGildeAddOn/game/spiel.h"


// SIZE 0x10
struct vec4 {
	float x;
	float y;
	float z;
	float w;
};

#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_665ea0;

void __cdecl d3_SelectSceneContext(int, int);

void __cdecl d3_TransformPoint(char*, char*, struct vec4*);
float __cdecl fcn_004514d0(struct vec4*, char*);

int __cdecl fcn_005589d0(char* u)
{
	char* x;
	struct vec4 b;
	struct vec4 a;
	struct vec4 d;
	int t;
	char* c;

	t = d3_CurrentContextIndex;
	d3_SelectSceneContext(0, 1);
	c = *(char**) (u + 0xc8);
	if (c != 0 && *(char**) (c + 0x1cc) != 0 && *(char**) (*(char**) (c + 0x1cc) + 0x318) != 0) {
		gm_ResolveEntityById((void**) (&x), 0, 0, *(int*) (u + 0xb4));
		if (x != 0 && *(char**) (x + 0x61) != 0 && *(char**) (*(char**) (x + 0x61) + 0x1cc) != 0
		    && *(char**) (*(char**) (*(char**) (x + 0x61) + 0x1cc) + 0x318) != 0) {
			d3_TransformPoint(*(char**) (x + 0x61), *(char**) (x + 0x61) + 0x4c, &a);
			a.y = (a.y + *(float*) (*(char**) (*(char**) (*(char**) (x + 0x61) + 0x1cc) + 0x318) + 0x1d4)) + g_665ea0;
			d3_TransformPoint(*(char**) (u + 0xc8), *(char**) (u + 0xc8) + 0x4c, &b);
			d.x = a.x - b.x;
			d.y = a.y - b.y;
			d.z = a.z - b.z;
			fcn_004514d0(&d, *(char**) (u + 0xc8) + 0x84);
			*(int*) (u + 0xe0) = *(int*) (*(char**) (u + 0xc8) + 0x84);
			*(int*) (u + 0xe4) = *(int*) (*(char**) (u + 0xc8) + 0x88);
			*(int*) (u + 0xe8) = *(int*) (*(char**) (u + 0xc8) + 0x8c);
			*(float*) (u + 0xd0) = b.x;
			*(float*) (u + 0xd4) = b.y;
			*(float*) (u + 0xd8) = b.z;
			*(int*) (u + 0xc4) = 1;
			d3_SelectSceneContext(t, 1);
			return 1;
		}
	}
	d3_SelectSceneContext(t, 1);
	return 0;
}
