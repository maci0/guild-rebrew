


#include <math.h>

// SIZE 0x10
typedef struct {
	float x;
	float y;
	float z;
	float w;
} V4353b0;

extern float g_662a94;

float __cdecl fcn_004353b0(V4353b0* v, int n)
{
	float best;
	float d;
	int i;

	best = g_662a94;
	for (i = 0; i < n; i++) {
		d = v[i].x * v[i].x + v[i].z * v[i].z + v[i].y * v[i].y;
		if (!(best > d)) {
			best = d;
		}
	}
	return (float) sqrt(best);
}
