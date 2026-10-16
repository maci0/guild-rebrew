void __cdecl fcn_0045d7f0(int owner, int node);
void __cdecl m_FreeTracked(void *ptr);

/* ADDRESS: GOLD 0x0045da90 */
void __cdecl fcn_0045da90(int owner)
{
	int n;

	if (owner == 0)
		return;
	n = *(int *)(owner + 0xac0);
	while (n != 0) {
		fcn_0045d7f0(owner, n);
		n = *(int *)(owner + 0xac0);
	}
	m_FreeTracked((void *)owner);
}
