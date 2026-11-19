/* ADDRESS: GOLDTL 0x004f0f60 */
void __cdecl fcn_004f0f60(int value, int* out)
{
	float p;
	int i;

	if (value < 4 && value > 0)
		goto body;
	if (value >= 4)
		goto big;
	value = 0;
	goto body;
big:
	value = 4;
body:
	out[0] = value;
	out[1] = value + 2;

	for (i = 1; i <= 3; i++) { p = (float) value * 0.25f + 1.0f;
		out[i + 1] = (int) ((500.0f * ((float) i * p)) * 32.0f);
		out[i + 4] = (int) ((700.0f * ((float) i * p)) * 32.0f);
	}
}
