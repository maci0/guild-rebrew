// FUNCTION: GOLD 0x00509df0
// FUNCTION: GOLDTL 0x0050d200

int __cdecl fcn_0050d170(int k);
int __cdecl fcn_004f4830(int k, int* info);

int __cdecl fcn_0050d200(unsigned char* p, int k)
{
	int info[9];
	int total;
	float m;

	total = fcn_0050d170(k);
	m = 0.85f;
	if (p[0x166] != 0xe) {
		m = 1.0f;
	}
	fcn_004f4830(6, info);
	return (int) (((4 - info[6]) * 0.1f + 0.8f) * total * m);
}
