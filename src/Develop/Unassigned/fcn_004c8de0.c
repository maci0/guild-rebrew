int __cdecl fcn_004c4dc0(int a, int b);
#define SLOT_DWORD(off) (*(int*) ((char*) 0x7f4ca0 + (off) + 4))
#define SLOT_WORD(off)  (*(unsigned short*) ((char*) 0x7f4ca0 + (off)))

/* Updates one slot's relation matrix for the given update kind and mode.
 * Native body: 889 bytes at 0x004c8de0. */
/* ADDRESS: GOLDTL 0x004c8de0 */
int __cdecl fcn_004c8de0(int* a, unsigned char* changed)
{
	char* p;
	int* t;
	int i;
	int j;
	int r1;
	int idx5;
	int idx4;
	unsigned int mode;
	int kind;
	int e;
	int v;
	int hi;
	int lo;
	int hiadd;
	int loadd;

	t = a;
	r1 = fcn_004c4dc0((int) t, t[4]);
	t[4] = r1;
	idx5 = fcn_004c4dc0((int) t, t[5]);
	t[5] = idx5;
	kind = t[7];

	if (kind == 4) {
		mode = t[9];
		if (mode == 0) {
			hi = 0x64; lo = -0x4b; hiadd = -5; loadd = 0xb;
		} else if (mode >= 4) {
			hi = 0x28; lo = -0x73; hiadd = -0x14; loadd = 3;
		} else if (mode == 3) {
			hi = 0x37; lo = -0x69; hiadd = -0x10; loadd = 5;
		} else if (mode == 2) {
			hi = 0x46; lo = -0x5f; hiadd = -0xc; loadd = 7;
		} else if (mode == 1) {
			hi = 0x55; lo = -0x55; hiadd = -8; loadd = 9;
		} else {
			hi = 0x64; lo = -0x4b; hiadd = -5; loadd = 0xb;
		}
		for (i = 0; i < 0x300; i++) {
			p = (char*) 0x869480 + i * 0x300;
			for (j = 0; j < 0x300; j++) {
				if (i != j && SLOT_WORD(i * 0x21c) != 0xffff &&
				    SLOT_WORD(j * 0x21c) != 0xffff) {
					v = (signed char) p[j];
					if (v > hi) {
						v += hiadd;
					} else if (v < lo) {
						v += loadd;
					}
					if (v <= -0x7f) {
						v = -0x7f;
					} else if (v >= 0x7f) {
						v = 0x7f;
					}
					p[j] = (signed char) v;
				}
			}
		}
	} else {
		idx4 = 0;
		for (i = 0; i < 0x65400; i += 0x21c) {
			if (SLOT_DWORD(i) == idx5) {
				break;
			}
			idx4++;
		}
		if (i >= 0x65400) {
			return 1;
		}
		if (idx4 >= 0x300) {
			return 1;
		}
		if (SLOT_WORD(idx4 * 0x21c) == 0xffff) {
			return 1;
		}
		if (kind == 3) {
			e = *(int*) ((char*) 0x7f4ca0 + idx4 * 0x21c + 0x210);
			p = (char*) (0x90e0a0 + idx4);
			for (i = 0; i < 0x300; i++) {
				if (SLOT_DWORD(i * 0x21c) != e) {
					*p = (char) (int) ((float) *p * *(float*) (t + 8));
				}
				p += 0x300;
			}
		} else {
			idx4 = 0;
			for (i = 0; i < 0x65400; i += 0x21c) {
				if (SLOT_DWORD(i) == r1) {
					break;
				}
				idx4++;
			}
			if (i >= 0x65400) {
				return 1;
			}
			if (idx4 >= 0x300) {
				return 1;
			}
			if (SLOT_WORD(idx4 * 0x21c) == 0xffff) {
				return 1;
			}
			p = (char*) (0x869480 + idx4 * 0x300);
			if (kind == 2) {
				*(unsigned char*) ((char*) 0x90e0a0 + idx4 * 0x300) = 0;
				v = *(signed char*) p + t[6];
				if (v <= -0x7f) {
					v = -0x7f;
				} else if (v >= 0x7f) {
					v = 0x7f;
				}
				*p = (signed char) v;
			} else if (kind == 1) {
				v = *(signed char*) p + t[6];
				if (v <= -0x7f) {
					v = -0x7f;
				} else if (v >= 0x7f) {
					v = 0x7f;
				}
				*p = (signed char) v;
				if (t[6] >= 0) {
					v = v / 2;
				}
				v += *(signed char*) ((char*) 0x90e0a0 + idx4 * 0x300);
				if (v <= -0x7f) {
					*(unsigned char*) ((char*) 0x90e0a0 + idx4 * 0x300) = 0x81;
				} else if (v >= 0x7f) {
					*(unsigned char*) ((char*) 0x90e0a0 + idx4 * 0x300) = 0x7f;
				} else {
					*(signed char*) ((char*) 0x90e0a0 + idx4 * 0x300) = (signed char) v;
				}
			} else if (kind == 0) {
				v = *(signed char*) p + t[6];
				if (v <= -0x7f) {
					v = -0x7f;
				} else if (v >= 0x7f) {
					v = 0x7f;
				}
				*p = (signed char) v;
			}
		}
	}
	if (changed != 0) {
		*changed = 1;
	}
	return 0;
}
