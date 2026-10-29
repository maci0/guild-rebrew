int __cdecl fcn_0047b620(int, int);

extern char* g_1015ea0;

typedef struct
{
	char pad_00[0xc];
	int f0c;
	int f10;
	int f14;
	char pad_18[0x74];
	int f8c;
	int f90;
	int f94;
	char pad_98[4];
	int f9c;
	char pad_a0[0x254];
} fcn_00467870_Def;
// SIZE 0x2f4

/* ADDRESS: GOLDTL 0x00467870 */
int __cdecl fcn_00467870(int idx, int* out1, int* out2)
{
	int e;
	char* lo;
	char* hi;
	int d;
	int q;
	int v;
	int r;

	e = ((fcn_00467870_Def*) g_1015ea0)[idx].f0c;
	lo = (char*) fcn_0047b620(e, 0);
	fcn_0047b620(e, 1);
	hi = (char*) fcn_0047b620(e, 3);
	d = ((fcn_00467870_Def*) g_1015ea0)[idx].f94 - ((fcn_00467870_Def*) g_1015ea0)[idx].f90;
	q = ((fcn_00467870_Def*) g_1015ea0)[idx].f8c - ((fcn_00467870_Def*) g_1015ea0)[idx].f90;
	v = (int) ((float) ((fcn_00467870_Def*) g_1015ea0)[idx].f9c / d * q);
	r = v - (((unsigned short) *(short*) (hi + 2)) >> 1)
	    + (unsigned short) *(short*) (lo + 2)
	    + ((fcn_00467870_Def*) g_1015ea0)[idx].f10;
	*out1 = r;
	*out2 = ((fcn_00467870_Def*) g_1015ea0)[idx].f14;
	return 1;
}
