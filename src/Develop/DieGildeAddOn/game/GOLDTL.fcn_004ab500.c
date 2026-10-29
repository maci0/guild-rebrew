/* Select a placement candidate for an entity and fill the caller's packet
 * with the chosen node's keys. */

int __cdecl gm_CheckStatLevel(int, int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_00510400(char*);
int __cdecl gm_RandomMod(unsigned short);
int __cdecl fcn_004a5340(int*, int, int*, int, float, unsigned short*);
int __cdecl fcn_004a5c40(int*, int, int, float, float, int, unsigned short*);
int __cdecl fcn_004e99c0(unsigned char);

/* ADDRESS: GOLDTL 0x004ab500 */
unsigned int __cdecl fcn_004ab500(unsigned int a0, unsigned short* a1, int a2,
                                  char* a3, int a4)
{
	unsigned int v8;
	unsigned short v9[4];
	int v10[4];
	unsigned short* v12;
	unsigned char* v11;
	int v5;
	int v6;
	int v7;
	int v1;

	v5 = gm_CheckStatLevel((int) *a1, 0xe);
	v9[0] = 0xffff;
	v9[1] = 0xffff;
	v9[2] = 0xffff;
	v9[3] = 0xffff;
	v12 = 0;
	v6 = 0;
	v10[0] = 0;
	v10[1] = 0;
	v10[2] = 0;
	v10[3] = 0;
	if ((*(unsigned char*) ((char*) a1 + 0x1cc) & 8) == 0 &&
	    *(int*) ((char*) a1 + 0x194) >= 5 && (a0 == 0x44 || a0 == 0) &&
	    a2 == 0 && v5 != 0 && *(char*) ((char*) a1 + 2) != 3) {
		a0 = 0x100;
		v11 = (unsigned char*) *(unsigned int*) 0x90e094;
		do {
			if (*v11 != 0 && *(unsigned short*) (v11 + 0x27) == *a1 &&
			    *(unsigned char*) (*(unsigned int*) 0x868050 +
			                       (unsigned int) *v11 * 0x24c) == 0x1f &&
			    fcn_00502cd0(*(int*) (v11 + 0x5d), 2, 6, 0, 0x27c) != 0) {
				v5 = fcn_00510400((char*) v11);
				if (v12 == 0) {
					v6 = v5;
					v12 = (unsigned short*) v11;
				} else if (v5 > v6) {
					v6 = v5;
					v12 = (unsigned short*) v11;
				}
			}
			v11 += 0xa9;
		} while (--a0);
		if (v12 != 0 && v6 != 0) {
			unsigned int* v4 = (unsigned int*) 0xf00500;

			a2 = (int) gm_RandomMod(0x20) & 0xffff;
			if (fcn_004a5340((int*) a1, 1, (int*) &v4, 0,
			                 (float) a2 + *(float*) 0x662da8,
			                 (unsigned short*) &v8) != 0) {
				v1 = *(unsigned char*) ((a2 & 0xffff) * 0x21c + 0x7f4e06);
				a2 = (a2 & 0xffff) * 0x21c + 0x7f4ca0;
				v7 = fcn_004e99c0((unsigned char) v1) / 3;
				v5 = v7 + 2;
				if (v7 + 4 <= *(int*) ((char*) a1 + 0x194) &&
				    (a0 = fcn_004a5c40((int*) a1, 4, (int) v4, 25.0f,
				                       75.0f, v6, v9)) != 0) {
					v7 = 0;
					v6 = 0;
					if (1 <= a0) {
						do {
							v1 = *(unsigned char*) (
							    (unsigned int) v9[v7] * 0x21c + 0x7f4e06);
							v5 = fcn_004e99c0((unsigned char) v1) / 3 +
							     2 + v5;
							if (*(int*) ((char*) a1 + 0x194) <= v5) {
								v10[v6] = (unsigned int) v9[v7] *
								              0x21c +
								          0x7f4ca0;
								v6 += 1;
							}
							v7 += 1;
						} while (v7 < (int) a0);
						if (v6 != 0) {
							*(unsigned int*) (a3 + 4) =
							    *(unsigned int*) (a2 + 4);
							*(unsigned int*) (a3 + 0xc) =
							    *(unsigned int*) (v10[0] + 4);
							if (2 <= v6)
								*(unsigned int*) (a3 + 8) =
								    *(unsigned int*) (v10[1] + 4);
							if (3 <= v6)
								*(unsigned int*) (a4 + 0xc) =
								    *(unsigned int*) (v10[2] + 4);
							if (4 <= v6)
								*(unsigned int*) (a4 + 8) =
								    *(unsigned int*) (v10[3] + 4);
							*(int*) (a3 + 0x10) = v5;
							*a3 = 7;
							return 0x44;
						}
					}
				}
			}
		}
	}
	return 0;
}
