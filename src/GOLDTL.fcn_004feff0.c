// FUNCTION: GOLD 0x004fc890
// SIZE: 77
// FUNCTION: GOLDTL 0x4feff0
// SIZE: 77

typedef struct
{
	unsigned short id;
	char p2[6];
	char active;
	char p9;
	unsigned short cur;
	char pc[4];
	float lo;
	char p14[8];
	float hi;
	float max;
} Bar24;
// SIZE 0x24

extern float g_662a94;

float __cdecl fcn_004feff0(Bar24* a1)
{
	float v;

	if (a1->id == 0xffff) {
		return g_662a94;
	}
	if (a1->active == 0) {
		return g_662a94;
	}
	v = a1->cur;
	if (v <= a1->max) {
		return (a1->hi - a1->lo) / a1->max * v + a1->lo;
	}
	return a1->hi;
}
