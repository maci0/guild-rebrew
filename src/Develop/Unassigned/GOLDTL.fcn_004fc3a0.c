

void __cdecl fcn_004f4830(int, int*);

/* k indexes both arrays, so the out address is derived from the weight
   pointer; the product goes through a float temporary, so its load issues
   before the out store. */
/* ADDRESS: GOLD 0x4f9d40 */
float __cdecl fcn_004fc3a0(int* out)
{
	float sum = 0;
	int buf[9];
	float w[12] = {0.06f, 0.05f, 0.08f, 0.04f, 0.13f, 0.1f, 0.13f, 0.12f, 0.14f, 0.15f};
	float f;
	int i;
	int k;

	for (k = 0, i = 0x11; i < 0x1d; i++, k++) {
		fcn_004f4830(i, buf);
		f = buf[6] * w[k];
		out[k] = buf[6];
		sum += f;
	}
	return sum;
}
