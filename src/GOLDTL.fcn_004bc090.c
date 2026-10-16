unsigned char* __cdecl gm_StartFilteredEntitySearch(int, int);
unsigned char* __cdecl gm_AddObjekt(void);
int __cdecl gm_CheckEntityType(unsigned char*);
int __cdecl fcn_00505340(unsigned char*);
unsigned short __cdecl gm_RandomMod(unsigned short);
void __cdecl fcn_00455350(int, int, void*);
#include "client_scene_transform.h"

struct vec_4bc090 {
	float x;
	float y;
	float z;
	float w;
};
// SIZE 0x10

/* ADDRESS: GOLD 0x004bbb80 */
/* ADDRESS: GOLDTL 0x004bc090 */

void __cdecl fcn_004bc090(char* a1)
{
	unsigned char* chosen;
	struct vec_4bc090 pb;
	struct vec_4bc090 pa;
	struct vec_4bc090 pts[16];
	unsigned char* ents[256];
	unsigned char* it;
	unsigned char* b;
	unsigned short n;
	unsigned short cnt;
	int i;

	if (*(int*) (a1 + 8) != -1)
		return;
	n = 0;
	for (it = gm_StartFilteredEntitySearch(1, 6); it != 0; it = gm_AddObjekt()) {
		if (gm_CheckEntityType(it) == 0 && fcn_00505340(it) == 0 && *(int*) (it + 0x61) != 0)
			ents[n++] = it;
	}
	chosen = ents[gm_RandomMod(n)];
	fcn_00455350(*(int*) (chosen + 0x61), *(int*) (chosen + 0x61) + 0x4c, &pa);
	cnt = 0;
	for (i = 0; i < n; i++) {
		if (cnt >= 0x10)
			break;
		b = ents[i];
		fcn_00455350(*(int*) (b + 0x61), *(int*) (b + 0x61) + 0x4c, &pb);
		if (b != chosen && fcn_00451840((float*) &pa, (float*) &pb, 6000.0f) != 0) {
			pts[cnt++].x = pb.x;
			pts[cnt++].y = pb.y;
			pts[cnt++].z = pb.z;
		}
	}
	*(int*) (a1 + 8) = cnt;
}
