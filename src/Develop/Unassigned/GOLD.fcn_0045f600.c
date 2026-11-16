void* __cdecl m_alloc(int, int);

/* ADDRESS: GOLD 0x0045f600 */
void __cdecl fcn_0045f600(unsigned int a0)
{
	*(unsigned int*) 0xfb9080 = a0;
	*(int*) 0xfb91b4 = 0;
	*(int*) 0xfb907c = 0;
	if (a0 > 0) {
		*(void**) 0x633f08 = m_alloc(a0 * 20, 0x5fd0b4);
	} else {
		*(void**) 0x633f08 = 0;
	}
}
