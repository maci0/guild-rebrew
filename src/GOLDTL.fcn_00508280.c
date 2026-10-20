
typedef struct
{
	int a;
	float b;
	int c;
} S0c;
// SIZE 0xc

unsigned short __cdecl gm_RandomMod(unsigned short n);
int __cdecl fcn_00508220(int, S0c*);
void __cdecl fcn_004c4510(char*, int);
void __cdecl fcn_004c4570(int, int, int, int*);
void __cdecl fcn_004c5360(void);
float __cdecl fcn_004ff210(unsigned short, int);

/* ADDRESS: GOLDTL 0x00508280 */
int __cdecl fcn_00508280(char* p, unsigned int* a1, float* a2)
{
	int flags;
	int avail[8];
	S0c s;
	int v;
	int n;
	int i;
	int mask;
	int r;
	float f;

	flags = *(int*) (p + 0x2c);
	avail[0] = 0;
	avail[1] = 0;
	avail[2] = 0;
	avail[3] = 0;
	avail[4] = 0;
	avail[5] = 0;
	avail[6] = 0;
	avail[7] = 0;
	if ((flags & 0xf0) == 0) {
		avail[0] = 1;
	}
	if ((flags & 0xf00) == 0) {
		avail[1] = 1;
	}
	if ((flags & 0x3000) == 0) {
		avail[2] = 1;
	}
	if ((flags & 0x1c000) == 0) {
		avail[3] = 1;
	}
	if ((flags & 0xe0000) == 0) {
		avail[4] = 1;
	}
	if ((flags & 0x700000) == 0) {
		avail[5] = 1;
	}
	if ((flags & 0x1800000) == 0) {
		avail[6] = 1;
	}
	if ((flags & 0x1e000000) == 0) {
		avail[7] = 1;
	}
	i = gm_RandomMod(8);
	n = 8;
	while (avail[i] != 1) {
		n--;
		i = (i + 1) % 8;
		if (n == 0) {
			return 0;
		}
	}
	if (i == -1) {
		return 0;
	}
	if (i >= 8) {
		return 0;
	}
	flags = *(int*) (p + 0x2c);
	i += 2;
	if (fcn_00508220(i, &s) == 0) {
		return 0;
	}
	r = gm_RandomMod(s.c);
	if (a1 != 0) {
		*a1 = r != 0 ? i : 0;
	}
	if (r == 0) {
		return 0;
	}
	mask = 0;
	if (i == 2) {
		mask = ((r << 4) ^ flags) & 0xf0;
	} else if (i == 3) {
		mask = ((r << 8) ^ flags) & 0xf00;
	} else if (i == 4) {
		mask = ((r << 0xc) ^ flags) & 0x3000;
	} else if (i == 5) {
		mask = ((r << 0xe) ^ flags) & 0x1c000;
	} else if (i == 6) {
		mask = ((r << 0x11) ^ flags) & 0xe0000;
	} else if (i == 7) {
		mask = ((r << 0x14) ^ flags) & 0x700000;
	} else if (i == 8) {
		mask = ((r << 0x17) ^ flags) & 0x1800000;
	} else if (i == 9) {
		mask = ((r << 0x19) ^ flags) & 0x1e000000;
	}
	flags ^= mask;
	v = flags;
	fcn_004c4510(p, *(int*) (p + 4));
	fcn_004c4570(4, 1, 0x2c, &v);
	fcn_004c5360();
	f = fcn_004ff210(*(unsigned short*) p, -(int) (r * s.b));
	if (a2 == 0) {
		return 1;
	}
	*a2 = f;
	return 1;
}
