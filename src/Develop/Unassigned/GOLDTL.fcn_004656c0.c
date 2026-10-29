#include <stdio.h>

/* ADDRESS: GOLDTL 0x004656c0 */
int __cdecl fcn_004656c0(char* s, char* comment, unsigned long size_buf)
{
	unsigned long read_this;

	if (s == 0) {
		return -102;
	}
	read_this = size_buf;
	if (read_this > *(unsigned long*) (s + 8)) {
		read_this = *(unsigned long*) (s + 8);
	}
	if (fseek(*(FILE**) s, *(unsigned long*) (s + 0x1c) + 22, SEEK_SET) != 0) {
		return -1;
	}
	if (read_this > 0) {
		*comment = '\0';
		if (fread(comment, (unsigned int) read_this, 1, *(FILE**) s) != 1) {
			return -1;
		}
	}
	if (comment != 0 && size_buf > *(unsigned long*) (s + 8)) {
		*(comment + *(unsigned long*) (s + 8)) = '\0';
	}
	return (int) read_this;
}
