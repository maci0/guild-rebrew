typedef struct {
	int x0;
	char p4[0xc];
	unsigned short w;
	char p12[6];
	float f;
	char p1c[0x64];
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

extern Obj41* g_99ec10;
extern float g_773d4c;
extern double g_665b80;
extern double g_662908;
extern double g_665b78;

// FUNCTION: GOLDTL 0x00502450
// SIZE: 131
int __cdecl fcn_00502450(int a, int b)
{
	unsigned short w;
	Obj41* o;

	w = g_85ab80[a].c[b].w;
	o = &g_99ec10[w];
	if (o->kind == 0x17 || o->kind == 0x25) {
		return 0;
	}
	if (a == 0) {
		return (int) (g_773d4c * g_85ab80[0].c[b].f * g_665b80 + g_662908);
	}
	return (int) (g_85ab80[a].c[0].x0 * g_85ab80[a].c[b].f * g_665b78);
}
