typedef struct D3_PICK_VIEWPORT {
	unsigned long x;
	unsigned long y;
	unsigned long width;
	unsigned long height;
	float min_z;
	float max_z;
} D3_PICK_VIEWPORT;
typedef struct D3_PICK_CELL {
	char pad[0x1ee];
	unsigned char on;
	char pad2[5];
} D3_PICK_CELL;

extern void* d3_ActiveCamera;
extern char g_1052be0[];
extern float g_1052c00[16];
extern float g_1043294;
extern float flt_1_0;
extern float flt_0_0;

double __cdecl sqrt(double);
float* __stdcall fcn_005ec410(float*, float, float, float);
float* __stdcall fcn_005eb970(float*, float*, float*);
float* __stdcall fcn_005eb2e4(float*, float*, D3_PICK_VIEWPORT*, float*, float*, float*);

/* ADDRESS: GOLDTL 0x00441ab0 */
/* ADDRESS: GOLDDE 0x0043a430 */
int __cdecl d3_PickFloorPoint(char* floor, int mx, int my, float radius, float* out)
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
	D3_PICK_VIEWPORT* vp;
	int b;
	int a;
	int ib;
	int ia;
	int row;
	int col;
	float dx;
	float dy;
	float z;
	unsigned char* height;

	if (floor == 0) {
		return -1;
	}
	fcn_005ec410(world, *(float*) (floor + 0x50) - *(float*) (((char*) d3_ActiveCamera) + 0x4c),
	             *(float*) (floor + 0x54) - *(float*) (((char*) d3_ActiveCamera) + 0x50),
	             *(float*) (floor + 0x58) - *(float*) (((char*) d3_ActiveCamera) + 0x54));
	fcn_005eb970(world, world, (float*) (((char*) d3_ActiveCamera) + 0x18c));
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
	vp = (D3_PICK_VIEWPORT*) g_1052be0;
	for (b = 0; b < 8; b++) {
		for (a = 0; a < 8; a++) {
			if (((D3_PICK_CELL*) (floor + 0xa0))[b * 8 + a].on > 0) {
				ib = *(int*) (floor + 4) * b;
				ia = *(int*) (floor + 4) * a;
				pos[0] = (float) ib * *(float*) (floor + 0x70);
				pos[1] = (float) ib * *(float*) (floor + 0x74);
				pos[2] = (float) ib * *(float*) (floor + 0x78);
				pos[0] += (float) ia * *(float*) (floor + 0x60);
				pos[1] += (float) ia * *(float*) (floor + 0x64);
				pos[2] += (float) ia * *(float*) (floor + 0x68);
				for (row = 0; row < *(int*) (floor + 4); row++) {
					height = *(unsigned char**)(floor + 0x10) + (*(int*)(floor + 4) * b + row) * *(int*)floor + *(int*)(floor + 4) * a;
					cur[0] = pos[0];
					cur[1] = pos[1];
					cur[2] = pos[2];
					for (col = 0; col < *(int*) (floor + 4); col++, height++) {
						v[0] = cur[0];
						v[2] = cur[2];
						v[1] = cur[1] + (float) *height *
						      *(float*) (floor + 0x84);
						fcn_005eb2e4(p, v, vp, g_1052c00, view, world);
						if (p[0] > (float) vp->x &&
						    p[0] <= (float) (vp->x + vp->width) &&
						    p[1] > (float) vp->y &&
						    p[1] <= (float) (vp->y + vp->height) &&
						    p[2] >= 0.0f && p[2] < 1.0f) {
							dx = (float) mx - p[0];
							dy = (float) my - p[1];
							if (dx * dx + dy * dy < r2) {
								z = (float) sqrt(dx * dx + dy * dy) / radius *
								    (p[2] / g_1043294);
								if (z < best && (*(int*)(floor + 4) * b + row) < *(int*)floor &&
								    (*(int*)(floor + 4) * a + col) < *(int*)floor) {
									best = z;
									packed = ((*(int*) (floor + 4) * b + row) << 16) |
									         (*(int*) (floor + 4) * a + col);
									out[0] = p[0];
									out[1] = p[1];
									out[2] = p[2];
								}
							}
						}
						cur[0] += *(float*) (floor + 0x60);
						cur[1] += *(float*) (floor + 0x64);
						cur[2] += *(float*) (floor + 0x68);
					}
					pos[0] += *(float*) (floor + 0x70);
					pos[1] += *(float*) (floor + 0x74);
					pos[2] += *(float*) (floor + 0x78);
				}
			}
		}
	}
	return packed;
}
