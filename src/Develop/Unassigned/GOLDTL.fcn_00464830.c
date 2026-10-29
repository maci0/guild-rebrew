#include <stdio.h>

/* ADDRESS: GOLDTL 0x00464830 */
int __cdecl fcn_00464830(FILE* fin, int* pi)
{
	unsigned char c;
	int err = fread(&c, 1, 1, fin);

	if (err == 1) {
		*pi = (int) c;
		return 0;
	} else {
		if (ferror(fin)) {
			return -1;
		} else {
			return 0;
		}
	}
}
