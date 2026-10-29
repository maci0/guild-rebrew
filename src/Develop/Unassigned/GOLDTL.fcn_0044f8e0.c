#include <math.h>

typedef struct Vert {
	float x;
	float y;
	float z;
	char padc[0xc];
} Vert;
// SIZE 0x18


/* Stores the bounding radius of o's vertices at 0x1d4 and appends the eight
 * corners of their bounding box after the last vertex. */
/* ADDRESS: GOLDTL 0x0044f8e0 */
void __cdecl fcn_0044f8e0(char* o)
{
	float bb[6];
	float r;
	float d;
	Vert* v;
	int i;

	r = 0.0f;
	for (i = 0; i < *(int*) (o + 0x44); i++) {
		v = &(*(Vert**) (o + 0x40))[i];
		d = (float) sqrt(v->x * v->x + v->y * v->y + v->z * v->z);
		if (d > r) {
			r = d;
		}
	}
	*(float*) (o + 0x1d4) = r;
	if (*(int*) (o + 0x44) <= 0) {
		return;
	}
	for (i = 0; i < 6; i++) {
		if (i & 1) {
			bb[i] = -1e10f;
		} else {
			bb[i] = 1e10f;
		}
	}
	for (i = 0; i < *(int*) (o + 0x44); i++) {
		v = &(*(Vert**) (o + 0x40))[i];
		if (v->x < bb[0]) {
			bb[0] = v->x;
		}
		if (v->x > bb[1]) {
			bb[1] = v->x;
		}
		if (v->y < bb[2]) {
			bb[2] = v->y;
		}
		if (v->y > bb[3]) {
			bb[3] = v->y;
		}
		if (v->z < bb[4]) {
			bb[4] = v->z;
		}
		if (v->z > bb[5]) {
			bb[5] = v->z;
		}
	}
	(*(Vert**) (o + 0x40))[*(int*) (o + 0x44)].x = bb[0];
	(*(Vert**) (o + 0x40))[*(int*) (o + 0x44)].y = bb[2];
	(*(Vert**) (o + 0x40))[*(int*) (o + 0x44)].z = bb[4];
	(*(Vert**) (o + 0x40))[*(int*) (o + 0x44) + 1].x = bb[1];
	(*(Vert**) (o + 0x40))[*(int*) (o + 0x44) + 1].y = bb[2];
	(*(Vert**) (o + 0x40))[*(int*) (o + 0x44) + 1].z = bb[4];
	(*(Vert**) (o + 0x40))[*(int*) (o + 0x44) + 2].x = bb[0];
	(*(Vert**) (o + 0x40))[*(int*) (o + 0x44) + 2].y = bb[3];
	(*(Vert**) (o + 0x40))[*(int*) (o + 0x44) + 2].z = bb[4];
	(*(Vert**) (o + 0x40))[*(int*) (o + 0x44) + 3].x = bb[1];
	(*(Vert**) (o + 0x40))[*(int*) (o + 0x44) + 3].y = bb[3];
	(*(Vert**) (o + 0x40))[*(int*) (o + 0x44) + 3].z = bb[4];
	(*(Vert**) (o + 0x40))[*(int*) (o + 0x44) + 4].x = bb[0];
	(*(Vert**) (o + 0x40))[*(int*) (o + 0x44) + 4].y = bb[2];
	(*(Vert**) (o + 0x40))[*(int*) (o + 0x44) + 4].z = bb[5];
	(*(Vert**) (o + 0x40))[*(int*) (o + 0x44) + 5].x = bb[1];
	(*(Vert**) (o + 0x40))[*(int*) (o + 0x44) + 5].y = bb[2];
	(*(Vert**) (o + 0x40))[*(int*) (o + 0x44) + 5].z = bb[5];
	(*(Vert**) (o + 0x40))[*(int*) (o + 0x44) + 6].x = bb[0];
	(*(Vert**) (o + 0x40))[*(int*) (o + 0x44) + 6].y = bb[3];
	(*(Vert**) (o + 0x40))[*(int*) (o + 0x44) + 6].z = bb[5];
	(*(Vert**) (o + 0x40))[*(int*) (o + 0x44) + 7].x = bb[1];
	(*(Vert**) (o + 0x40))[*(int*) (o + 0x44) + 7].y = bb[3];
	(*(Vert**) (o + 0x40))[*(int*) (o + 0x44) + 7].z = bb[5];
}
