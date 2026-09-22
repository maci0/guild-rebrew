// FUNCTION: GOLDTL 0x4c27f0
// SIZE: 34

int __cdecl fcn_004c27f0(void)
{
	int i;
	int v;
	char* p;

	i = 0;
	p = (char*) 0x688118;
	do {
		if (p[0x112] != 0) {
			return i;
		}
		v = *(int*) p;
		i++;
		p += 0x114;
	} while (v != 0);
	return -1;
}
