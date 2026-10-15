

typedef float* (__cdecl* fcn_0043a5d0_f)(char*, char*, char*);

#include "Develop/Units/d3/d3_camera.h"

void __cdecl fcn_00438100(char*, char*, int);

char __cdecl fcn_0043a5d0(char* o, float* bb)
{
	float* p;
	float* row;
	int j;
	int k;

	if (*(char**) (o + 0x1cc) != 0 && *(char**) (o + 0x1ec) != 0) {
		if ((o[0x216] & 0x20) == 0) {
			fcn_00438100(o, g_6b8014, 0);
		}
		p = (*(fcn_0043a5d0_f*) (*(char**) (*(char**) (o + 0x1cc) + 0x318) + 0x1f0))(o, *(char**) (o + 0x1cc), *(char**) (o + 0x1ec) + 8);
		for (j = 0; j < 8; j++) {
			row = p + j * 20;
			for (k = 0; k < 3; k++) {
				bb[k] = (double) bb[k] < row[k] ? bb[k] : row[k];
				bb[k + 4] = (double) bb[k + 4] > row[k] ? bb[k + 4] : row[k];
			}
		}
	}
	return 1;
}
