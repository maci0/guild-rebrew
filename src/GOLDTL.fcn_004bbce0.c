extern unsigned int g_7728e0;

// FUNCTION: GOLDTL 0x4bbce0
// SIZE: 60

unsigned int __cdecl fcn_004bbce0(unsigned int n)
{
	if (n == 0)
		return 0;
	g_7728e0 = g_7728e0 * 0x41c64e6d + 0x3039;
	return *((unsigned short*) &g_7728e0 + 1) % 0x7fffu % n;
}
