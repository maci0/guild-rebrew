extern char* g_868050;
extern char* g_90e094;
extern char g_773d75;
extern int g_666028;
extern int g_66602c;
extern float g_664178;
extern float g_664158;
extern float g_6628bc;

char* __cdecl fcn_005463a0(int, ...);
char* __cdecl fcn_005462a0(void);
char* __cdecl fcn_00503fe0(int, ...);
char* __cdecl fcn_00503e80(void);
int __cdecl fcn_004fa5b0(int, int, int);
int __cdecl fcn_0049e900(int, char*, int, char*, int);
int __cdecl fcn_0050cf50(char*, int);
int __cdecl fcn_0050d320(char*, char);
int __cdecl fcn_00505e20(int, int, int, char*, int);

/* ADDRESS: GOLDTL 0x00497990 */
int __cdecl fcn_00497990(int a1, char* a2, int a3, char* a4, int a5)
{
	unsigned char* e;
	unsigned char* t;
	unsigned char* p;
	int i;
	int n;
	int b;
	int bits_lo;
	int bits_hi;
	int q[4];
	int A;
	int B;
	int r;
	int id;
	char buf[0x220];

	if (*(char*) (a2 + 2) == 3) {
		return 0;
	}
	for (i = 0; i < 0x88; i++) {
		((int*) buf)[i] = 0;
	}
	*(int*) buf = 1;
	if (a3 == 0) {
		if (*(char*) a4 != 0) {
			return 0;
		}
	} else if (a3 == 1) {
		b = *(char*) a4;
		if (b != 5 && b != 4) {
			return 0;
		}
	}
	if (fcn_005463a0(2, 0, 0xd, 2, *(unsigned short*) a2) != 0) {
		return 0;
	}
	e = (unsigned char*) g_90e094;
	for (i = 0; i < 0x100; i++) {
		if (*e != 0) {
			b = *(unsigned char*) (g_868050 + (unsigned int) *e * 0x24d);
			bits_lo = 0;
			bits_hi = 0;
			if (b > 0x1f) {
				bits_hi = 1 << ((b - 0x20) & 0x1f);
			} else {
				bits_lo = 1 << (b & 0x1f);
			}
			if (*(unsigned short*) (e + 0x27) == *(unsigned short*) a2) {
				if ((g_666028 & bits_lo) != 0 || (g_66602c & bits_hi) != 0) {
					goto found;
				}
			}
		}
		e += 0xa9;
	}
	return 0;
found:
	A = (int) (fcn_0050d320(a2, g_773d75) * g_664178);
	r = fcn_004fa5b0(1, (int) a2, (int) buf);
	q[0] = (r == 2 || r == 4);
	r = fcn_004fa5b0(5, (int) a2, (int) buf);
	q[1] = (r == 2 || r == 4);
	r = fcn_004fa5b0(9, (int) a2, (int) buf);
	q[2] = (r == 2 || r == 4);
	r = fcn_004fa5b0(0xc, (int) a2, (int) buf);
	q[3] = (r == 2 || r == 4);
	t = (unsigned char*) *(int*) (a2 + 0x170);
	if (t != 0) {
		b = *(unsigned char*) (g_868050 + (unsigned int) *t * 0x24d + 0x247);
		n = b - 1;
		if (n >= 0) {
			/* uncertain: native clears b dwords from &q[0], past q[3] when b > 4 */
			p = (unsigned char*) q;
			for (i = 0; i <= n; i++) {
				((int*) q)[i] = 0;
			}
		}
	}
	if (*(char*) a4 != 0) {
		goto state_path;
	}
	e = (unsigned char*) fcn_00503fe0(1, 6);
	if (*(char*) a4 != 0) {
		return 0x10;
	}
loop_ent:
	if (e == 0) {
		if (*(char*) a4 != 0) {
			return 0x10;
		}
		return 0;
	}
	b = *(unsigned char*) e;
	if (*(unsigned char*) (g_868050 + (unsigned int) b * 0x24d) == 2 && (*(unsigned char*) (e + 0x5a) & 2) != 0) {
		if ((b == 4 && q[0] != 0) || (b == 5 && q[1] != 0) || (b == 6 && q[2] != 0) || (b == 7 && q[3] != 0)) {
			t = (unsigned char*) fcn_005463a0(1, 0, 0x1b);
			if (t != 0) {
				while (*(int*) (t + 0xac) != *(int*) (e + 1)) {
					t = (unsigned char*) fcn_005462a0();
					if (t == 0) {
						goto next_ent;
					}
				}
				B = *(int*) (t + 0xb0);
				if (A < B) {
					goto fraction;
				}
				*(char*) a4 = 4;
				*(int*) (a4 + 4) = *(int*) (e + 1);
				*(int*) (a4 + 8) = 1;
			}
		}
	}
next_ent:
	e = (unsigned char*) fcn_00503e80();
	if (*(char*) a4 != 0) {
		return 0x10;
	}
	goto loop_ent;
state_path:
	if (*(unsigned char*) a4 != 5) {
		return 0;
	}
	id = *(int*) (a4 + 4);
	if (id == 4 && q[0] == 0) {
		return 0;
	}
	if (id == 5 && q[1] == 0) {
		return 0;
	}
	if (id == 6 && q[2] == 0) {
		return 0;
	}
	if (id == 7 && q[3] == 0) {
		return 0;
	}
	e = (unsigned char*) fcn_00503fe0(1, 6);
	if (*(unsigned char*) a4 != 5) {
		return 0x10;
	}
loop_ent2:
	if (e == 0) {
		if (*(unsigned char*) a4 == 5) {
			return 0;
		}
		return 0x10;
	}
	b = *(unsigned char*) (g_868050 + (unsigned int) *e * 0x24d);
	if (b == id) {
		t = (unsigned char*) fcn_005463a0(1, 0, 0x1b);
		if (t != 0) {
			while (*(int*) (t + 0xac) != *(int*) (e + 1)) {
				t = (unsigned char*) fcn_005462a0();
				if (t == 0) {
					goto next_ent2;
				}
			}
			B = *(int*) (t + 0xb0);
			if (A < B) {
				goto fraction;
			}
			*(char*) a4 = 4;
			*(int*) (a4 + 4) = *(int*) (e + 1);
			*(int*) (a4 + 8) = 1;
		}
	}
next_ent2:
	e = (unsigned char*) fcn_00503e80();
	if (*(unsigned char*) a4 == 5) {
		goto loop_ent2;
	}
	return 0x10;
fraction:
	r = fcn_0050cf50((char*) e, (int) *(signed char*) (e + 0x5c));
	if (!((double) (B - r) / (double) r * g_664158 + g_6628bc > (double) (B - A) / (double) B)) {
		return 0;
	}
	*(int*) (a4 + 8) = B - A;
	*(char*) a4 = 0x12;
	return fcn_0049e900(0x10, a2, a3, a4, a5);
}

/* ADDRESS: GOLDTL 0x00497e60 */
int __cdecl fcn_00497e60(int a1, char* a2)
{
	unsigned char* t;
	int id;

	if (*(unsigned char*) a2 != 4) {
		return 0;
	}
	id = *(int*) (a2 + 4);
	t = (unsigned char*) fcn_005463a0(1, 0, 0x1b);
	if (t != 0) {
		while (*(int*) (t + 0xac) != id) {
			t = (unsigned char*) fcn_005462a0();
			if (t == 0) {
				return 0;
			}
		}
		return fcn_00505e20(*(int*) (a2 + 4), *(int*) (a1 + 4), *(int*) (t + 0xb0), (char*) t, 1);
	}
	return 0;
}
