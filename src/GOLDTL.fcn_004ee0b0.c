char* __cdecl fcn_004ecbe0(int id);

/* ADDRESS: GOLDTL 0x004ee0b0 */
int __cdecl fcn_004ee0b0(char* p)
{
	char* q;
	float s;
	float v;
	float alt;

	q = fcn_004ecbe0(*(int*) (p + 0xc));
	v = (float) *(unsigned char*) (p + 4) * 0.003968254f;
	s = v * v;
	v = (float) *(unsigned char*) (p + 5) * 0.003968254f;
	s = s + v * v;
	v = (float) *(unsigned char*) (p + 6) * 0.003968254f;
	s = s + v * v;
	v = (float) *(unsigned char*) (p + 7) * 0.003968254f;
	s = s + v * v;
	alt = q ? *(float*) (q + 8) + *(float*) (q + 4) : 0.0f;
	alt = alt * 500.0f;
	return (int) (alt + s * 500.0f) << 5;
}
