typedef struct {
	int x0;
	char p4[0xc];
	unsigned short w;
	char p12[6];
	float f;
	char p1c[0x14];
	float f30;
	float f34;
	char p38[0x18];
	struct {
		unsigned char kind;
		char pad[3];
		float v;
	} ent[4];
	char p70[0x10];
} Cell502450;
// SIZE 0x80

typedef struct {
	Cell502450 c[85];
	char tail[0x10];
} Row502450;
// SIZE 0x2a90

extern Row502450 g_85ab80[];
#pragma pack(push, 1)
typedef struct {
	char kind;
	char pad[0x40];
} Obj41;
#pragma pack(pop)
// SIZE 0x41

extern char* g_99ec10;
extern float g_773d4c;
extern double g_665b80;
extern double g_662908;
extern double g_665b78;

// FUNCTION: GOLD 0x4ff8c0
// SIZE: 131
// FUNCTION: GOLDTL 0x00502450
// SIZE: 131
int __cdecl fcn_00502450(int a, int b)
{
	unsigned short w;
	Obj41* o;

	w = g_85ab80[a].c[b].w;
	o = &((Obj41*)g_99ec10)[w];
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

// FUNCTION: GOLD 0x4ff950
// SIZE: 192
// FUNCTION: GOLDTL 0x005024e0
// SIZE: 187
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
