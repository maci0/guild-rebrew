/* Black-board ("schwarzes Brett") dialogue: lists up to four messages and
 * runs the modal click loop until the dialogue closes. */

#include "client_types.h"

typedef struct {
	char pad0[4];
	int f4;
	char pad8[0x68];
	int f70;
	char pad74[0x48];
	int fbc;
	char padc0[1];
	unsigned char fc1;
} Ent5c1110;

int __cdecl fcn_00470820(int, int, char*);
void __cdecl fcn_00471b60(int);
void __cdecl fcn_00473a90(int, int);
void __cdecl d2_SetForm(int, int);
int __cdecl fcn_00519190();
char* __cdecl he_fn_Handlung(void);
int __cdecl fcn_005463a0();
unsigned short* __cdecl fcn_00508e40(int);
int __cdecl fcn_00472250(int, int, int);
void __cdecl fcn_00472170(int, int);
int __cdecl fcn_00525f60(char*, int);
int __cdecl fcn_004c5620(int, char*);
int __cdecl fcn_004c4450(int);
int __cdecl fcn_005373e0(void*, int);
void __cdecl fcn_00471e30(int);
int __cdecl fcn_00532ef0(void);
int __cdecl fcn_005100f0(int, int);

/* ADDRESS: GOLDTL 0x005c1110 */
int __cdecl fcn_005c1110(void)
{
	int n;
	int t;
	unsigned short* p;
	int a[4];
	int b[4];
	Ent5c1110* ent;
	int h;
	int k;
	int i;
	int j;
	int o;
	int r;
	int* q;

	t = *(int*) 0x6b7fac;
	a[0] = -1;
	a[1] = -1;
	a[2] = -1;
	a[3] = -1;
	b[0] = -1;
	b[1] = -1;
	b[2] = -1;
	b[3] = -1;
	h = fcn_00470820(0, 0, (char*) 0x6ac514);
	fcn_00471b60(h);
	fcn_00473a90(0, 0);
	d2_SetForm(h, 0);
	fcn_00519190(0x1912);
	*(int*) 0x100f1dc = -1;
	do {
		if ((unsigned int) t <= (unsigned int) *(int*) 0x6b7fac) {
			n = 1;
			t = *(int*) 0x6b7fac + 0x1f4;
			a[0] = -1;
			b[0] = -1;
			a[1] = -1;
			b[1] = -1;
			a[2] = -1;
			a[3] = -1;
			b[2] = -1;
			b[3] = -1;
			ent = (Ent5c1110*) fcn_005463a0(n, 0, 0x35);
			if (ent != 0) {
				i = 2;
				for (k = 0; ; k += 4) {
					if (k >= 0x10) {
						goto done;
					}
					if (ent->f70 > -1) {
						p = fcn_00508e40(ent->fbc);
						if (p != 0) {
							d2_SetForm(h, i - 1);
							fcn_00519190(0x6811b0);
							fcn_00519190(0x1913, 0x1916 + (int) ent->fc1,
							    (int) *p);
							d2_SetForm(h, i);
							fcn_00519190(0x6811b0);
							*(int*) ((char*) a + k) = fcn_00472250(h, i,
							    fcn_00519190(0x1914, 2));
							*(int*) ((char*) b + k) = ent->f4;
							fcn_00472170(*(int*) ((char*) 0x10161bc
							    + 0x3cc * *(int*) ((char*) 0x1038140
							    + h * 0x2bc + n * 8)), 1);
							n++;
							i += 2;
						}
					}
					ent = (Ent5c1110*) he_fn_Handlung();
					if (ent == 0) {
						break;
					}
				}
			}
			if (n < 5) {
				q = (int*) ((char*) 0x1038140 + h * 0x2bc + n * 8);
				for (j = n * 2 - 1; j < 9; j += 2) {
					d2_SetForm(h, j);
					fcn_00519190(0x6811b0);
					fcn_00472170(*(int*) ((char*) 0x10161bc
					    + 0x3cc * *q), 0);
					q += 2;
				}
			}
done:
			n = -1;
		}
		if (*(int*) 0x14ce8e0 != 0) {
			*(int*) 0x774654 = 1;
		} else if (*(int*) 0x100f1dc != n && *(int*) 0x67d370 != n) {
			for (k = 0; k < 4; k++) {
				if (a[k] == *(int*) 0x67d370) {
					break;
				}
			}
			if (k < 4) {
				o = fcn_005463a0(1, 1, b[k]);
				if (o != 0) {
					if (fcn_00525f60((char*) 0x7f4ca0 + 0x21c
					    * (unsigned int) *(unsigned short*) 0x774970, 2) != 0) {
						*(pos14_7f4c00*) ((char*) o + 0x52) =
						    *(pos14_7f4c00*) 0x7f4c00;
						r = fcn_004c5620(n, (char*) o);
						if (r != n) {
							while (fcn_004c4450(r) == 0) {
								fcn_005373e0(0, 0x677c7);
							}
						}
						if (fcn_004c4450(r) == 1) {
							fcn_005100f0(*(int*) ((char*) 0x7f4ca0
							    + 4 + 0x21c
							    * (unsigned int) *(unsigned short*) 0x774970), -2);
						}
						t = *(int*) 0x6b7fac;
					}
				}
			}
		}
	} while (fcn_005373e0((void*) fcn_005c1110, 0x677c7) != 0);
	fcn_00471e30(h);
	return fcn_00532ef0();
}
