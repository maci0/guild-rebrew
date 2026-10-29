#include <string.h>

extern int __cdecl fcn_0041bac0(char a, char b, char c);

/* ADDRESS: GOLDTL 0x00479830 */
int __cdecl fcn_00479830(unsigned char* src)
{
	unsigned short* out;
	unsigned short* end;
	unsigned char* p;

	if (src == 0) {
		return 0;
	}
	memcpy((void*) 0x100eb80, src, 0x400);
	out = (unsigned short*) 0x100efa0;
	*(int*) 0x100f1b4 = (int) out;
	end = (unsigned short*) 0x100f1a0;
	p = src + 1;
	do {
		*out = (unsigned short) fcn_0041bac0((char) p[-1], (char) p[0], (char) p[1]);
		out++;
		p += 4;
	} while ((int) out < (int) end);
	return 1;
}
