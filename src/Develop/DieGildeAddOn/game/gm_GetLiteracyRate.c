


int __cdecl gm_GetLawEntry(int k, int* info);

/* ADDRESS: GOLDDE 0x004e8090 */
float __cdecl gm_GetJusticeRating(void)
{
	float w[7] = {0.3f, 0.25f, 0.12f, 0.1f, 0.05f, 0.08f, 0.1f};
	float sum = 0.0f;
	int info[9];
	float lo;
	float t;
	int k;

	for (k = 9; k <= 0xf; k++) {
		gm_GetLawEntry(k, info);
		lo = (float) info[1];
		t = (float)((1.0 - (info[6] - lo) / (info[2] - lo)) * w[k - 9]);
		sum += t;
	}
	return t + sum;
}
