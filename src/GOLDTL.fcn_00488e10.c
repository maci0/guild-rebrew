#include <string.h>

#pragma intrinsic(memcpy, memset)

extern unsigned char* g_868050;

void __cdecl fcn_004c5530(int a1);
char* __cdecl fcn_00502cd0(int, int, int, int, int);

/* ADDRESS: GOLDTL 0x00488e10 */
void __cdecl fcn_00488e10(char* e)
{
	char s[0xf8];
	char* p;
	char* q;
	char* r;
	char* o;
	unsigned char f;
	int cnt;

	cnt = 1;
	p = (char*) 0x7f4ca0;
	do {
		if (*(unsigned short*) p != 0xffff
		    && *(int*) (p + 0x16c) == *(int*) (e + 0x16c)
		    && *(char*) (p + 0x165) != 0
		    && (q = *(char**) (p + 0x17c)) != 0
		    && *q == 0x8f) {
			cnt--;
		}
		p += 0x21c;
	} while ((int) p < 0x85a0a0);
	if (cnt <= 0) {
		return;
	}
	q = *(char**) (e + 0x16c);
	if (g_868050[*(unsigned char*) q * 0x24d] != 0x1d) {
		return;
	}
	r = fcn_00502cd0(*(int*) (q + 0x5d), 2, 6, 0, 0x211);
	if (r == 0) {
		return;
	}
	memset(s, 0, 0xf8);
	*(char*) (s + 4) = 0x8f;
	*(int*) (s + 8) = *(int*) (*(unsigned short*) (q + 0x27) * 0x21c + 0x7f4ca4);
	*(int*) (s + 0xc) = *(int*) (q + 1);
	*(int*) (s + 0x28) = *(int*) 0x7f4c00;
	*(int*) (s + 0x2c) = *(int*) 0x7f4c04;
	*(int*) (s + 0x30) = *(int*) 0x7f4c08;
	*(unsigned short*) (s + 0x34) = *(unsigned short*) 0x7f4c0c;
	*(char*) (s + 0x36) = 1;
	*(int*) (s + 0x60) = *(int*) (r + 2);
	p = (char*) 0x7f4ca0;
	do {
		if ((int) p >= 0x85a0a0) {
			break;
		}
		if (*(unsigned short*) p == 0xffff) {
			goto next;
		}
		if (*(int*) (p + 0x16c) != *(int*) (e + 0x16c)) {
			goto next;
		}
		if (*(char*) (p + 0x165) == 0) {
			goto next;
		}
		f = *(unsigned char*) (p + 0x1b4);
		if ((f & 0x10) == 0) {
			goto next;
		}
		o = *(char**) (p + 0x17c);
		if (o != 0) {
			if (*o != 0x8f) {
				goto next;
			}
			*(unsigned char*) (p + 0x1b4) = f & 0xef;
			goto next;
		}
		o = *(char**) (p + 0x184);
		if (o == 0) {
			goto next;
		}
		if (*(int*) (o + 0x2c) != *(int*) (*(char**) (p + 0x16c) + 1)) {
			goto next;
		}
		*(unsigned char*) (p + 0x1b4) = f & 0xef;
		if (*(unsigned char*) (p + 0x81) < *(unsigned char*) (p + 0x82)) {
			*(int*) (s + 0x58) = *(int*) (p + 4);
			*(int*) (s + 0x5c) = 1;
		} else {
			*(int*) (s + 0x58) = *(int*) (p + 4);
			*(int*) (s + 0x5c) = 2;
			if (*(unsigned char*) (p + 0x82) >= *(unsigned char*) (p + 0x84)) {
				*(int*) (s + 0x60) = 4;
			}
		}
		fcn_004c5530((int) s);
		cnt--;
		*(int*) (p + 0x1c8) |= 4;
next:
		p += 0x21c;
	} while (cnt > 0);
}
