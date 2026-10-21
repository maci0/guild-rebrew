typedef struct {
	short lo;
	short hi;
	int min_cost;
	int max_cost;
	int a;
	int b;
	int c;
	int d;
} TierInfo;

int __cdecl fcn_004e9580(int, TierInfo*);
int __cdecl gm_RandomMod(unsigned short);
int __cdecl fcn_00507400(int, int);
int __cdecl fcn_004c4fc0(char, int, int, short, int, char, char, char);

/* ADDRESS: GOLDTL 0x004e9730 */
unsigned int __cdecl fcn_004e9730(unsigned int a0)
{
	TierInfo t;
	int v;
	int r;
	short s;

	if (fcn_004e9580((int) a0, &t) == 0) {
		return 0xffffffff;
	}
	if (*(int*) 0x68de28 == 2) {
		*(int*) 0x68de28 = gm_RandomMod(2) & 0xffff;
	}
	r = (gm_RandomMod(t.d - t.c + 1) & 0xffff) + t.c;
	v = fcn_00507400((gm_RandomMod(0xc) & 0xffff) + 1, r);
	s = (short) ((gm_RandomMod(t.hi - t.lo + 1) & 0xffff) + t.lo);
	v = fcn_004c4fc0(0x13, -1, -1, s, -1, (char) v, 0, *(char*) 0x68de28);
	*(int*) 0x68de28 = 1 - *(int*) 0x68de28;
	return v;
}
