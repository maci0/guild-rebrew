// FUNCTION: GOLDTL 0x004fc520
// SIZE: 154

int __cdecl fcn_004f4830(int k, int* info);

float __cdecl fcn_004fc520(void)
{
	float w[7] = {0.3f, 0.25f, 0.12f, 0.1f, 0.05f, 0.08f, 0.1f};
	float sum = 0.0f;
	int info[9];
	float lo;
	float t;
	int k;

	for (k = 9; k <= 0xf; k++) {
		fcn_004f4830(k, info);
		lo = (float) info[1];
		t = (1.0 - (info[6] - lo) / (info[2] - lo)) * w[k - 9];
		sum += t;
	}
	return t + sum;
}
