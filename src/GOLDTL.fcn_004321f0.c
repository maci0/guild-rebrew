#define K_6628A0 (*(float*) 0x6628a0)
#define K_6628CC (*(float*) 0x6628cc)

/* ADDRESS: GOLDTL 0x004321f0 */
void __cdecl fcn_004321f0(float* a0, float* a1, float* a2)
{
	float v1;
	float v2;
	float v3;
	float v4;
	float v5;

	v1 = K_6628A0 / *a0;
	v2 = *a1;
	v5 = K_6628A0 / v2;
	v3 = ((a2[1] - a1[1]) * v5 + v1 * (a1[1] - a0[1])) * K_6628CC;
	v4 = ((a2[2] - a1[2]) * v5 + v1 * (a1[2] - a0[2])) * K_6628CC;
	v5 = ((a2[3] - a1[3]) * v5 + v1 * (a1[3] - a0[3])) * K_6628CC;
	a1[8] = v2 * v3;
	a1[9] = v2 * v4;
	a1[10] = v2 * v5;
	v1 = *a0;
	a0[0xc] = *a0 * v3;
	a0[0xd] = v1 * v4;
	a0[0xe] = v1 * v5;
	v1 = K_6628A0 / v1;
	v2 = *a1;
	v5 = K_6628A0 / v2;
	v3 = ((a2[5] - a1[5]) * v5 + v1 * (a1[5] - a0[5])) * K_6628CC;
	v4 = ((a2[6] - a1[6]) * v5 + v1 * (a1[6] - a0[6])) * K_6628CC;
	v5 = ((a2[7] - a1[7]) * v5 + v1 * (a1[7] - a0[7])) * K_6628CC;
	a1[0x10] = v2 * v3;
	a1[0x11] = v2 * v4;
	a1[0x12] = v2 * v5;
	v1 = *a0;
	a0[0x13] = *a0 * v3;
	a0[0x14] = v1 * v4;
	a0[0x15] = v1 * v5;
}
