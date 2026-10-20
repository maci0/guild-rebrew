typedef struct {
	short lo;
	short hi;
	int x4;
	int x8;
	int xc;
	int x10;
	int c;
	int d;
} TierInfo;
// SIZE 0x1c

int __cdecl fcn_004e9580(int, TierInfo*);
int __cdecl gm_RandomMod(unsigned short);
int __cdecl fcn_00507400(int, int);
int __cdecl fcn_004c4fc0(char, int, int, short, int, char, char, char);

/* ADDRESS: GOLDTL 0x004e9730 */
unsigned int __cdecl fcn_004e9730(unsigned int a0)
{
	TierInfo t;
	int v;
	int c0;
	int d0;

	if (fcn_004e9580((int) a0, &t) == 0) {
		return 0xffffffff;
	}
	if (*(int*) 0x68de28 == 2) {
		*(int*) 0x68de28 = gm_RandomMod(2) & 0xffff;
	}
	d0 = t.d;
	c0 = t.c;
	v = fcn_00507400((gm_RandomMod(0xc) & 0xffff) + 1,
	    c0 + (gm_RandomMod(d0 - c0 + 1) & 0xffff));
	d0 = t.hi;
	c0 = t.lo;
	v = fcn_004c4fc0(0x13, -1, -1, (short) (c0 + (gm_RandomMod(d0 - c0 + 1) & 0xffff)),
	    -1, (char) v, 0, (char) *(int*) 0x68de28);
	*(int*) 0x68de28 = 1 - *(int*) 0x68de28;
	return v;
}
