#include <stdio.h>

extern char* d3_ActiveCamera;
extern float g_6628a8;
#include "Develop/DieGildeAddOn/game/game_data.h"
extern float g_6629b0;
extern float g_662a70;
extern double g_6629c8;
extern double g_662a50;
extern double g_662a58;
extern double g_662a60;

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


/* Advances the camera anchor, then integrates the wind drift of every rain
   record (stride 0x28: x, y, z, u, v, then the two projected end points) and
   rebuilds the screen positions. Out-of-range records are logged and reset. */
/* ADDRESS: GOLDTL 0x00415710 */
void __cdecl d3_UpdateRain(Rain415710* self, float dt)
{
	char* cam;
	float* m;
	float* s;
	float in[3];
	float out[16];
	float transformX; double d0; double d1; double d2;
	float transformY;
	float transformZ;
	float b0;
	float b1;
	float t0;
	float t1;
	float t2;
	float u0;
	float u1;
	float u2;
	float hw;
	float hh;
	float half;
	float cx;
	float cy;
	float k;
	float dz;
	float wx;
	float wy;
	float wz;
	float num;
	float sv;
	float f;
	float f2;
	char msg[3][0x80];
	int i;

	cam = d3_ActiveCamera;
	
	in[0] = self->x - *(float*) (cam + 0x84);
	in[1] = self->y - *(float*) (cam + 0x88);
	in[2] = self->z - *(float*) (cam + 0x8c);
	d3_BuildEulerRotationMatrix(in, out);
	cam = d3_ActiveCamera; m = (float*) (cam + 0x18c);
	b0 = (out[4] + out[0]) * 0.0f + out[8] * g_6629b0;
	self->x = *(float*) (d3_ActiveCamera + 0x84);
	self->y = *(float*) (d3_ActiveCamera + 0x88);
	self->z = *(float*) (d3_ActiveCamera + 0x8c);
	b1 = (out[5] + out[1]) * 0.0f + out[9] * g_6629b0;
	d0 = (double) self->px - *(float*) (cam + 0x4c);
	d1 = (double) self->py - *(float*) (cam + 0x50);
	d2 = (double) self->pz - *(float*) (cam + 0x54);
	transformX = d2 * m[8] + d1 * m[4] + d0 * m[0]; transformX *= g_662a70;
	transformY = d2 * m[9] + d1 * m[5] + d0 * m[1]; transformY *= g_662a70;
	transformZ = (d2 * m[10] + d1 * m[6] + d0 * m[2]) * g_662a70;
	self->px = *(float*) (cam + 0x4c);
	self->py = *(float*) (cam + 0x50);
	self->pz = *(float*) (cam + 0x54);
	t0 = self->wind_x * m[0] + self->wind_z * m[8] + m[4] * 0.0f;
	t1 = self->wind_x * m[1] + self->wind_z * m[9] + m[5] * 0.0f;
	t2 = self->wind_x * m[2] + self->wind_z * m[10] + m[6] * 0.0f;
	u0 = (m[0] + m[8]) * 0.0f - m[4] * g_662a6c;
	u1 = (m[1] + m[9]) * 0.0f - m[5] * g_662a6c;
	u2 = (m[2] + m[10]) * 0.0f - m[6] * g_662a6c;
	hw = (float) ((d3_ViewportRight - g_1042570) >> 1);
	hh = (float) ((d3_ViewportBottom - g_1042574) >> 1);
	half = (hw > hh) ? hw : hh;
	cx = (float) g_1042570 + hw;
	cy = (float) g_1042574 + hh;
	if (self->count <= 0) {
		return;
	}
	dz = transformZ + transformZ;
	k = half * 0.33333334f;
	s = self->segs;
	for (i = 0; i < self->count; i++, s += 10) {
		wx = t0 * s[4] + u0 * s[5];
		s[0] = wx * dt + s[0] + transformX + b0;
		if (s[0] < g_662a60 || g_662a58 <= s[0]) {
			sprintf(msg[0], (char*) 0x6775e0, (long) i, (double) s[0]);
			sprintf(msg[0], (char*) 0x6775b8, (double) self->wind_x, (double) self->wind_z);
			s[0] = 0;
		}
		if (s[0] < g_662a50) {
			do {
				s[0] += g_662a48;
			} while (s[0] < g_662a50);
		}
		if (g_6629c8 <= s[0]) {
			do {
				s[0] -= g_662a48;
			} while (g_6629c8 <= s[0]);
		}
		wy = t1 * s[4] + u1 * s[5];
		s[1] = wy * dt + transformY + b1 + s[1];
		if (s[1] < g_662a60 || g_662a58 <= s[1]) {
			sprintf(msg[1], (char*) 0x6775a4, (long) i, (double) s[1]);
			sprintf(msg[1], (char*) 0x6775b8, (double) self->wind_x, (double) self->wind_z);
			s[1] = 0;
		}
		if (s[1] < g_662a50) {
			do {
				s[1] += g_662a48;
			} while (s[1] < g_662a50);
		}
		if (g_6629c8 <= s[1]) {
			do {
				s[1] -= g_662a48;
			} while (g_6629c8 <= s[1]);
		}
		wz = t2 * s[4] + u2 * s[5];
		s[2] = wz * dt + dz + s[2];
		if (s[2] < g_662a60 || g_662a58 <= s[2]) {
			sprintf(msg[2], (char*) 0x677590, (long) i, (double) s[2]);
			sprintf(msg[2], (char*) 0x6775b8, (double) self->wind_x, (double) self->wind_z);
			s[2] = 0;
		}
		if (s[2] < g_662a50) {
			do {
				s[2] += g_662a48;
			} while (s[2] < g_662a50);
		}
		if (g_6629c8 <= s[2]) {
			do {
				s[2] -= g_662a48;
			} while (g_6629c8 <= s[2]);
		}
		num = ((float) self->count * g_6628cc + k) * g_6628b0;
		sv = s[3] * wz + s[2];
		f = num / (s[2] + s[2] + g_6628b0);
		f2 = num / (sv + sv + g_6628b0);
		s[6] = f * s[0] + cx;
		s[7] = cy - f * s[1];
		s[8] = f2 * (s[3] * wx + s[0]) + cx;
		s[9] = cy - f2 * (s[3] * wy + s[1]);
	}
}
