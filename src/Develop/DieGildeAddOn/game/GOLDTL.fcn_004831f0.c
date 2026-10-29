#include <string.h>

struct unit;

struct unit* __cdecl fcn_005463a0(int n, ...);
int __cdecl gm_RandomMod(unsigned short n);
unsigned char* __cdecl fcn_004f43b0(char* e, unsigned char lim);
int __cdecl fcn_004f1790(char* a, void* e);
void __cdecl fcn_004c5530(int a1);

/* ADDRESS: GOLDTL 0x004831f0 */
void __cdecl fcn_004831f0(char* obj)
{
	char* p;
	char* e;
	char* found;
	char* parent;
	char* q;
	char* r;
	int mode;
	char s[0xf8];

	mode = *(int*) 0x7f4c04;
	if ((short) mode != 7 && (short) mode != 0xc && (short) mode != 0x12) {
		*(int*) (obj + 0x1b4) &= ~0x800;
		return;
	}
	if (*(int*) (obj + 0x1b4) & 0x800) {
		return;
	}
	*(int*) (obj + 0x1b4) |= 0x800;
	if (fcn_005463a0(2, 0, 0x8d, 3, *(int*) ((char*) *(int*) (obj + 0x16c) + 1)) != 0) {
		return;
	}
	e = (char*) fcn_004f43b0((char*) *(int*) (obj + 0x16c),
	    (unsigned char) (gm_RandomMod(0x40) + 0x80));
	if (e == 0) {
		return;
	}
	found = 0;
	p = (char*) 0x7f4ca0;
	do {
		if ((int) p >= 0x85a0a0) {
			break;
		}
		if (*(unsigned short*) p != 0xffff) {
			parent = (char*) *(int*) (p + 0x16c);
			if (parent == (char*) *(int*) (obj + 0x16c)) {
				if (*(char*) (p + 0x165) != 0) {
					q = *(char**) (p + 0x17c);
					if (q == 0 || *q == 4 || *q == 0x8c) {
						r = (char*) *(int*) (p + 0x184);
						if (r != 0 && *(int*) (r + 0x2c) == *(int*) (parent + 1)) {
							found = p;
						}
					}
				}
			}
		}
		p += 0x21c;
	} while (found == 0);
	if (found == 0) {
		return;
	}
	{
		char* c;

		memset(s, 0, sizeof(s));
		c = (char*) *(int*) (obj + 0x16c);
		*(char*) (s + 4) = 0x8d;
		*(int*) (s + 8) = *(int*) (*(unsigned short*) (c + 0x27) * 0x21c + 0x7f4ca4);
		*(int*) (s + 0xc) = *(int*) (c + 1);
		*(int*) (s + 0x28) = *(int*) 0x7f4c00;
		*(int*) (s + 0x2c) = *(int*) 0x7f4c04;
		*(int*) (s + 0x30) = *(int*) 0x7f4c08;
		*(unsigned short*) (s + 0x34) = *(unsigned short*) 0x7f4c0c;
		*(char*) (s + 0x36) = 1;
		*(int*) (s + 0x5c) = *(int*) e;
		*(char*) (s + 0x60) = (char) fcn_004f1790(*(char**) (c + 0x65), e);
		*(int*) (s + 0x38) = *(int*) (found + 4);
		fcn_004c5530((int) s);
	}
}
