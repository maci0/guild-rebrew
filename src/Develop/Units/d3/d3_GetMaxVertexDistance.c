


#include <math.h>

// SIZE 0x10
typedef struct {
	float x;
	float y;
	float z;
	float w;
} V4353b0;



/* ADDRESS: GOLDDE 0x0042e970 */
float __cdecl d3_GetMaxVertexDistance(V4353b0* v, int n)
{
	float best;
	float d;
	int i;

	best = (-1.0f);
	for (i = 0; i < n; i++) {
		d = v[i].x * v[i].x + v[i].z * v[i].z + v[i].y * v[i].y;
		if (!(best > d)) {
			best = d;
		}
	}
	return (float) sqrt(best);
}
