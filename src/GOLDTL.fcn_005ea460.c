// FUNCTION: GOLDTL 0x005ea460
// SIZE: 98

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

extern float g_666100;

float __cdecl fcn_005ea460(float x)
{
	return MAX(MIN(x, g_666100), 0.0f) / g_666100;
}
