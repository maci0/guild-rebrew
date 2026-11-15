#include <math.h>
#include "Develop/Units/d3/d3_camera.h"

typedef struct Vec3_453100 {
	float x;
	float y;
	float z;
} Vec3_453100;

typedef struct Query_453100 {
	char* ref;
	int count;
	char** list;
} Query_453100;

void __cdecl fcn_00458b10(char* object, char* camera, float* position, float* out);
void __cdecl fcn_00458940(char* o, char* ref, Vec3_453100* v, Vec3_453100* out);

/* ADDRESS: GOLD 0x00453100 */
char __cdecl fcn_00453100(char* o, Query_453100* q)
{
	char* ref;
	float dx;
	float dy;
	float dz;
	float d;

	if (q->list == 0) {
		*(char*) (*(char**) (o + 0x1e8) + 0x1a8) = 0;
		fcn_00458b10(o, g_6b8014, (float*) (o + 0x4c), (float*) (o + 0x1d8));
		if (*(int*) (o + 0x218) == 7) {
			if (*(float*) (o + 0x94) != *(double*) 0x5eb830 && (*(unsigned char*) (o + 0x211) & 0x10) == 0) {
				fcn_00458940(o, g_6b8014, (Vec3_453100*) 0x5ebb74, (Vec3_453100*) (*(char**) (o + 0x1e8) + 0x188));
				q->count++;
				return *(char*) (*(char**) (o + 0x1e8) + 0x1a8) = 1;
			}
			return 1;
		}
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
		return 1;
	}
	if (*(char*) (*(char**) (o + 0x1e8) + 0x1a8) != 0) {
		q->list[q->count] = o;
		q->count++;
	}
	return 1;
}
