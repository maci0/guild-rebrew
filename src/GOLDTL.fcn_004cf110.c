// FUNCTION: GOLDTL 0x4cf110
// SIZE: 110

typedef struct {
	int p;
	int t;
} rec8;
// SIZE 0x8

extern rec8 g_9ba1c0[32];
extern char g_68b7b4[];
extern int g_6b7fac;

int __cdecl fcn_00442910(int, int, float*, char*);

rec8* __cdecl fcn_004cf110(int a)
{
	float v[3];
	int i;

	v[0] = 0;
	v[1] = 0;
	v[2] = 0;
	for (i = 0; i < 32; i++) {
		if (g_9ba1c0[i].p == 0) {
			g_9ba1c0[i].p = fcn_00442910(0, a, v, g_68b7b4);
			g_9ba1c0[i].t = g_6b7fac;
			return &g_9ba1c0[i];
		}
	}
	return 0;
}
