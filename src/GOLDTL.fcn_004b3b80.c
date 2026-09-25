extern unsigned int g_7e1f60;

// FUNCTION: GOLD 0x004b3a10
// SIZE: 49
// FUNCTION: GOLDTL 0x4b3b80
// SIZE: 49

unsigned int __cdecl fcn_004b3b80(unsigned int n)
{
	g_7e1f60 = g_7e1f60 * 0x41c64e6d + 0x3039;
	return *((unsigned short*) &g_7e1f60 + 1) % 0x7fffu % n;
}
