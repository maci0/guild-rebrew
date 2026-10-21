typedef struct EvRec EvRec;
struct EvRec {
	unsigned char f00;
	char pad0[3];
	int id;
	unsigned char kind;
	char pad1[15];
};

int __cdecl fcn_004e8b40(unsigned char, int*);
int __cdecl fcn_004e8b80(int, int, EvRec*);
unsigned char* __cdecl fcn_00508e40(int);
int __cdecl gm_RandomMod(int);
int __cdecl fcn_004e8240(unsigned char, unsigned char*, unsigned char*, int, int);
void __cdecl fcn_004c54c0(int, int, int, int);
void __cdecl fcn_00545d40(int, int, void*, int, int, void*);
void __cdecl fcn_0051af00(void*, int, ...);
void __cdecl fcn_00500bb0(void*, int, int, int);
void __cdecl fcn_00546190(void*);

/* ADDRESS: GOLDTL 0x0055a0b0 */
void __cdecl fcn_0055a0b0(char* a0)
{
	int cnt;
	int b;
	int idx;
	int n;
	int tmp[6];
	EvRec arr[6];
	char buf[0x800];
	unsigned char* p;
	unsigned char* r;
	unsigned char* v3;

	idx = *(int*) (a0 + 0x70);
	if (idx == 0xc) {
		if (*(int*) (a0 + 0xac) == 0) {
			fcn_0051af00(buf, 0x10bc, (unsigned char*) 0x868080 + *(unsigned char*) 0x773d75 * 0x2f4);
		} else {
			fcn_0051af00(buf, 0x10be, (unsigned char*) 0x868080 + *(unsigned char*) 0x773d75 * 0x2f4);
		}
		p = (unsigned char*) 0x7f4ca2;
		do {
			if (*p == 6 || *p == 7) {
				fcn_00545d40(*(unsigned int*) (p + 2), -1, buf, 0x20, 0x600, (void*) 0x6b5c60);
			}
			p += 0x21c;
		} while ((int) p < 0x85a0a2);
		*(int*) (a0 + 0x70) = 0;
		fcn_00500bb0((unsigned char*) a0 + 0x52, 1, 0, 0);
		return;
	} else {
		if (idx >= 0 && idx < 6) {
			cnt = fcn_004e8b80(*(int*) (a0 + 0xb0 + idx * 4), 6, arr);
			if (cnt > 0) {
				r = (unsigned char*) arr;
				do {
					v3 = fcn_00508e40(*(int*) (r + 4));
					if (v3 != 0 && fcn_004e8b40(*(unsigned char*) (r + 8), tmp)) {
						if (*(int*) (a0 + 0xac) == 1
						    && ((unsigned char) *(tmp + 2) == 9 || ((*(2 + tmp)) & 0xFF) == 6)) {
							if ((short) gm_RandomMod(3) != 0) {
								fcn_004e8240(*(unsigned char*) r, 0, 0, 4, 0xff);
							}
						}
						if (*(unsigned char*) (v3 + 2) != 3) {
							n = 0;
							p = (unsigned char*) 0x7f4ca4;
							do {
								if (*(unsigned int*) (p + 0x168) != 0
								    && *(unsigned int*) p != *(unsigned int*) (v3 + 4)
								    && *(unsigned short*) (*(unsigned int*) (p + 0x168) + 0x27) == *(unsigned short*) v3) {
									++n;
									b = (tmp[2] & 0xff) * 3;
									fcn_004c54c0(*(int*) (v3 + 4), *(int*) p,
									             -((unsigned short) gm_RandomMod(b) + (tmp[2] & 0xff) * 3), 1);
								}
								p += 0x21c;
							} while ((int) p < 0x85a0a4);
							if (n != 0) {
								if ((*(unsigned char*) (v3 + 2) == 6 || *(unsigned char*) (v3 + 2) == 7)) {
									if (!(*(int*) (a0 + 0xac) != 0)) {
										fcn_0051af00(buf, 0x10bd, *(unsigned short*) v3);
										fcn_00545d40(*(int*) (v3 + 4), -1, buf, 1, 0x5fd, (void*) 0x6b5c60);
									} else {
										fcn_0051af00(buf, 0x10bf, *(unsigned short*) v3);
										fcn_00545d40(*(int*) (v3 + 4), -1, (buf), 1, 0x5fd, (void*) 0x6b5c60);
									}
								}
							}
						}
					}
					r = r + 0x18;
				} while (--cnt);
			}
			(*(int*) (a0 + 0x70))++;
			fcn_00500bb0((unsigned char*) a0 + 0x52, 1, 0, 0);
			return;
		}
		fcn_00546190((unsigned char*) a0);
	}
}
