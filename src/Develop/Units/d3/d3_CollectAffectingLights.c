#include <math.h>
#include "Develop/Units/d3/d3_camera.h"

typedef struct D3_LIGHT_VEC3 {
	float x;
	float y;
	float z;
} D3_LIGHT_VEC3;

typedef struct D3_LIGHT_QUERY {
	char* ref;
	int count;
	char** list;
} D3_LIGHT_QUERY;

void __cdecl d3_TransformPointToView(char* object, char* camera, float* position, float* out);
void __cdecl d3_TransformDirectionToView(char* o, char* ref, D3_LIGHT_VEC3* v, D3_LIGHT_VEC3* out);

/* ADDRESS: GOLD 0x00453100 */
char __cdecl d3_CollectAffectingLights(char* o, D3_LIGHT_QUERY* q)
{
	char* ref;
	float dx;
	float dy;
	float dz;
	float d;

	if (q->list == 0) {
		*(char*) (*(char**) (o + 0x1e8) + 0x1a8) = 0;
		d3_TransformPointToView(o, d3_ActiveCamera, (float*) (o + 0x4c), (float*) (o + 0x1d8));
		if (*(int*) (o + 0x218) == 7) {
			if (*(float*) (o + 0x94) != *(double*) 0x5eb830 && (*(unsigned char*) (o + 0x211) & 0x10) == 0) {
				d3_TransformDirectionToView(o, d3_ActiveCamera, (D3_LIGHT_VEC3*) 0x5ebb74, (D3_LIGHT_VEC3*) (*(char**) (o + 0x1e8) + 0x188));
				q->count++;
				return *(char*) (*(char**) (o + 0x1e8) + 0x1a8) = 1;
			}
		} else {
			*(float*) (o + 0x1e4) = *(float*) (o + 0x90);
			ref = q->ref;
			dx = *(float*) (o + 0x1d8) - *(float*) (ref + 0x1d8);
			dy = *(float*) (o + 0x1dc) - *(float*) (ref + 0x1dc);
			dz = *(float*) (o + 0x1e0) - *(float*) (ref + 0x1e0);
			if (*(float*) (o + 0x94) != *(double*) 0x5eb830) {
				d = (float) sqrt(dx * dx + dy * dy + dz * dz);
				if (d < *(float*) (o + 0x1e4) + *(float*) (ref + 0x1e4)) {
					q->count++;
					return *(char*) (*(char**) (o + 0x1e8) + 0x1a8) = 1;
				}
			}
		}
	} else if (*(char*) (*(char**) (o + 0x1e8) + 0x1a8) != 0) {
		q->list[q->count] = o;
		q->count++;
	}
	return 1;
}
