/* ADDRESS: GOLDTL 0x004f0f60 */
void __cdecl fcn_004f0f60(int a0, int* out)
{
	float p;
	int i;

	if (a0 < 4 && a0 > 0)
		goto body;
	if (a0 >= 4)
		goto big;
	a0 = 0;
	goto body;
big:
	a0 = 4;
body:
	out[0] = a0;
	out[1] = a0 + 2;
	p = (float) a0 * 0.25f + 1.0f;
	for (i = 1; i <= 3; i++) {
		out[i + 1] = (int) ((500.0f * ((float) i * p)) * 32.0f);
		out[i + 4] = (int) ((700.0f * ((float) i * p)) * 32.0f);
	}
}
