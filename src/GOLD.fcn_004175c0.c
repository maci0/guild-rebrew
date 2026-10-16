void __cdecl m_FreeTracked(int);

/* ADDRESS: GOLD 0x004175c0 */
void __cdecl fcn_004175c0(void)
{
	int p;

	for (p = 0x14661e4; p < 0x1466640; p += 0x7c) {
		m_FreeTracked(*(int *)p);
		*(int *)p = 0;
	}
	for (p = 0x1466ac4; p < 0x1466f20; p += 0x7c) {
		m_FreeTracked(*(int *)p);
		*(int *)p = 0;
	}
	for (p = 0x1466f24; p < 0x1467380; p += 0x7c) {
		m_FreeTracked(*(int *)p);
		*(int *)p = 0;
	}
	for (p = 0x1466664; p < 0x1466ac0; p += 0x7c) {
		m_FreeTracked(*(int *)p);
		*(int *)p = 0;
	}
}
