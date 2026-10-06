// FUNCTION: GOLDTL 0x4f5810

// fcn_004f36e0 — first table (stride 0x2d) index equal to a, else -1.

int __cdecl fcn_004f36e0(int a)
{
	int i;
	int p;
	i = 0;
	p = 0x9a3800;
	while (p < 0x9a9200) {
		if (*(int*) p == a) {
			return i;
		}
		p += 0x2d;
		i++;
	}
	return -1;
}
