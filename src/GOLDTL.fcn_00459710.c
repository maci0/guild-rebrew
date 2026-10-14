

#include <math.h>

extern float g_10425a0[];
extern float g_10425b0[];
extern float g_10425c0[];
extern float g_10425d0[];

void __cdecl fcn_00451340(float*, float*, float, float*);
void __cdecl fcn_004518a0(float*);

void __cdecl fcn_00459710(char* o, char flag)
{
	float vc[4];
	float v[2][4];
	float t;
	int i;
	int j;

	if (o == 0) {
		return;
	}
	*(int*) (o + 0xc) = -1;
	if (flag == 0) {
		return;
	}
	for (i = 0; i < 6; i++) {
		t = i * 0.2f;
		fcn_00451340(g_10425d0, g_10425b0, t, v[0]);
		fcn_00451340(g_10425c0, g_10425a0, t, v[1]);
		for (j = 0; j < 8; j++) {
			fcn_00451340(v[0], v[1], j * 0.14285715f, vc);
			fcn_004518a0(vc);
			*(float*) (o + 0x9c + (i * 8 + j) * 0x10) = atan2(vc[0], vc[2]);
		}
	}
}
