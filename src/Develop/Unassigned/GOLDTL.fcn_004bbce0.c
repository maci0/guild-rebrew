extern int g_7728e0;


/* ADDRESS: GOLDTL 0x004bbce0 */
unsigned int __cdecl fcn_004bbce0(unsigned int n)
{
	if (n == 0)
		return 0;
	(*(unsigned int*)&g_7728e0) = (*(unsigned int*)&g_7728e0) * 0x41c64e6d + 0x3039;
	return *((unsigned short*) &(*(unsigned int*)&g_7728e0) + 1) % 0x7fffu % n;
}
