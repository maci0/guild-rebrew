// FUNCTION: GOLDTL 0x420ba0
// SIZE: 80

extern int g_14cbcc0[][4];

void __cdecl fcn_00420ba0(unsigned char* p, unsigned int n, char flag)
{
	int k;

	if (p != 0 && n > *p && *p < 0x6a) {
		k = flag ? 0 : 2;
		g_14cbcc0[*p][k]++;
		g_14cbcc0[*p][k + 1] += n;
	}
}
