#include <stdlib.h>

extern void* __cdecl fcn_0064e2f9(const char*, const char*);
extern int __cdecl fcn_0064e48f(void*, int, int);
extern int __cdecl fcn_0064ebe4(void*, int, int, void*);
extern int __cdecl fcn_0064e1fd(void*);

/* ADDRESS: GOLDTL 0x004758b0 */
int __cdecl fcn_004758b0(char* name, unsigned char* pix)
{
	unsigned char hdr[0x28];
	unsigned char* p;
	unsigned char t;
	void* f;
	int i;
	int n;
	int align;
	int rev;
	int row;

	f = fcn_0064e2f9(name, (char*) 0x6750e8);
	if (f == 0) {
		return 0;
	}
	fcn_0064e48f(f, 0xe, 0);
	fcn_0064ebe4(hdr, 1, 0x28, f);
	fcn_0064e48f(f, *(int*) (hdr + 0x20) * 4 + 0x36, 0);
	if (*(int*) (hdr + 0x10) != 0 || *(unsigned short*) (hdr + 0xc) != 1
	    || *(unsigned short*) (hdr + 0xe) != 0x18) {
		fcn_0064e1fd(f);
		return 1;
	}
	n = *(int*) (hdr + 8);
	rev = n >= 0;
	*(int*) (hdr + 8) = abs(n);
	align = (*(int*) (hdr + 4) * 3) & 3;
	for (i = 0; i < *(int*) (hdr + 8); i++) {
		row = rev ? i : *(int*) (hdr + 8) - i - 1;
		fcn_0064ebe4(pix + row * *(int*) (hdr + 4) * 3, 1,
			*(int*) (hdr + 4) * 3, f);
		if (align != 0) {
			fcn_0064e48f(f, 4 - align, 1);
		}
	}
	fcn_0064e1fd(f);
	p = pix + 2;
	for (i = *(int*) (hdr + 4) * *(int*) (hdr + 4); i > 0; i--) {
		t = p[-2];
		p[-2] = p[0];
		p[0] = t;
		p += 3;
	}
	return 1;
}
