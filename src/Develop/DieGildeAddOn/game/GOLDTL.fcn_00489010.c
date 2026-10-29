/* 0x21c-stride entity-table sweep from 0x7f4ca0 to 0x85a0a0: matches the
   record whose owner pointer equals the driver's, resolves its type row
   through 0x100e764/0x100e724 and reports the 0x39 event. */

int __cdecl fcn_00502cd0(int, int, int, int);
int __cdecl fcn_004ce590(int);
int __cdecl fcn_005c7270(int, int);
void __cdecl fcn_004c51f0(int, int, int, int, char, int);
int __cdecl sprintf(char*, char*, ...);

/* ADDRESS: GOLDTL 0x00489010 */
void __cdecl fcn_00489010(char* e)
{
	char buf[0x400];
	char* p;
	char* n;
	char* a;
	char* b;
	char* found;
	char* tbl;
	int i;
	int k;
	int idx;

	p = (char*) 0x7f4e24;
	do {
		if (*(unsigned short*) (p - 0x184) == 0xffff
		    || *(char**) (p - 0x18) != *(char**) (e + 0x16c)
		    || *(char*) (p - 0x1f) == 0
		    || *(char**) p == 0
		    || *(int*) (*(char**) p + 0x2c) != *(int*) (*(char**) (p - 0x18) + 1)) {
			goto next;
		}
		n = (char*) fcn_00502cd0(*(int*) (p - 0xc), 1, 4, 0xc);
		if (n == 0) {
			return;
		}
		found = 0;
		for (b = (char*) 0x100e764, a = (char*) 0x100b100;; b += 4, a += 0x40) {
			if (*(int*) (b - 4) == 0 || *(int*) b == 0) {
				break;
			}
			k = *(unsigned short*) n;
			*(int*) (b - 4) = k;
			if (k != 0 && found == 0) {
				for (i = 0; i < *(int*) 0x100b0a8; i++) {
					if (*(int*) (0x100b0c0 + i * 0x40) == *(int*) b) {
						found = a;
						break;
					}
				}
			}
			b += 4;
			a += 0x40;
			if (found != 0) {
				break;
			}
		}
		if (found == 0) {
			for (b = (char*) 0x100e724, a = (char*) 0x100b100;; b += 4, a += 0x40) {
				if (*(int*) (b - 4) == 0 || *(int*) b == 0) {
					break;
				}
				k = *(unsigned short*) n;
				*(int*) (b - 4) = k;
				if (k != 0 && found == 0) {
					for (i = 0; i < *(int*) 0x100b0a8; i++) {
						if (*(int*) (0x100b0c0 + i * 0x40) == *(int*) b) {
							found = a;
							break;
						}
					}
				}
				b += 4;
				a += 0x40;
				if (found != 0) {
					break;
				}
			}
		}
		if (found != 0 && *(int*) (found + 0x28) != 0
		    && fcn_004ce590(*(int*) found) != 0
		    && fcn_005c7270((int) e, *(int*) found) != 0) {
			idx = *(int*) found;
			tbl = *(char**) 0x99ec10;
			sprintf(buf, (char*) 0x67e388, e + 0x30, p - 0x154,
			        tbl + idx * 0x41 + 1);
			sprintf(buf + 0x14, (char*) 0x67e358, *(int*) (p - 0x180),
			        *(int*) (e + 2), idx, 1, *(unsigned char*) 0x773d75, 0);
			fcn_004c51f0(*(int*) (p - 0x180), *(int*) (e + 2), idx, 1,
			             *(unsigned char*) 0x773d75, 0);
			*(int*) (found + 0x28) = *(int*) (found + 0x28) - 1;
		}
next:
		p += 0x21c;
	} while (p < (char*) 0x85a224);
}
