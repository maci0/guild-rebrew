int __cdecl m_alloc(int, int);

/* ADDRESS: GOLD 0x0045f600 */
void __cdecl fcn_0045f600(unsigned int a)
{
	*(int*) 0xfb9080 = a;
	*(int*) 0xfb91b4 = 0;
	*(int*) 0xfb907c = 0;
	if (a > 0)
		*(int*) 0x633f08 = m_alloc(a * 20, 0x5fd0b4);
	else
		*(int*) 0x633f08 = 0;
}
