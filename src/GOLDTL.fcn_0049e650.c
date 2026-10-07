// FUNCTION: GOLD 0x0049ec10
// FUNCTION: GOLDTL 0x49e650

typedef struct Blk24 {
	int v[6];
} Blk24;
// SIZE 0x18

extern unsigned short g_7f4c04;

int __cdecl gm_CheckStatLevel(int, int);
int __cdecl fcn_00507d10(int job);
int __cdecl fcn_004ab010(unsigned short* e, Blk24* o1, Blk24* o2);
int __cdecl fcn_004a4410(float* o1, float* o2, int a3, unsigned short* e, int a5, Blk24* a6, Blk24* a7);
int __cdecl fcn_004a4550(float* o1, float* o2, int a3, unsigned short* e, int a5, Blk24* a6, Blk24* a7);

int __cdecl fcn_0049e650(float* o1, float* o2, int a3, unsigned short* e, int skip, Blk24* a6, Blk24* a7)
{
	Blk24 b1;
	Blk24 b2;
	int r;

	*o1 = -1.0e30f;
	*o2 = -1.0e30f;
	if (skip) {
		return 0;
	}
	r = gm_CheckStatLevel(*e, 4);
	if (r != 0 && fcn_00507d10(r) > 2) {
		if (fcn_004ab010(e, &b1, &b2) != 0) {
			fcn_004a4550(o1, o2, a3, e, 0, a6, a7);
			*a6 = b1;
			*a7 = b2;
			*o1 = *o1 * 6.0f;
			*o2 = *o2 + *o2;
			return 1;
		}
		return 0;
	}
	if (g_7f4c04 < 0x14) {
		return 0;
	}
	return fcn_004a4410(o1, o2, a3, e, 0, a6, a7);
}
