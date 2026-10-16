int __cdecl m_alloc(int, int);
void __cdecl fcn_0045d680(int, int);

/* ADDRESS: GOLD 0x0045da20 */
int __cdecl fcn_0045da20(int a, int b, int c)
{
	int s;
	int z;

	z = 0;
	s = m_alloc(0xacc, 0x5fcf90);
	if (s != z) {
		*(int *)(s + 0xaa4) = -1;
		*(int *)(s + 0xac0) = z;
		*(int *)(s + 0xab4) = a;
		*(int *)(s + 0xac4) = *(int *)0x6333cc;
		*(int *)(s + 0xac8) = z;
		*(int *)(s + 0xab8) = b;
		*(int *)(s + 0xabc) = c;
		fcn_0045d680(s, 1);
	}

	return s;
}
