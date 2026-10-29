#include "client_town.h"

#pragma pack(push, 1)
typedef struct {
	char kind;
	char pad[0x40];
} Obj41;
#pragma pack(pop)
// SIZE 0x41

extern char* lpObjektePROT;
extern float g_773d4c;
extern double g_665b80;
extern double g_662908;
extern double g_665b78;

/* ADDRESS: GOLDTL 0x00502450 */
int __cdecl fcn_00502450(int a, int b)
{
	unsigned short w;
	Obj41* o;

	w = g_85ab80[a].c[b].w;
	o = &((Obj41*)lpObjektePROT)[w];
	if (o->kind == 0x17 || o->kind == 0x25) {
		return 0;
	}
	if (a == 0) {
		return (int) (g_773d4c * g_85ab80[0].c[b].f * g_665b80 + g_662908);
	}
	return (int) (g_85ab80[a].c[0].x0 * g_85ab80[a].c[b].f * g_665b78);
}

extern float g_6628a8;
extern double g_662908;

unsigned char* __cdecl gm_StartFilteredEntitySearch(int, ...);
unsigned char* __cdecl gm_AddObjekt(void);

/* ADDRESS: GOLDTL 0x005024e0 */
int __cdecl fcn_005024e0(int a, int b)
{
	char* c;
	int sum;
	int j;
	unsigned char* e;

	sum = 0;
	c = (char*) &g_85ab80[a].c[b].w;
	if (c[0x40] == 0) {
		return 0;
	}
	for (j = 0; j < 4; j++) {
		if (c[0x40 + j * 8] != 0) {
			for (e = gm_StartFilteredEntitySearch(1, 5, *(unsigned char*) (c + 0x40 + j * 8)); e != 0; e = gm_AddObjekt()) {
				sum = (int) (sum + *(float*) (c + 0x44 + j * 8));
			}
		}
	}
	sum = (int) (sum * g_662908);
	if (*(float*) (c + 0x24) != g_6628a8) {
		sum = (int) (*(float*) (c + 0x24) / *(float*) (c + 0x20) * sum);
	}
	return sum;
}
