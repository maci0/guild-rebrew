


#define MIN(a, b) ((a) > (b) ? (b) : (a))
#define MAX(a, b) ((a) < (b) ? (b) : (a))

#include "Develop/Units/d3/d3_camera.h"
void __cdecl d3_UpdateObjectCameraTransform(char* e, char* cam, int f);
char* __cdecl fcn_00455910(char* e, int h, char* p);

int __cdecl d3_GetObjectVerticalBounds(char* e, float* lo, float* hi)
{
	float* q;
	int i;
	char* p;

	*hi = 0.0f;
	*lo = 0.0f;
	if (*(int*) (e + 0x218) == 4) {
		d3_UpdateObjectCameraTransform(e, d3_ActiveCamera, 0);
		p = fcn_00455910(e, *(int*) (e + 0x1cc), *(char**) (e + 0x1ec) + 8);
		if (p != 0) {
			q = (float*) (p + 4);
			*lo = *q;
			*hi = *q;
			for (i = 7; i != 0; i--) {
				*lo = MIN(*q, *lo);
				*hi = MAX(*q, *hi);
				q += 20;
			}
			return 0;
		}
	}
	return 1;
}
