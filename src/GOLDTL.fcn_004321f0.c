#define K_6628A0 (*(float*) 0x6628a0)
#define K_6628CC (*(float*) 0x6628cc)

typedef struct {
	int i;
	float f[21];
} F4321F0;

/* ADDRESS: GOLDTL 0x004321f0 */
void __cdecl fcn_004321f0(F4321F0* a0, F4321F0* a1, F4321F0* a2)
{
	float v1;
	float v2;
	float v3;
	float v4;
	float v5;

	v1 = K_6628A0 / (float) a0->i;
	v3 = (a1->f[0] - a0->f[0]) * v1;
	v4 = (a1->f[1] - a0->f[1]) * v1;
	v5 = (a1->f[2] - a0->f[2]) * v1;
	v2 = (float) a1->i;
	v1 = K_6628A0 / v2;
	v3 = ((a2->f[0] - a1->f[0]) * v1 + v3) * K_6628CC;
	v4 = ((a2->f[1] - a1->f[1]) * v1 + v4) * K_6628CC;
	v5 = ((a2->f[2] - a1->f[2]) * v1 + v5) * K_6628CC;
	a1->f[7] = v2 * v3;
	a1->f[8] = v2 * v4;
	a1->f[9] = v2 * v5;
	v1 = (float) a0->i;
	a0->f[11] = v1 * v3;
	a0->f[12] = v1 * v4;
	a0->f[13] = v1 * v5;
	v1 = K_6628A0 / v1;
	v3 = (a1->f[4] - a0->f[4]) * v1;
	v4 = (a1->f[5] - a0->f[5]) * v1;
	v5 = (a1->f[6] - a0->f[6]) * v1;
	v2 = (float) a1->i;
	v1 = K_6628A0 / v2;
	v3 = ((a2->f[4] - a1->f[4]) * v1 + v3) * K_6628CC;
	v4 = ((a2->f[5] - a1->f[5]) * v1 + v4) * K_6628CC;
	v5 = ((a2->f[6] - a1->f[6]) * v1 + v5) * K_6628CC;
	a1->f[15] = v2 * v3;
	a1->f[16] = v2 * v4;
	a1->f[17] = v2 * v5;
	v1 = (float) a0->i;
	a0->f[18] = v1 * v3;
	a0->f[19] = v1 * v4;
	a0->f[20] = v1 * v5;
}
