#include <math.h>
#include "Develop/DieGildeAddOn/game/game_data.h"
/* Scene camera; inferred owner in d3_camera.h. */

extern double g_662958;
extern double g_662cc0;
extern double g_662a50;
extern float g_6628a8;
extern char g_14cf70f;
extern float g_662a70;

float* __stdcall D3DXMatrixTranspose(float*, const float*);
void __cdecl d3_SetObjectRotation(char*, float*);
void __cdecl fcn_00438b40(char*, float*);
int __cdecl CompareVector3WithinTolerance(float*, float*, float);

/* ADDRESS: GOLDTL 0x0052b230 */
int __cdecl fcn_0052b230(void)
{
	float m[16];
	float d[4];
	float b[4];
	float v[4];
	float sc;
	float y;
	short my;
	short mx;
	char* p;
	int i;
	int r;

	my = g_14cf902;
	mx = *(short*) g_14cf900;
	r = 0;
	i = g_14ce8e8;
	if (i != 0 && *(int*) 0x774740 == 0) {
		*(int*) 0x774738 = (int) mx;
		*(int*) 0x774740 = 1;
		*(int*) 0x77473c = (int) my;
	}
	if (g_14ce8d0 != 0 && d3_ActiveCamera != 0) {
		p = d3_ActiveCamera;
		if (i != 0) {
			if (g_14cf70f != 0) {
				d[0] = (float) ((int) my - *(int*) 0x77473c) * g_662a70 + *(float*) (p + 0x84);
				*(float*) 0x7e26f0 = d[0];
				*(float*) 0x7e26f4 = *(float*) (p + 0x88);
				*(float*) 0x7e26f8 = *(float*) (p + 0x8c);
				*(float*) 0x7e26f0 = (float) fmod(*(float*) 0x7e26f0, g_662958);
			} else {
				*(float*) 0x7e26f0 = *(float*) (p + 0x84);
				*(float*) 0x7e26f4 = *(float*) (p + 0x88) - (float) ((int) mx - *(int*) 0x774738) * g_662a70;
				*(float*) 0x7e26f8 = *(float*) (p + 0x8c);
				*(float*) 0x7e26f4 = (float) fmod(*(float*) 0x7e26f4, g_662958);
			}
			d3_SetObjectRotation(p, (float*) 0x7e26f0);
			p = d3_ActiveCamera;
			if (g_774650 == g_774658 && (*(int*) &g_7746c4 == 0 || *(int*) &g_7746c8 != 0)) {
				*(int*) &d3_CameraTargetRotation = *(int*) (p + 0x84);
				*(int*) &g_7e3a54 = *(int*) (p + 0x88);
				*(int*) &g_7e3a58 = *(int*) (p + 0x8c);
				*(int*) &g_7e3a40 = *(int*) (p + 0x4c);
				*(int*) &g_7e3a44 = *(int*) (p + 0x50);
				*(int*) &g_7e3a48 = *(int*) (p + 0x54);
			}
			*(int*) 0x774738 = (int) *(short*) g_14cf900;
			*(int*) 0x77473c = (int) g_14cf902;
			i = g_14ce8e8;
			r = 1;
		}
	}
	p = d3_ActiveCamera;
	if (i == 0) {
		if (*(int*) 0x774740 != 0) {
			*(int*) 0x774740 = 0;
			return 0;
		}
	}
	if (p == 0) {
		return r;
	}
	if (i == 0) {
		return r;
	}
	if (g_14ce8d0 != 0) {
		return r;
	}
	D3DXMatrixTranspose(m, (const float*) (p + 0x18c));
	d[0] = (float) ((int) *(short*) g_14cf900 - *(int*) 0x774738);
	d[1] = d[0] * g_6628a8;
	d[2] = d[1];
	v[0] = m[8] * d[2] + m[4] * d[1] + m[0] * d[0];
	v[1] = m[9] * d[2] + m[5] * d[1] + m[1] * d[0];
	v[2] = m[10] * d[2] + m[6] * d[1] + m[2] * d[0];
	if (g_14cf70f != 0) {
		b[1] = (float) ((double) (*(int*) 0x77473c - (int) g_14cf902) * g_662cc0);
		b[0] = (float) ((double) b[1] * 0.0);
		b[2] = (float) ((double) b[1] * 0.0);
		v[0] = v[0] + b[0];
		v[1] = v[1] + b[1];
		v[2] = v[2] + b[2];
		v[0] = v[0] + *(float*) (p + 0x4c);
		v[1] = v[1] + *(float*) (p + 0x50);
		v[2] = v[2] + *(float*) (p + 0x54);
	} else {
		y = (float) ((double) ((int) g_14cf902 - *(int*) 0x77473c) * g_662cc0);
		d[0] = (float) ((double) y * 0.0);
		d[1] = (float) ((double) y * 0.0);
		d[2] = (float) ((double) y * g_662a50);
		b[0] = m[8] * d[2] + m[4] * d[1] + m[0] * d[0];
		b[1] = m[9] * d[2] + m[5] * d[1] + m[1] * d[0];
		b[2] = m[10] * d[2] + m[6] * d[1] + m[2] * d[0];
		sc = (float) sqrt((double) ((b[2] * b[2] + b[1] * b[1]) + b[0] * b[0]));
		v[0] = b[0] + v[0];
		v[2] = b[2] + v[2];
		sc = sc / (float) sqrt((double) (v[2] * v[2] + v[0] * v[0]));
		v[0] = v[0] * sc;
		v[1] = g_6628a8 * sc;
		v[2] = v[2] * sc;
		v[0] = v[0] + *(float*) (p + 0x4c);
		v[1] = v[1] + *(float*) (p + 0x50);
		v[2] = v[2] + *(float*) (p + 0x54);
		*(int*) &v[1] = *(int*) (p + 0x50);
	}
	r = CompareVector3WithinTolerance((float*) 0x773e04, v, 0.1f);
	if (r == 0) {
		fcn_00438b40(d3_ActiveCamera, v);
		if (g_774650 == g_774658 && (*(int*) &g_7746c4 == 0 || *(int*) &g_7746c8 != 0)) {
			p = d3_ActiveCamera;
			*(int*) &d3_CameraTargetRotation = *(int*) (p + 0x84);
			*(int*) &g_7e3a54 = *(int*) (p + 0x88);
			*(int*) &g_7e3a58 = *(int*) (p + 0x8c);
			*(int*) &g_7e3a40 = *(int*) (p + 0x4c);
			*(int*) &g_7e3a44 = *(int*) (p + 0x50);
			*(int*) &g_7e3a48 = *(int*) (p + 0x54);
		}
	}
	*(int*) 0x773e08 = *(int*) &v[1];
	*(int*) 0x773e0c = *(int*) &v[2];
	*(int*) 0x773e04 = *(int*) v;
	*(int*) 0x773e10 = *(int*) &v[3];
	*(int*) 0x774738 = (int) *(short*) g_14cf900;
	*(int*) 0x77473c = (int) g_14cf902;
	return 1;
}
