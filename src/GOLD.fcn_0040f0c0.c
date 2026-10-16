int __cdecl m_is_tracked(void *);
void __cdecl fcn_00455750(int);
void __cdecl fcn_00425bf0(int, int, int);

/* ADDRESS: GOLD 0x0040f0c0 */
int __cdecl fcn_0040f0c0(int *p)
{
	int g;

	if (m_is_tracked((void *)*p) != 0) {
		fcn_00455750(*p);
		return 0;
	}
	g = *(int *)0x6332b8;
	fcn_00425bf0(g, *(int *)(g + 0x118), 0x5f29a8);
	return 0;
}
