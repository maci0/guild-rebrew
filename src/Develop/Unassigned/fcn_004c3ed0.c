/* ADDRESS: GOLDTL 0x004c3ed0 */
void __cdecl fcn_004c3ed0(void)
{
	char* rec;
	char* e;
	int i;
	int z;
	int one;

	z = 0;
	for (i = 0; i < 0x2000; i++) {
		rec = (char*) 0x9bade0 + i * 0x99;
		rec[0] = (char) z;
		if (i == 0) {
			*(int*) 0x9bae71 = z;
			*(int*) (rec + 0x95) = (int) (rec + 0x99);
		} else {
			*(int*) (rec + 0x91) = (int) (rec - 0x99);
			if (i < 0x1fff) {
				*(int*) (rec + 0x95) = (int) (rec + 0x99);
			} else {
				*(int*) (rec + 0x95) = z;
			}
		}
	}
	*(int*) 0xaed200 = 0x9bade0;
	*(int*) 0xaed324 = z;
	*(char*) 0x1005780 = (char) z;
	*(int*) 0x1005768 = z;
	*(int*) 0x1005760 = z;
	one = -1;
	for (e = (char*) 0xfb5760; (int) e < (int) 0x1005760; e += 0xa) {
		*(int*) (e + 2) = one;
		e[0] = 1;
	}
}
