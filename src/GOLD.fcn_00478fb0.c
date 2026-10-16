int __cdecl fcn_004790d0(int);
void __cdecl m_FreeTracked(int);
void __cdecl fcn_0041e720(int);

/* ADDRESS: GOLD 0x00478fb0 */
int __cdecl fcn_00478fb0(int p)
{
	int a;

	if (p == 0)
		return 0;
	if (*(int *)(p + 0x34) != 0)
		fcn_004790d0(p);
	if (*(int *)(p + 0x38) == 0) {
		a = *(int *)(p + 0x1c);
		if (a != 0) {
			m_FreeTracked(a);
			*(int *)(p + 0x1c) = 0;
		}
		a = *(int *)(p + 0x20);
		if (a != 0)
			fcn_0041e720(a);
	}
	m_FreeTracked(p);
	return 1;
}
