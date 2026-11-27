

void __cdecl gm_GetLawEntry(int, int*);

void __cdecl fcn_004fc5c0(float* out)
{
	int buf[9];
	int i;
	float lo;

	for (i = 9; i <= 15; i++) {
		gm_GetLawEntry(i, buf);
		lo = (float) buf[1];
		out[i] = (buf[6] - lo) / (buf[2] - lo);
	}
}
