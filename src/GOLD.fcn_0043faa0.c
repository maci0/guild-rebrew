/* ADDRESS: GOLD 0x0043faa0 */
int __cdecl fcn_0043faa0(void)
{
	unsigned int *p;
	unsigned int n;
	unsigned int lim;
	unsigned int bestv;
	unsigned int i;
	int *best;
	unsigned int v;
	int obj;

	p = *(unsigned int **)0x63374c;
	n = *(unsigned int *)0x633744;
	lim = *(unsigned int *)0x63343c;
	best = 0;
	i = 0;
	bestv = lim;
	if (n > 0) {
		do {
			if (p[0] == 0) {
				p[1] = lim;
				return (int)p;
			}
			v = p[1];
			if (v < bestv) {
				bestv = v;
				best = (int *)p;
			}
			i++;
			p = (unsigned int *)((char *)p + 0x44);
		} while (i < n);
		if (best != 0) {
			obj = *best;
			best[1] = lim;
			if (obj != 0)
				*(int *)(obj + 0x58) = 0;
		}
	}
	return (int)best;
}
