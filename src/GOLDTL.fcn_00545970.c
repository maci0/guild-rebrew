// FUNCTION: GOLDTL 0x545970

int __cdecl fcn_00545970(int a1)
{
	int i;
	int n;

	n = 0;
	for (i = 0; i < 768; i++) {
		if (*(unsigned char*) (0x7f4ca2 + i * 0x21c) == 6) {
			if (i == a1) {
				return n;
			}
			n++;
		}
	}
	return -1;
}
