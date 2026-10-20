char* __cdecl fcn_004ecbe0(int id);

/* ADDRESS: GOLDTL 0x004ee0b0 */
int __cdecl fcn_004ee0b0(char* p)
{
	char* q;
	float a;
	float b;
	float c;
	float d;
	float s;
	float alt;

	q = fcn_004ecbe0(*(int*) (p + 0xc));
	alt = q ? *(float*) (q + 8) + *(float*) (q + 4) : 0.0f;
	a = (float) *(unsigned char*) (p + 4) * 0.003968254f;
	b = (float) *(unsigned char*) (p + 5) * 0.003968254f;
	c = (float) *(unsigned char*) (p + 6) * 0.003968254f;
	d = (float) *(unsigned char*) (p + 7) * 0.003968254f;
	s = a * a;
	s = s + b * b;
	s = s + c * c;
	s = s + d * d;
	return (int) (alt * 500.0f + s * 500.0f) << 5;
}
