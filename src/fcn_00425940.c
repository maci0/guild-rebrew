// FUNCTION: GOLDTL 0x425940
// SIZE: 38

int __cdecl fcn_00425940(void)
{
	int count;
	int i;
	int base;
	char* p;

	count = 0;
	base = *(int*) 0x6b7e88;
	if (base != 0) {
		i = *(int*) 0x6b7e8c;
		if (i > 0) {
			p = (char*) (base + 0x14);
			for (; i != 0; i--) {
				if (*(unsigned char*) p & 0x10) {
					count++;
				}
				p += 0x30;
			}
		}
	}
	return count;
}
