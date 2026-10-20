void __cdecl m_FreeTracked(int);

/* ADDRESS: GOLD 0x0042ebc0 */
void __cdecl fcn_0042ebc0(void)
{
	int p;

	p = *(int *)0x6333f8;
	if (p == 0 || (unsigned int)p < *(unsigned int *)0x6333f0) {
		__asm {
			int 3
		}
		return;
	}
	m_FreeTracked(p);
	*(int *)0x6333f0 = 0;
	*(int *)0x6333f4 = 0;
	*(int *)0x6333f8 = 0;
}
