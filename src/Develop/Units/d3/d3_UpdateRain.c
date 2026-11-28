#include <stdio.h>

extern char* d3_ActiveCamera;
#include "Develop/DieGildeAddOn/game/game_data.h"

void __cdecl d3_BuildEulerRotationMatrix(float*, float*);

/* SIZE 0x5c */
typedef struct {
	int count;		/* +0x00 */
	char pad04[0x0c];	/* +0x04 */
	float* segs;		/* +0x10 */
	char pad14[8];		/* +0x14 */
	float wind_x;		/* +0x1c */
	float wind_z;		/* +0x20 */
	char pad24[0x1c];	/* +0x24 */
	float x;		/* +0x40 */
	float y;		/* +0x44 */
	float z;		/* +0x48 */
	char pad4c[4];
	float px;		/* +0x50 */
	float py;		/* +0x54 */
	float pz;		/* +0x58 */
} Rain415710;


typedef struct {
	float x;
	float y;
	float z;
	float w;
} Vec4_415710;

/* Advances the camera anchor, then integrates the wind drift of every rain
   record (stride 0x28: x, y, z, u, v, then the two projected end points) and
   rebuilds the screen positions. Out-of-range records are logged and reset. */
/* ADDRESS: GOLDTL 0x00415710 */
/* ADDRESS: GOLDDE 0x00413b10 */
void __cdecl d3_UpdateRain(Rain415710* self, float dt)
{
	char* cam;
	float* m;
	float* s;
	Vec4_415710 b;
	Vec4_415710 in;
	float out[16];
	float u[4];
	float t[4];
	float k;
	float dz;
	float w[4];
	float transform[4];
	float d0; float d1; float d2;
	float wind_x; float wind_z;
	float hw;
	float hh;
	float half;
	float cx;
	float cy;
	float num;
	float sv;
	float f;
	float f2;
	char msg[3][0x80];
	int i;

	cam = d3_ActiveCamera;
	
	in.x = self->x - *(float*) (cam + 0x84);
	in.y = self->y - *(float*) (cam + 0x88);
	in.z = self->z - *(float*) (cam + 0x8c);
	d3_BuildEulerRotationMatrix(&in.x, out);
	b.x = (out[0] + out[4]) * 0.0f + out[8] * 2.5f;
	self->x = *(float*) (d3_ActiveCamera + 0x84);
	self->y = *(float*) (d3_ActiveCamera + 0x88);
	self->z = *(float*) (d3_ActiveCamera + 0x8c);
	b.y = (out[1] + out[5]) * 0.0f + out[9] * 2.5f;
	cam = d3_ActiveCamera;
	m = (float*) (cam + 0x18c);
	d0 = self->px - *(float*) (cam + 0x4c);
	d1 = self->py - *(float*) (cam + 0x50);
	d2 = self->pz - *(float*) (cam + 0x54);
	transform[0] = d2 * m[8] + d1 * m[4] + d0 * m[0];
	transform[1] = d2 * m[9] + d1 * m[5] + d0 * m[1];
	transform[2] = d2 * m[10] + d1 * m[6] + d0 * m[2];
	transform[0] *= 0.0025f;
	transform[1] *= 0.0025f;
	transform[2] *= 0.0025f;
	self->px = *(float*) (d3_ActiveCamera + 0x4c);
	self->py = *(float*) (d3_ActiveCamera + 0x50);
	self->pz = *(float*) (d3_ActiveCamera + 0x54);
	wind_x = self->wind_x;
	wind_z = self->wind_z;
	m = (float*) (d3_ActiveCamera + 0x18c);
	t[0] = wind_z * m[8] + wind_x * m[0] + m[4] * 0.0f;
	t[1] = wind_z * m[9] + wind_x * m[1] + m[5] * 0.0f;
	t[2] = wind_z * m[10] + wind_x * m[2] + m[6] * 0.0f;
	u[0] = (m[8] + m[0]) * 0.0f - m[4] * 0.75f;
	u[1] = (m[9] + m[1]) * 0.0f - m[5] * 0.75f;
	u[2] = (m[10] + m[2]) * 0.0f - m[6] * 0.75f;
	hw = (float) ((d3_ViewportRight - g_1042570) >> 1);
	hh = (float) ((d3_ViewportBottom - g_1042574) >> 1);
	half = (hw > hh) ? hw : hh;
	cx = (float) g_1042570 + hw;
	cy = (float) g_1042574 + hh;
	s = self->segs;
	i = 0;
	if (self->count > 0) {
		dz = transform[2] + transform[2];
		k = half * 0.33333334f;
		do {
			w[0] = u[0] * s[5] + t[0] * s[4];
			s[0] = w[0] * dt + s[0] + transform[0] + b.x;
			if (s[0] < -1000.0 || s[0] > 1000.0) {
				sprintf(msg[0], "Drop %li: X is %f", (long) i, (double) s[0]);
				sprintf(msg[0], "    Rain->WindX: %f    Rain->WindZ: %f", (double) self->wind_x, (double) self->wind_z);
				s[0] = 0;
			}
			if (s[0] < -1.0) {
				do {
					s[0] += 2.0;
				} while (s[0] < -1.0);
			}
			if (s[0] >= 1.0) {
				do {
					s[0] -= 2.0;
				} while (s[0] >= 1.0);
			}
			w[1] = u[1] * s[5] + t[1] * s[4];
			s[1] = (w[1] * dt + transform[1] + b.y) + s[1];
			if (s[1] < -1000.0 || s[1] > 1000.0) {
				sprintf(msg[1], "Drop %li: Y is %f", (long) i, (double) s[1]);
				sprintf(msg[1], "    Rain->WindX: %f    Rain->WindZ: %f", (double) self->wind_x, (double) self->wind_z);
				s[1] = 0;
			}
			if (s[1] < -1.0) {
				do {
					s[1] += 2.0;
				} while (s[1] < -1.0);
			}
			if (s[1] >= 1.0) {
				do {
					s[1] -= 2.0;
				} while (s[1] >= 1.0);
			}
			w[2] = u[2] * s[5] + t[2] * s[4];
			s[2] = w[2] * dt + dz + s[2];
			if (s[2] < -1000.0 || s[2] > 1000.0) {
				sprintf(msg[2], "Drop %li: Z is %f", (long) i, (double) s[2]);
				sprintf(msg[2], "    Rain->WindX: %f    Rain->WindZ: %f", (double) self->wind_x, (double) self->wind_z);
				s[2] = 0;
			}
			if (s[2] < -1.0) {
				do {
					s[2] += 2.0;
				} while (s[2] < -1.0);
			}
			if (s[2] >= 1.0) {
				do {
					s[2] -= 2.0;
				} while (s[2] >= 1.0);
			}
			num = ((float) self->count * 0.5f + k) * 3.0f;
			f = num / (s[2] + s[2] + 3.0f);
			s[6] = f * s[0] + cx;
			s[7] = cy - f * s[1];
			w[0] = s[3] * w[0];
			w[1] = s[3] * w[1];
			sv = s[3] * w[2] + s[2];
			f2 = num / (sv + sv + 3.0f);
			s[8] = (w[0] + s[0]) * f2 + cx;
			s[9] = cy - (w[1] + s[1]) * f2;
			s += 10;
			i++;
		} while (i < self->count);
	}
}
