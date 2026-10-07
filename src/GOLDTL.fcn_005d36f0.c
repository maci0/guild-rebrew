// FUNCTION: GOLD 0x005c7420
// FUNCTION: GOLDTL 0x005d36f0

#include "client_types.h"
typedef Pt5d36_99ec2c Pt5d36;
// SIZE 0x14

typedef struct {
	int f[10];
} Arg5d36;
// SIZE 0x28

extern Pt5d36_99ec2c g_99ec2c[16];
extern float g_773d4c;

void __cdecl fcn_00472c30(int, int, int, int, int, int, int);

int __cdecl fcn_005d36f0(Arg5d36 s, int w, int h)
{
	int steps[9];
	int step;
	int i;
	int m;
	int x0;
	int x1;
	float sy;
	float by;

	step = (w - 0x69) / 16;
	m = -1;
	steps[0] = 500;
	steps[1] = 1000;
	steps[2] = 2000;
	steps[3] = 4000;
	steps[4] = 8000;
	steps[5] = 10000;
	steps[6] = 15000;
	steps[7] = 20000;
	steps[8] = 50000;
	for (i = 0; i < 16; i++) {
		if (g_99ec2c[i].v > m) {
			m = g_99ec2c[i].v;
		}
	}
	m = (int) (g_773d4c > (float) m ? g_773d4c : (float) m);
	for (i = 0; i < 8; i++) {
		if (m < steps[i]) {
			m = steps[i];
			break;
		}
	}
	sy = (float) (h - 0x1e) / m;
	by = (float) (h - 0x16);
	x0 = 0x2d;
	for (i = 0; i < 15; i++) {
		x1 = x0 + step;
		fcn_00472c30(x0, (int) (by - g_99ec2c[i].v * sy), x1, (int) (by - g_99ec2c[i + 1].v * sy), 0x33, 0x33, 0x33);
		x0 = x1;
	}
	fcn_00472c30(step * 15 + 0x2d, (int) (by - g_99ec2c[15].v * sy), step * 16 + 0x2d, (int) (by - g_773d4c * sy), 0x33, 0x33, 0x33);
	return m;
}
