void __cdecl m_FreeTracked(int);
int __cdecl m_alloc(int, int);

/* ADDRESS: GOLD 0x0043cc10 */
void __cdecl fcn_0043cc10(int p)
{
	int a;
	int n;

	if (*(int *)(p + 8) == 0)
		return;
	if (*(int *)(p + 0xc) == 0)
		return;
	a = *(int *)(p + 4);
	if (a != 0) {
		m_FreeTracked(a);
		*(int *)(p + 4) = 0;
	}
	*(int *)(p + 4) = m_alloc(*(int *)(p + 0xc) * 40, 0x5fb6f4);
	a = *(int *)p;
	if (a != 0) {
		m_FreeTracked(a);
		*(int *)p = 0;
	}
	n = *(int *)(p + 8) + 8;
	*(int *)p = m_alloc(n * 80, 0x5fb6dc);
}
