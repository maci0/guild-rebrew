extern char* d3_ActiveCamera;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_6629b8;
extern float g_662a70;
extern float g_662a90;
extern float g_662a94;
extern double g_662a50;
extern double g_6629c8;

void __cdecl d3_BuildEulerRotationMatrix(float*, float*);

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
void __cdecl d3_UpdateSnowFlakes(Ctx_416540* self, float dt)
{
	float in[4]; float dv[4];
	float out[16];
	float* r;
	float transformX;
	float transformY;
	float transformZ;
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
	float s;
	float w; float s7;
	int i;

	in[0] = self->x - *(float*) (d3_ActiveCamera + 0x84);
	in[1] = self->y - *(float*) (d3_ActiveCamera + 0x88);
	in[2] = self->z - *(float*) (d3_ActiveCamera + 0x8c);
	d3_BuildEulerRotationMatrix(in, out);
	b0 = (out[6] + out[2]) * 0.0f + out[8] * 1.9f;
	self->x = *(float*) (d3_ActiveCamera + 0x84);
	self->y = *(float*) (d3_ActiveCamera + 0x88);
	self->z = *(float*) (d3_ActiveCamera + 0x8c);
	b1 = (out[5] + out[1]) * 0.0f + out[9] * 1.9f;
	dv[0] = self->px - *(float*) (d3_ActiveCamera + 0x4c);
	dv[1] = self->py - *(float*) (d3_ActiveCamera + 0x50);
	dv[2] = self->pz - *(float*) (d3_ActiveCamera + 0x54);
	transformX = dv[2] * (*(float*) (d3_ActiveCamera + 0x18c + 8 * 4)) + dv[1] * (*(float*) (d3_ActiveCamera + 0x18c + 4 * 4)) + dv[0] * (*(float*) (d3_ActiveCamera + 0x18c + 0 * 4));
	transformY = dv[2] * (*(float*) (d3_ActiveCamera + 0x18c + 9 * 4)) + dv[1] * (*(float*) (d3_ActiveCamera + 0x18c + 5 * 4)) + dv[0] * (*(float*) (d3_ActiveCamera + 0x18c + 1 * 4));
	transformZ = dv[2] * (*(float*) (d3_ActiveCamera + 0x18c + 10 * 4)) + dv[1] * (*(float*) (d3_ActiveCamera + 0x18c + 6 * 4)) + dv[0] * (*(float*) (d3_ActiveCamera + 0x18c + 2 * 4));
	transformX *= 0.0025f; transformY *= 0.0025f; transformZ *= 0.0025f;
	self->px = *(float*) (d3_ActiveCamera + 0x4c);
	self->py = *(float*) (d3_ActiveCamera + 0x50);
	self->pz = *(float*) (d3_ActiveCamera + 0x54);
	t0 = self->u * (*(float*) (d3_ActiveCamera + 0x18c + 0 * 4)) + self->v * (*(float*) (d3_ActiveCamera + 0x18c + 8 * 4)) + (*(float*) (d3_ActiveCamera + 0x18c + 4 * 4)) * 0.0f;
	t1 = self->u * (*(float*) (d3_ActiveCamera + 0x18c + 1 * 4)) + self->v * (*(float*) (d3_ActiveCamera + 0x18c + 9 * 4)) + (*(float*) (d3_ActiveCamera + 0x18c + 5 * 4)) * 0.0f;
	t2 = self->u * (*(float*) (d3_ActiveCamera + 0x18c + 2 * 4)) + self->v * (*(float*) (d3_ActiveCamera + 0x18c + 10 * 4)) + (*(float*) (d3_ActiveCamera + 0x18c + 6 * 4)) * 0.0f;
	u0 = ((*(float*) (d3_ActiveCamera + 0x18c + 0 * 4)) + (*(float*) (d3_ActiveCamera + 0x18c + 8 * 4))) * 0.0f - (*(float*) (d3_ActiveCamera + 0x18c + 4 * 4)) * g_6628a0;
	u1 = ((*(float*) (d3_ActiveCamera + 0x18c + 1 * 4)) + (*(float*) (d3_ActiveCamera + 0x18c + 9 * 4))) * 0.0f - (*(float*) (d3_ActiveCamera + 0x18c + 5 * 4)) * g_6628a0;
	u2 = ((*(float*) (d3_ActiveCamera + 0x18c + 2 * 4)) + (*(float*) (d3_ActiveCamera + 0x18c + 10 * 4))) * 0.0f - (*(float*) (d3_ActiveCamera + 0x18c + 6 * 4)) * g_6628a0;
	hw = (float) ((d3_ViewportRight - g_1042570) >> 1);
	hh = (float) ((d3_ViewportBottom - g_1042574) >> 1);
	half = (hw > hh) ? hw : hh;
	cx = (float) g_1042570 + hw;
	cy = (float) g_1042574 + hh;
	i = 0;
	r = self->list;
	while (i < self->count) {
		r[0] = (u0 * r[5] + t0 * r[4]) * dt + r[0] + transformX + b0;
		if (r[0] < (-1.0)) {
			do {
				r[0] += 2.0;
			} while (r[0] < (-1.0));
		}
		if (r[0] >= 1.0) {
			do {
				r[0] -= 2.0;
			} while (r[0] >= 1.0);
		}
		r[1] = (u1 * r[5] + t1 * r[4]) * dt + r[1] + transformY + b1;
		if (r[1] < (-1.0)) {
			do {
				r[1] += 2.0;
			} while (r[1] < (-1.0));
		}
		if (r[1] >= 1.0) {
			do {
				r[1] -= 2.0;
			} while (r[1] >= 1.0);
		}
		r[2] = (u2 * r[5] + t2 * r[4]) * dt + (transformZ + transformZ) + r[2];
		if (r[2] < (-1.0f)) {
			do {
				r[2] += 2.0f;
			} while (r[2] < (-1.0f));
		}
		if (r[2] >= 1.0f) {
			do {
				r[2] -= 2.0f;
			} while (r[2] >= 1.0f);
		}
		s = (half * 3.0f) / (r[2] + r[2] + 3.0f);
		r[6] = s * r[0] + cx;
		s7 = cy - s * r[1]; r[7] = s7;
		w = (1.0f - r[2]) * 13.5f + 1.0f;
		w *= r[3];
		r[8] = r[6] + w;
		r[9] = w + s7;
		r += 10;
		i++;
	}
}
