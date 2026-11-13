extern char* g_6b8014;
extern float g_6628a8;
extern float g_6628a0;
extern float g_6629b8;
extern float g_662a70;
extern float g_6628b0;
extern float g_662a90;
extern float g_662a94;
extern float g_662918;
extern double g_662a48;
extern double g_662a50;
extern double g_6629c8;
extern int g_1042570;
extern int g_1042574;
extern int g_1042578;
extern int g_104257c;

void __cdecl fcn_00451900(float*, float*);

typedef struct {
	int count;		/* +0x00 */
	char pad04[0x34];	/* +0x04 */
	float* list;		/* +0x38 */
	char pad3c[8];		/* +0x3c */
	float u;		/* +0x44 */
	float v;		/* +0x48 */
	char pad4c[0x24];	/* +0x4c */
	float x;		/* +0x70 */
	float y;		/* +0x74 */
	float z;		/* +0x78 */
	char pad7c[4];		/* +0x7c */
	float px;		/* +0x80 */
	float py;		/* +0x84 */
	float pz;		/* +0x88 */
} Ctx_416540;


/* Rotates the camera position into the view matrix, then rebuilds the screen
 * position and the two extrusion points of every record (stride 0x28) in the
 * emitter's track list. */
/* ADDRESS: GOLDTL 0x00416540 */
void __cdecl fcn_00416540(Ctx_416540* self, float dt)
{
	float in[3]; float dx; float dy; float dz;
	float out[16];
	float* m;
	float* r;
	float a0;
	float a1;
	float a2;
	float t0;
	float t1;
	float t2;
	float u0;
	float u1;
	float u2;
	float b0;
	float b1;
	float hw;
	float hh;
	float half;
	float cx;
	float cy;
	float k;
	float s;
	float w; float s7;
	int i;

	in[0] = self->x - *(float*) (g_6b8014 + 0x84);
	in[1] = self->y - *(float*) (g_6b8014 + 0x88);
	in[2] = self->z - *(float*) (g_6b8014 + 0x8c);
	fcn_00451900(in, out);
	b0 = (out[6] + out[2]) * g_6628a8 + out[8] * 1.9f;
	self->x = *(float*) (g_6b8014 + 0x84);
	self->y = *(float*) (g_6b8014 + 0x88);
	self->z = *(float*) (g_6b8014 + 0x8c);
	b1 = (out[5] + out[1]) * g_6628a8 + out[9] * 1.9f;
	dx = self->px - *(float*) (g_6b8014 + 0x4c);
	dy = self->py - *(float*) (g_6b8014 + 0x50);
	dz = self->pz - *(float*) (g_6b8014 + 0x54);
	m = (float*) (g_6b8014 + 0x18c);
	a0 = dz * m[8] + dy * m[4] + dx * m[0];
	a1 = dz * m[9] + dy * m[5] + dx * m[1];
	a2 = dz * m[10] + dy * m[6] + dx * m[2];
	a0 *= 0.0025f; a1 *= 0.0025f; a2 *= 0.0025f;
	self->px = *(float*) (g_6b8014 + 0x4c);
	self->py = *(float*) (g_6b8014 + 0x50);
	self->pz = *(float*) (g_6b8014 + 0x54);
	t0 = self->u * m[0] + self->v * m[8] + m[4] * g_6628a8;
	t1 = self->u * m[1] + self->v * m[9] + m[5] * g_6628a8;
	t2 = self->u * m[2] + self->v * m[10] + m[6] * g_6628a8;
	u0 = (m[0] + m[8]) * g_6628a8 - m[4] * 1.0f;
	u1 = (m[1] + m[9]) * g_6628a8 - m[5] * 1.0f;
	u2 = (m[2] + m[10]) * g_6628a8 - m[6] * 1.0f;
	hw = (float) ((g_1042578 - g_1042570) >> 1);
	hh = (float) ((g_104257c - g_1042574) >> 1);
	half = (hw > hh) ? hw : hh;
	cx = (float) g_1042570 + hw;
	cy = (float) g_1042574 + hh;
	k = half * 3.0f;
	i = 0;
	r = self->list;
	while (i < self->count) {
		r[0] = (u0 * r[5] + t0 * r[4]) * dt + r[0] + a0 + b0;
		if (r[0] < (-1.0)) {
			do {
				r[0] += 2.0;
			} while (r[0] < (-1.0));
		}
		if (1.0 <= r[0]) {
			do {
				r[0] -= 2.0;
			} while (1.0 <= r[0]);
		}
		r[1] = (u1 * r[5] + t1 * r[4]) * dt + r[1] + a1 + b1;
		if (r[1] < (-1.0)) {
			do {
				r[1] += 2.0;
			} while (r[1] < (-1.0));
		}
		if (1.0 <= r[1]) {
			do {
				r[1] -= 2.0;
			} while (1.0 <= r[1]);
		}
		r[2] = (u2 * r[5] + t2 * r[4]) * dt + (a2 + a2) + r[2];
		if (r[2] < (-1.0f)) {
			do {
				r[2] += 2.0f;
			} while (r[2] < (-1.0f));
		}
		if (1.0f <= r[2]) {
			do {
				r[2] -= 2.0f;
			} while (1.0f <= r[2]);
		}
		s = k / (r[2] + r[2] + 3.0f);
		r[6] = s * r[0] + cx;
		s7 = cy - s * r[1]; r[7] = s7;
		w = (1.0f - r[2]) * 13.5f + 1.0f;
		w *= r[3];
		r[8] = r[6] + w;
		r[9] = w + s7;
		i++;
		r += 10;
	}
}
