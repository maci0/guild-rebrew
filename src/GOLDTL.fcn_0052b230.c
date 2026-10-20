#include <math.h>

/* Scene camera; inferred owner in d3_camera.h. */
extern char* g_6b8014;
extern double g_662950;
extern double g_662958;
extern double g_662cc0;
extern double g_662a50;
extern float g_6628a8;

void __cdecl fcn_005ebbb9(float*, char*);
void __cdecl fcn_00438cb0(char*, float*);
void __cdecl fcn_00438b40(char*, float*);
int __cdecl fcn_00451840(float*, float*, float);

/* ADDRESS: GOLDTL 0x0052b230 */
int __cdecl fcn_0052b230(void)
{
	float m[12];
	float v8;
	float v10;
	float v12;
	float t;
	float s;
	float x;
	float y;
	float n;
	float b8;
	float b10;
	float v8f;
	float v12f;
	float sc;
	float a;
	char* p;
	int i;
	int r;
	int flag;
	int u13;

	r = 0;
	if (*(int*) 0x14ce8e8 != 0 && *(int*) 0x774740 == 0) {
		*(int*) 0x774738 = (int) *(short*) 0x14cf900;
		*(int*) 0x774740 = 1;
		*(int*) 0x77473c = (int) *(short*) 0x14cf902;
	}
	i = *(int*) 0x14ce8e8;
	p = g_6b8014;
	if (*(int*) 0x14ce8d0 != 0 && p != 0) {
		if (i != 0) {
			flag = *(char*) 0x14cf70f;
			if (flag != 0) {
				t = (float) ((int) *(short*) 0x14cf902 - *(int*) 0x77473c) * *(float*) 0x662a70 + *(float*) (p + 0x84);
				*(float*) 0x7e26f0 = t;
				*(float*) 0x7e26f4 = *(float*) (p + 0x88);
				*(float*) 0x7e26f8 = *(float*) (p + 0x8c);
				*(float*) 0x7e26f0 = (float) fmod(*(float*) 0x7e26f0, g_662958);
			} else {
				*(float*) 0x7e26f0 = *(float*) (p + 0x84);
				*(float*) 0x7e26f4 = *(float*) (p + 0x88) - (float) ((int) *(short*) 0x14cf900 - *(int*) 0x774738) * *(float*) 0x662a70;
				*(float*) 0x7e26f8 = *(float*) (p + 0x8c);
				*(float*) 0x7e26f4 = (float) fmod(*(float*) 0x7e26f4, g_662958);
			}
			fcn_00438cb0(p, (float*) 0x7e26f0);
			if (*(int*) 0x774650 == *(int*) 0x774658 && (*(int*) 0x7746c4 == 0 || *(int*) 0x7746c8 != 0)) {
				*(int*) 0x7e3a50 = *(int*) (p + 0x84);
				*(int*) 0x7e3a54 = *(int*) (p + 0x88);
				*(int*) 0x7e3a58 = *(int*) (p + 0x8c);
				*(int*) 0x7e3a40 = *(int*) (p + 0x4c);
				*(int*) 0x7e3a44 = *(int*) (p + 0x50);
				*(int*) 0x7e3a48 = *(int*) (p + 0x54);
			}
			*(int*) 0x774738 = (int) *(short*) 0x14cf900;
			*(int*) 0x77473c = (int) *(short*) 0x14cf902;
			r = 1;
		}
	}
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
	if (*(int*) 0x14ce8d0 != 0) {
		return r;
	}
	fcn_005ebbb9(m, p + 0x18c);
	t = (float) ((int) *(short*) 0x14cf900 - *(int*) 0x774738);
	s = t * *(float*) 0x6628a8;
	v8 = m[0] * t + (m[4] * s + m[8] * s);
	v10 = m[1] * t + (m[5] * s + m[9] * s);
	v12 = m[2] * t + (m[6] * s + m[10] * s);
	if (flag != 0) {
		y = (float) ((double) (*(int*) 0x77473c - (int) *(short*) 0x14cf902) * g_662cc0);
		x = (float) ((double) y * g_662950);
		v8 = v8 + x;
		v10 = v10 + y;
		v12 = v12 + x;
		v8 = v8 + *(float*) (p + 0x4c);
		v10 = v10 + *(float*) (p + 0x50);
		v12 = v12 + *(float*) (p + 0x54);
	} else {
		y = (float) ((double) ((int) *(short*) 0x14cf902 - *(int*) 0x77473c) * g_662cc0);
		n = (float) ((double) y * g_662950);
		s = (float) ((double) y * g_662a50);
		b8 = m[0] * n + (m[4] * n + m[8] * s);
		b10 = m[1] * n + (m[5] * n + m[9] * s);
		v8f = b8 + v8;
		v12f = n + v12;
		sc = (float) sqrt((double) ((n * n + b10 * b10) + b8 * b8));
		a = (float) sqrt((double) ((v8f * v8f) + v12f * v12f));
		sc = sc / a;
		v8 = v8f * sc + *(float*) (p + 0x4c);
		v10 = g_6628a8 * sc;
		v12 = v12f * sc + *(float*) (p + 0x54);
		v10 = *(float*) (p + 0x50);
	}
	x = (float) fcn_00451840((float*) 0x773e04, &v8, 0.1f);
	if (x == 0) {
		fcn_00438b40(p, &v8);
		if (*(int*) 0x774650 == *(int*) 0x774658 && (*(int*) 0x7746c4 == 0 || *(int*) 0x7746c8 != 0)) {
			*(int*) 0x7e3a50 = *(int*) (p + 0x84);
			*(int*) 0x7e3a54 = *(int*) (p + 0x88);
			*(int*) 0x7e3a58 = *(int*) (p + 0x8c);
			*(int*) 0x7e3a40 = *(int*) (p + 0x4c);
			*(int*) 0x7e3a44 = *(int*) (p + 0x50);
			*(int*) 0x7e3a48 = *(int*) (p + 0x54);
		}
	}
	*(int*) 0x773e08 = *(int*) &v10;
	*(int*) 0x773e0c = *(int*) &v12;
	*(int*) 0x773e04 = *(int*) &v8;
	*(int*) 0x773e10 = u13;
	*(int*) 0x774738 = (int) *(short*) 0x14cf900;
	*(int*) 0x77473c = (int) *(short*) 0x14cf902;
	return 1;
}
