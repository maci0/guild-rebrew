int __cdecl fcn_00507d10(int job);
unsigned short __cdecl gm_RandomMod(int n);
int __cdecl fcn_004a4410(float* o1, float* o2, int a3, char* e, int a5, int a6, int a7);
int __cdecl fcn_004a4550(float* o1, float* o2, int a3, char* e, int a5, int a6, int a7);

/* ADDRESS: GOLD 0x0049f4f0 */
/* ADDRESS: GOLDTL 0x0049ef30 */
int __cdecl fcn_0049ef30(float* o1, float* o2, int a3, char* e, int skip, int a6, int a7)
{
	int n;

	*o1 = -100.0f;
	*o2 = -100.0f;
	if (skip) {
		*o1 = -1.0e30f;
		*o2 = -1.0e30f;
	} else if (e[2] == 5 && !e[0x169]) {
		n = fcn_00507d10(*(unsigned char*) (e + 0x164));
		if (n >= 3) {
			if (n < 6) {
				if (gm_RandomMod(n - 1)) {
					return fcn_004a4410(o1, o2, a3, e, 0, a6, a7);
				}
			} else {
				fcn_004a4550(o1, o2, a3, e, 0, a6, a7);
				*o1 = *o1 + *o1;
				*o2 = *o2 * 3.0f;
				return 1;
			}
		}
	}
	return 0;
}
