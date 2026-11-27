/* ADDRESS: GOLDTL 0x004f0f60 */
void __cdecl gm_ComputeCannonShotStats(int value, int* out)
{
	float p;
	int i;
	int v;

	if (value < 4 && value > 0)
		goto keep;
	if (value >= 4)
		goto big;
	v = 0;
	goto body;
big:
	v = 4;
	goto body;
keep:
	v = value;
body:
	out[0] = v;
	out[1] = v + 2;

	for (i = 1; i <= 3; i++) { p = (float) v * 0.25f + 1.0f;
		out[i + 1] = (int) ((500.0f * ((float) i * p)) * 32.0f);
		out[i + 4] = (int) ((700.0f * ((float) i * p)) * 32.0f);
	}
}
