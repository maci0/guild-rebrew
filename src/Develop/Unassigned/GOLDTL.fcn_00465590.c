#include <stdio.h>

/* ADDRESS: GOLDTL 0x00465590 */
int __cdecl fcn_00465590(char* s, void* buf, unsigned int len)
{
	char* p;
	unsigned int read_now;
	unsigned long size_to_read;

	if (s == 0) {
		return -102;
	}
	p = *(char**) (s + 0x7c);
	if (p == 0) {
		return -102;
	}
	size_to_read = *(unsigned long*) (p + 0x48) - *(unsigned long*) (p + 0x4c);
	if (buf == 0) {
		return (int) size_to_read;
	}
	if (len > size_to_read) {
		read_now = (unsigned int) size_to_read;
	} else {
		read_now = len;
	}
	if (read_now == 0) {
		return 0;
	}
	if (fseek(*(FILE**) (p + 0x60), *(unsigned long*) (p + 0x44) + *(unsigned long*) (p + 0x4c), SEEK_SET) != 0) {
		return -1;
	}
	if (fread(buf, (unsigned int) size_to_read, 1, *(FILE**) (p + 0x60)) != 1) {
		return -1;
	}
	return (int) read_now;
}
