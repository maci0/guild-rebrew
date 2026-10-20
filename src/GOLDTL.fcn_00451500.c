#include <math.h>

extern float g_662d60;
extern float g_662d64;
extern float g_662d68;
extern float g_662ce8;
extern float g_662d40[3];

void __cdecl fcn_004518a0(float*);

/* ADDRESS: GOLDTL 0x00451500 */
void __cdecl fcn_00451500(float* a, float angle, float* m)
{
	float s;
	float c;
	float v5;
	float v6;
	float v7;
	float v4;

	v7 = g_662d68;
	s = (float) sin(angle);
	c = (float) cos(angle);
	v5 = g_662d60 * c - g_662d64 * s;
	v6 = g_662d60 * s + g_662d64 * c;
	m[8] = a[0];
	m[9] = a[1];
	m[10] = a[2];
	fcn_004518a0(m + 8);
	v4 = -(v5 * m[8] + v7 * m[10] + v6 * m[9]);
	v5 = v4 * m[8] + v5;
	m[4] = v5;
	v6 = v4 * m[9] + v6;
	m[5] = v6;
	v7 = v4 * m[10] + v7;
	m[6] = v7;
	if ((float) sqrt(v5 * v5 + v6 * v6 + v7 * v7) < g_662ce8) {
		v5 = -m[9];
		m[4] = v5 * m[8] + g_662d60;
		m[5] = v5 * m[9] + g_662d64;
		v5 = v5 * m[10] + g_662d68;
		m[6] = v5;
		if ((float) sqrt(m[5] * m[5] + m[4] * m[4] + v5 * v5) < g_662ce8) {
			v5 = -m[10];
			m[4] = v5 * m[8] + g_662d40[0];
			m[5] = v5 * m[9] + g_662d40[1];
			v5 = v5 * m[10] + g_662d40[2];
			m[6] = v5;
			if ((float) sqrt(m[5] * m[5] + m[4] * m[4] + v5 * v5) < g_662ce8) {
				m[0xe] = 0.0f;
				m[0xd] = 0.0f;
				m[0xc] = 0.0f;
				m[0xb] = 0.0f;
				m[9] = 0.0f;
				m[8] = 0.0f;
				m[7] = 0.0f;
				m[6] = 0.0f;
				m[4] = 0.0f;
				m[3] = 0.0f;
				m[2] = 0.0f;
				m[1] = 0.0f;
				m[0xf] = 1.0f;
				m[10] = 1.0f;
				m[5] = 1.0f;
				m[0] = 1.0f;
				return;
			}
		}
	}
	fcn_004518a0(m + 4);
	m[0xb] = 0.0f;
	m[7] = 0.0f;
	m[3] = 0.0f;
	m[0xf] = 1.0f;
	m[0] = m[5] * m[10] - m[9] * m[6];
	m[1] = m[8] * m[6] - m[4] * m[10];
	m[2] = m[4] * m[9] - m[8] * m[5];
}
