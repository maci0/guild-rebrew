// FUNCTION: GOLDTL 0x443d20
// SIZE: 237

// SIZE 0x8
typedef struct Hit {
	char* e;
	float d;
} Hit;

// SIZE 0x58
typedef struct Ctx {
	Hit hits[9];
	int cam;
	int mask;
	float x;
	float y;
} Ctx;

extern char g_6b85a0;
extern int g_1042570;
extern int g_1042574;
extern int g_1042578;
extern int g_104257c;
extern float g_1052bc0;
extern float g_1052bc8;
extern int g_67a370;

void __cdecl fcn_004379a0(int, int, int, void*, void*);
char __cdecl fcn_00443b00(char*, char*);

char* __cdecl fcn_00443d20(int cam, float a, float b, int flags)
{
	float best;
	Ctx ctx;
	char* r = 0;
	unsigned int i;

	best = 1.0e10f;
	for (i = 0; i < 9; i++) {
		ctx.hits[i].d = 1.0e10f;
		ctx.hits[i].e = 0;
	}
	ctx.mask = 0;
	ctx.cam = cam;
	if (g_6b85a0 != 0) {
		ctx.x = (g_1042578 - g_1042570) * 0.5f - a;
		ctx.y = (g_104257c - g_1042574) * 0.5f - b;
	} else {
		ctx.x = g_1052bc0 - a;
		ctx.y = g_1052bc8 - b;
	}
	fcn_004379a0(g_67a370, 0, flags, fcn_00443b00, &ctx);
	for (i = 0; i < 9; i++) {
		if (ctx.hits[i].e != 0 && ctx.hits[i].d < best) {
			r = ctx.hits[i].e;
			best = ctx.hits[i].d;
		}
	}
	return r;
}
