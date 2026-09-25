// FUNCTION: GOLDTL 0x005d3880
// SIZE: 255

typedef struct {
	float v;
	float pad[4];
} Pt5d38;
// SIZE 0x14

typedef struct {
	float f[10];
} Arg5d38;
// SIZE 0x28

extern Pt5d38 g_99ec2c[16];
extern float g_662a94;
extern float g_6640cc;

void __cdecl fcn_00472c30(int, int, int, int, int, int, int);

void __cdecl fcn_005d3880(Arg5d38 s, int w, int h)
{
	int step;
	int i;
	int x0;
	int x1;
	float m;
	float sy;
	float by;
	float t;
	float u;

	step = (w - 0x69) / 16;
	m = g_662a94;
	for (i = 0; i < 16; i++) {
		if (m < g_99ec2c[i].v) {
			m = g_99ec2c[i].v;
		}
	}
	x0 = 0x2d;
	sy = (float) (h - 0x1e);
	by = (float) (h - 0x20) + g_6640cc;
	for (i = 0; i < 15; i++) {
		x1 = x0 + step;
		t = g_99ec2c[i].v;
		u = g_99ec2c[i + 1].v;
		fcn_00472c30(x0, (int) (by - t * sy), x1, (int) (by - u * sy), 0x10, 0xee, 0x10);
		x0 = x1;
	}
	fcn_00472c30(step * 15 + 0x2d, (int) (by - g_99ec2c[15].v * sy), step * 16 + 0x2d, (int) (by - s.f[9] * sy), 0x10, 0xee, 0x10);
}
