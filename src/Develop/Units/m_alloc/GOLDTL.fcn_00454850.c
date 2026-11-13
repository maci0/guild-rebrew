/* Builds the bounding box of an object and its descendants, then splits the
 * node into four quadrants until either the size limit or the recursion depth
 * limit is reached.  Leaves that survive one level are collapsed. */

char __cdecl fcn_004546e0(char* e, float* lo, float* hi);
char* __cdecl fcn_00454630(char* src, float* lo, float* hi);
void __cdecl fcn_00454560(char** n);

/* ADDRESS: GOLDTL 0x00454850 */
void __cdecl fcn_00454850(unsigned int* a0, unsigned int a1, unsigned int a2, unsigned int a3)
{
	float lo[4];
	float hi[4];
	unsigned int* p;
	unsigned int v;
	unsigned int first;
	unsigned int ok;
	float dx;
	float dz;
	int i;

	ok = 1;
	if (a0[0xc] != 0) {
		*((float*) (a0 + 4)) = 1.0e10f;
		*((float*) (a0 + 5)) = 1.0e10f;
		*((float*) (a0 + 6)) = 1.0e10f;
		*((float*) (a0 + 8)) = -1.0e10f;
		*((float*) (a0 + 9)) = -1.0e10f;
		*((float*) (a0 + 10)) = -1.0e10f;
		if (a2 >= 2) {
			for (p = (unsigned int*) a0[0xf]; p != 0; p = (unsigned int*) p[1]) {
				v = *(unsigned int*) (*p + 0x1ec);
				*((float*) (a0 + 4)) = (*((float*) (a0 + 4)) < *((float*) (v + 0x90)))
					? *((float*) (a0 + 4)) : *((float*) (v + 0x90));
				*((float*) (a0 + 5)) = (*((float*) (a0 + 5)) < *((float*) (v + 0x94)))
					? *((float*) (a0 + 5)) : *((float*) (v + 0x94));
				*((float*) (a0 + 6)) = (*((float*) (a0 + 6)) < *((float*) (v + 0x98)))
					? *((float*) (a0 + 6)) : *((float*) (v + 0x98));
				*((float*) (a0 + 8)) = (*((float*) (a0 + 8)) > *((float*) (v + 0xa0)))
					? *((float*) (a0 + 8)) : *((float*) (v + 0xa0));
				*((float*) (a0 + 9)) = (*((float*) (a0 + 9)) > *((float*) (v + 0xa4)))
					? *((float*) (a0 + 9)) : *((float*) (v + 0xa4));
				*((float*) (a0 + 10)) = (*((float*) (a0 + 10)) > *((float*) (v + 0xa8)))
					? *((float*) (a0 + 10)) : *((float*) (v + 0xa8));
			}
		} else {
			for (p = (unsigned int*) a0[0xf]; p != 0; p = (unsigned int*) p[1]) {
				if (fcn_004546e0((char*) *p, lo, hi)) {
					*((float*) (a0 + 4)) = (*((float*) (a0 + 4)) < lo[0])
						? *((float*) (a0 + 4)) : lo[0];
					*((float*) (a0 + 5)) = (*((float*) (a0 + 5)) < lo[1])
						? *((float*) (a0 + 5)) : lo[1];
					*((float*) (a0 + 6)) = (*((float*) (a0 + 6)) < lo[2])
						? *((float*) (a0 + 6)) : lo[2];
					*((float*) (a0 + 8)) = (*((float*) (a0 + 8)) > hi[0])
						? *((float*) (a0 + 8)) : hi[0];
					*((float*) (a0 + 9)) = (*((float*) (a0 + 9)) > hi[1])
						? *((float*) (a0 + 9)) : hi[1];
					*((float*) (a0 + 10)) = (*((float*) (a0 + 10)) > hi[2])
						? *((float*) (a0 + 10)) : hi[2];
				}
			}
		}
	}
	if (a2 < a3 && a1 < a0[0xc]) {
		dx = (*((float*) (a0 + 8)) - *((float*) (a0 + 4))) * 0.5f;
		dz = (*((float*) (a0 + 10)) - *((float*) (a0 + 6))) * 0.5f;
		lo[0] = *((float*) (a0 + 4));
		lo[2] = *((float*) (a0 + 6));
		hi[0] = dx + *((float*) (a0 + 4));
		hi[2] = dz + *((float*) (a0 + 6));
		a0[0] = (unsigned int) fcn_00454630((char*) a0, lo, hi);
		lo[0] = dx + *((float*) (a0 + 4));
		lo[2] = *((float*) (a0 + 6));
		hi[0] = *((float*) (a0 + 8));
		hi[2] = dz + *((float*) (a0 + 6));
		a0[1] = (unsigned int) fcn_00454630((char*) a0, lo, hi);
		lo[0] = dx + *((float*) (a0 + 4));
		lo[2] = dz + *((float*) (a0 + 6));
		hi[0] = *((float*) (a0 + 8));
		hi[2] = *((float*) (a0 + 10));
		a0[2] = (unsigned int) fcn_00454630((char*) a0, lo, hi);
		lo[0] = *((float*) (a0 + 4));
		lo[2] = dx + *((float*) (a0 + 6));
		hi[0] = dx + *((float*) (a0 + 4));
		hi[2] = *((float*) (a0 + 10));
		a0[3] = (unsigned int) fcn_00454630((char*) a0, lo, hi);
		first = 0xffffffff;
		for (i = 0; i < 4; i++) {
			v = a0[i];
			if (v != 0) {
				if ((int) first >= 0) {
					if (first != *(unsigned int*) (v + 0x30))
						ok = 0;
				} else {
					first = *(unsigned int*) (v + 0x30);
				}
			}
		}
		for (i = 0; i < 4; i++) {
			v = a0[i];
			if (v != 0) {
				if (ok != 0) {
					fcn_00454560((char**) v);
					a0[i] = 0;
				} else {
					fcn_00454850((unsigned int*) v, a1, a2 + 1, a3);
				}
			}
		}
	}
}
