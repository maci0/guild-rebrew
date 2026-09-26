char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl fcn_005462a0(void);

#define MINV(a, b) ((a) < (b) ? (a) : (b))
#define MAXV(a, b) ((a) > (b) ? (a) : (b))

// FUNCTION: GOLDTL 0x004ecf00
// SIZE: 652

/* Finds the first linked object of kind 4, 149, 150 or 151 and reports its
 * progress fraction (clamped to [0, 1]) and, for some kinds, its owner. */
int __cdecl fcn_004ecf00(char* e, int* owner, float* frac, int want_idle)
{
	char* p;

	for (p = fcn_005463a0(1, 3, *(int*) (e + 1)); p != 0; p = fcn_005462a0()) {
		switch (*(unsigned char*) p) {
		case 4:
			*frac = ((float) *(int*) (p + 0xb8) - *(int*) (p + 0xb4)) / *(int*) (p + 0xb8);
			*frac = MAXV(MINV(1.0f, *frac), 0.0f);
			return 1;
		case 149:
			*frac = ((float) *(int*) (p + 0xbc) - *(int*) (p + 0xb8)) / *(int*) (p + 0xbc);
			*frac = MAXV(MINV(1.0f, *frac), 0.0f);
			*owner = *(int*) (p + 0xb0);
			return 2;
		case 150:
			*frac = ((float) *(int*) (p + 0xbc) - *(int*) (p + 0xb8)) / *(int*) (p + 0xbc);
			*frac = MAXV(MINV(1.0f, *frac), 0.0f);
			*owner = *(int*) (p + 0xb0);
			return 3;
		case 151:
			if (want_idle == 0) {
				return 0;
			}
			*frac = 0.0f;
			*owner = 0;
			return 4;
		}
	}
	return 0;
}
