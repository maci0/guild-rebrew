extern float g_6628a0;
#define K_6628A0 g_6628a0
#define K_6628CC 0.5f

typedef struct {
	int i;
	float f[21];
} D3_SPLINE_KEY;

/* ADDRESS: GOLDTL 0x004321f0 */
void __cdecl d3_ComputeSplineTangents(D3_SPLINE_KEY* previous, D3_SPLINE_KEY* current, D3_SPLINE_KEY* next)
{
	float d[4];
	float e[4];
	float s;
	float n1;
	float n0;

	d[0] = current->f[0] - previous->f[0];
	d[1] = current->f[1] - previous->f[1];
	d[2] = current->f[2] - previous->f[2];
	s = K_6628A0 / (float) previous->i;
	d[0] *= s;
	d[1] *= s;
	d[2] *= s;
	e[0] = next->f[0] - current->f[0];
	e[1] = next->f[1] - current->f[1];
	e[2] = next->f[2] - current->f[2];
	n1 = (float) current->i;
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
	current->f[7] = n1 * d[0];
	current->f[8] = n1 * d[1];
	current->f[9] = n1 * d[2];
	n0 = (float) previous->i;
	previous->f[11] = n0 * d[0];
	previous->f[12] = n0 * d[1];
	previous->f[13] = n0 * d[2];
	d[0] = current->f[4] - previous->f[4];
	d[1] = current->f[5] - previous->f[5];
	d[2] = current->f[6] - previous->f[6];
	s = K_6628A0 / n0;
	d[0] *= s;
	d[1] *= s;
	d[2] *= s;
	e[0] = next->f[4] - current->f[4];
	e[1] = next->f[5] - current->f[5];
	e[2] = next->f[6] - current->f[6];
	n1 = (float) current->i;
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
	current->f[15] = n1 * d[0];
	current->f[16] = n1 * d[1];
	current->f[17] = n1 * d[2];
	n0 = (float) previous->i;
	previous->f[18] = n0 * d[0];
	previous->f[19] = n0 * d[1];
	previous->f[20] = n0 * d[2];
}
