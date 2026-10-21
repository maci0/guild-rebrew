typedef struct Viewport_441ab0 {
	unsigned long x;
	unsigned long y;
	unsigned long width;
	unsigned long height;
	float min_z;
	float max_z;
} Viewport_441ab0;
typedef struct Cell_441ab0 {
	char pad[0x1ee];
	unsigned char on;
	char pad2[5];
} Cell_441ab0;

extern void* g_6b8014;
extern char g_1052be0[];
extern float g_1052c00[16];
extern float g_1043294;
extern float g_6628a0;
extern float g_6628a8;

double __cdecl sqrt(double);
float* __stdcall fcn_005ec410(float*, float, float, float);
float* __stdcall fcn_005eb970(float*, float*, float*);
float* __stdcall fcn_005eb2e4(float*, float*, Viewport_441ab0*, float*, float*, float*);

/* ADDRESS: GOLDTL 0x00441ab0 */
int __cdecl fcn_00441ab0(char* o, int mx, int my, float radius, float* out)
{
	float world[16];
	float view[16];
	float v[3];
	float p[3];
	float r2;
	float best;
	int packed;
	float pos[3];
	float cur[3];
	Cell_441ab0* cell;
	Viewport_441ab0* vp;
	int b;
	int a;
	int row;
	int col;
	float dx;
	float dy;
	float z;

	if (o == 0) {
		return -1;
	}
	fcn_005ec410(world, *(float*) (o + 0x50) - *(float*) (((char*) g_6b8014) + 0x4c),
	             *(float*) (o + 0x54) - *(float*) (((char*) g_6b8014) + 0x50),
	             *(float*) (o + 0x58) - *(float*) (((char*) g_6b8014) + 0x54));
	fcn_005eb970(world, world, (float*) (((char*) g_6b8014) + 0x18c));
	r2 = radius * radius;
	view[14] = 0.0f;
	view[13] = 0.0f;
	view[12] = 0.0f;
	view[11] = 0.0f;
	view[9] = 0.0f;
	view[8] = 0.0f;
	view[7] = 0.0f;
	view[6] = 0.0f;
	view[4] = 0.0f;
	view[3] = 0.0f;
	view[2] = 0.0f;
	view[1] = 0.0f;
	view[15] = 1.0f;
	view[10] = 1.0f;
	view[5] = 1.0f;
	view[0] = 1.0f;
	best = 1.0f;
	packed = -1;
	vp = (Viewport_441ab0*) g_1052be0;
	cell = (Cell_441ab0*) (o + 0x28e);
	for (b = 0; b < 8; b++) {
		for (a = 0; a < 8; a++) {
			if (cell->on != 0) {
				pos[0] = (float) (*(int*) (o + 4) * a) * *(float*) (o + 0x60) +
				         (float) (*(int*) (o + 4) * b) * *(float*) (o + 0x70);
				pos[1] = (float) (*(int*) (o + 4) * a) * *(float*) (o + 0x64) +
				         (float) (*(int*) (o + 4) * b) * *(float*) (o + 0x74);
				pos[2] = (float) (*(int*) (o + 4) * a) * *(float*) (o + 0x68) +
				         (float) (*(int*) (o + 4) * b) * *(float*) (o + 0x78);
				for (row = 0; row < *(int*) (o + 4); row++) {
					cur[0] = pos[0];
					cur[1] = pos[1];
					cur[2] = pos[2];
					for (col = 0; col < *(int*) (o + 4); col++) {
						v[0] = cur[0];
						v[2] = cur[2];
						v[1] = cur[1] + (float) *(unsigned char*) ((char*) *(int*) (o + 0x10) +
						      (*(int*) (o + 4) * b + row) * *(int*) o + *(int*) (o + 4) * a + col) *
						      *(float*) (o + 0x84);
						fcn_005eb2e4(p, v, vp, g_1052c00, view, world);
						if (p[0] >= (float) vp->x &&
						    p[0] <= (float) (vp->x + vp->width) &&
						    p[1] >= (float) vp->y &&
						    p[1] <= (float) (vp->y + vp->height) &&
						    p[2] >= 0.0f && p[2] <= 1.0f) {
							dx = (float) mx - p[0];
							dy = (float) my - p[1];
							if (dx * dx + dy * dy <= r2) {
								z = (float) sqrt(dx * dx + dy * dy) / radius *
								    (p[2] / g_1043294);
								if (z > best) {
									best = z;
									packed = ((*(int*) (o + 4) * b + row) << 16) |
									         (*(int*) (o + 4) * a + col);
									out[0] = p[0];
									out[1] = p[1];
									out[2] = p[2];
								}
							}
						}
						cur[0] += *(float*) (o + 0x60);
						cur[1] += *(float*) (o + 0x64);
						cur[2] += *(float*) (o + 0x68);
					}
					pos[0] += *(float*) (o + 0x70);
					pos[1] += *(float*) (o + 0x74);
					pos[2] += *(float*) (o + 0x78);
				}
			}
			cell++;
		}
	}
	return packed;
}
