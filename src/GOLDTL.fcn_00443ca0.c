// FUNCTION: GOLDTL 0x443ca0

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

extern Ctx g_6b8318;
extern float g_1052bc0;
extern float g_1052bc8;
extern int g_67a370;

void __cdecl fcn_004379a0(int, int, int, void*, void*);
char __cdecl fcn_00443b00(char*, char*);

Ctx* __cdecl fcn_00443ca0(float a, float b, int flags, int mask, int cam)
{
	unsigned int i;

	for (i = 0; i < 9; i++) {
		g_6b8318.hits[i].d = 1.0e10f;
		g_6b8318.hits[i].e = 0;
	}
	g_6b8318.cam = cam;
	g_6b8318.mask = mask;
	g_6b8318.x = g_1052bc0 - a;
	g_6b8318.y = g_1052bc8 - b;
	fcn_004379a0(g_67a370, 0, flags, fcn_00443b00, &g_6b8318);
	return &g_6b8318;
}
