extern unsigned int g_7e1f60;

/* ADDRESS: GOLD 0x004b3a10 */
/* ADDRESS: GOLDTL 0x004b3b80 */

unsigned int __cdecl fcn_004b3b80(unsigned int n)
{
	g_7e1f60 = g_7e1f60 * 0x41c64e6d + 0x3039;
	return *((unsigned short*) &g_7e1f60 + 1) % 0x7fffu % n;
}
