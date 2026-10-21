/* Select three random free building sites around the entity and report
 * their computed offsets. */

extern unsigned char g_773d75;

int __cdecl fcn_0050b7c0(int, int);
int __cdecl gm_WalkEntityChain(int);
int __cdecl fcn_0050d640(int, int, int, char*);
int __cdecl fcn_0050f980(int, int, int);
int __cdecl fcn_004fa5b0(int, unsigned short*, unsigned int*);
void __cdecl fcn_004c5150(int, int, int, int);
int __cdecl gm_RandomMod(int);
int __cdecl _ftol(void);
void __cdecl memset(void*, int, unsigned int);

/* ADDRESS: GOLDTL 0x0050d6d0 */
unsigned int __cdecl fcn_0050d6d0(int a0, unsigned short* a1, unsigned int a2,
                                  int* a3)
{
	char v15[36];
	unsigned int v16[136];
	int v4;
	int v6;
	unsigned int v8;
	int* v9;
	unsigned int v11;
	int* v12;
	int v17;
	int v18;
	int v21;
	unsigned int v20;
	unsigned int v5;
	unsigned short v3;
	char v2;

	v17 = 0;
	v5 = a2;
	if (a1 && a0 && *(short*) (a0 + 0x27) != -1 && a2) {
		v21 = fcn_0050b7c0(*(int*) (a0 + 0x5d), g_773d75);
		if ((char) a1[1] == 6) {
			if (*(int*) 0x7f4c00 <= 5) {
				v6 = (int) *(unsigned short*) (a0 + 0x27);
				v2 = *(char*) ((unsigned int) v6 * 0x21c + 0x7f4ca2);
				if (v2 != 6 && v2 != 7 &&
				    (float) v21 <
				        (float) gm_WalkEntityChain(*a1) * *(float*) 0x6628f0) {
					v21 = _ftol();
					v8 = _ftol();
					fcn_004c5150(*(int*) (a0 + 1), 0xffffffff,
					             g_773d75, v8);
				}
			}
			v12 = (int*) (a0 + 0x71);
			v18 = 3;
			v9 = a3;
			do {
				v4 = *v12;
				if (v4 >= 1) {
					if (v21 <= v4) {
						v17 = -1;
						*v9 = -1;
					} else {
						v9[0] = v12[0];
						v9[1] = v12[1];
						v9[2] = v12[2];
						v17 = -1;
					}
				} else if (v4 == -1) {
					v17 = -1;
					*v9 = -1;
				} else {
					*v9 = -1;
				}
				v12 = (int*) ((char*) v12 + 0xc);
				v9 += 3;
				v18 -= 1;
			} while (v18);
			if (v17 == -1) {
				return 3;
			}
			v5 = a2;
		}
		v3 = *(unsigned short*) (a0 + 0x27);
		if (fcn_0050d640((int) v3, 0, 0xffff, v15) <= 8) {
			memset(a3, 0, v5 * 12);
			gm_WalkEntityChain(*a1);
			memset(v16, 0, 0x220);
			v16[0] = 1;
			if (!(fcn_004fa5b0(0xf, a1, v16) & 2)) {
				fcn_004fa5b0(0xb, a1, v16);
			}
			_ftol();
			v11 = 0;
			if (a2) {
				do {
					gm_RandomMod(0x1e);
					v17 = _ftol();
					if (v11 == 0 || v11 == 1) {
						v17 = _ftol();
					}
					v6 = gm_RandomMod(6);
					v18 = _ftol();
					v2 = *(char*) ((unsigned int) *(unsigned short*) (a0 + 0x27) *
					                   0x21c +
					               0x7f4ca2);
					if (v2 != 6 && v2 != 7 &&
					    ((char) a1[1] == 6 || (char) a1[1] == 7)) {
						fcn_0050f980(*a1, a0, 1);
						v18 = _ftol();
					}
					v20 = v11 + 1;
					v12 = &a3[v11 * 3];
					v12[2] = v18;
					v12[0] = v17;
					v12[1] = v6 + 2;
					v11 = v20;
				} while (v20 < a2);
			}
			if ((char) a1[1] == 6) {
				v17 = 3;
				v12 = (int*) (a0 + 0x71);
				do {

					v17 -= 1;
					v12[0] = a3[0];
					v12[1] = a3[1];
					v12[2] = a3[2];
					a3 += 3;
					v12 = (int*) ((char*) v12 + 0xc);
				} while (v17);
			}
			return 3;
		}
	}
	return 0;
}
