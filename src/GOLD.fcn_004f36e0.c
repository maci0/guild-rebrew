/* ADDRESS: GOLD 0x004f36e0 */
// fcn_004f36e0 — first table (stride 0x2d) index equal to a, else -1.

int __cdecl fcn_004f36e0(int a)
{
	int i;
	int p;
	i = 0;
	p = 0x91f700;
	while (p < 0x925100) {
		if (*(int*) p == a) {
			return i;
		}
		p += 0x2d;
		i++;
	}
	return -1;
}
