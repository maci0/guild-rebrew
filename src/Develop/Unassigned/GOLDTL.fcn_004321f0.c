extern float g_6628a0;
#define K_6628A0 g_6628a0
#define K_6628CC 0.5f

typedef struct {
	int i;
	float f[21];
} F4321F0;

/* ADDRESS: GOLDTL 0x004321f0 */
void __cdecl fcn_004321f0(F4321F0* a0, F4321F0* a1, F4321F0* a2)
{
	float d[4];
	float e[4];
	float s;
	float n1;
	float n0;

	d[0] = a1->f[0] - a0->f[0];
	d[1] = a1->f[1] - a0->f[1];
	d[2] = a1->f[2] - a0->f[2];
	s = K_6628A0 / (float) a0->i;
	d[0] *= s;
	d[1] *= s;
	d[2] *= s;
	e[0] = a2->f[0] - a1->f[0];
	e[1] = a2->f[1] - a1->f[1];
	e[2] = a2->f[2] - a1->f[2];
	n1 = (float) a1->i;
	s = K_6628A0 / n1;
	e[0] *= s;
	e[1] *= s;
	e[2] *= s;
	d[0] = e[0] + d[0];
	d[1] = e[1] + d[1];
	d[2] = e[2] + d[2];
	d[0] = d[0] * K_6628CC;
	d[1] = d[1] * K_6628CC;
	d[2] = d[2] * K_6628CC;
	a1->f[7] = n1 * d[0];
	a1->f[8] = n1 * d[1];
	a1->f[9] = n1 * d[2];
	n0 = (float) a0->i;
	a0->f[11] = n0 * d[0];
	a0->f[12] = n0 * d[1];
	a0->f[13] = n0 * d[2];
	d[0] = a1->f[4] - a0->f[4];
	d[1] = a1->f[5] - a0->f[5];
	d[2] = a1->f[6] - a0->f[6];
	s = K_6628A0 / n0;
	d[0] *= s;
	d[1] *= s;
	d[2] *= s;
	e[0] = a2->f[4] - a1->f[4];
	e[1] = a2->f[5] - a1->f[5];
	e[2] = a2->f[6] - a1->f[6];
	n1 = (float) a1->i;
	s = K_6628A0 / n1;
	e[0] *= s;
	e[1] *= s;
	e[2] *= s;
	d[0] = e[0] + d[0];
	d[1] = e[1] + d[1];
	d[2] = e[2] + d[2];
	d[0] = d[0] * K_6628CC;
	d[1] = d[1] * K_6628CC;
	d[2] = d[2] * K_6628CC;
	a1->f[15] = n1 * d[0];
	a1->f[16] = n1 * d[1];
	a1->f[17] = n1 * d[2];
	n0 = (float) a0->i;
	a0->f[18] = n0 * d[0];
	a0->f[19] = n0 * d[1];
	a0->f[20] = n0 * d[2];
}
