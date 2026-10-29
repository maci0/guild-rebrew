void __cdecl fcn_00469c40(int, int, int);

/* ADDRESS: GOLDTL 0x00471c80 */
void __cdecl fcn_00471c80(int idx, unsigned char flags, float limit)
{
	int* p;
	float value;
	float bound;
	int t;

	p = (int*) (0x1015f40 + idx * 0x3cc);
	if (flags & 1) {
		value = (float) (p[1] + p[3] / 2)
			- (float) *(int*) 0x1015eac / *(float*) 0x67d368
			+ (float) *(int*) 0x1015eac - (float) (p[3] / 2);
	} else {
		value = (float) p[1];
	}
	if (flags & 2) {
		bound = (float) (p[2] + p[4] / 2) * *(float*) 0x67d368 - (float) (p[4] / 2);
	} else {
		bound = (float) p[2];
	}
	t = *(int*) 0x1040494 - p[3];
	if ((float) t < value) {
		value = (float) t;
	}
	t = *(int*) 0x1040490 - p[4];
	if ((float) t < bound) {
		bound = (float) t;
	}
	fcn_00469c40((int) value, (int) bound, *(int*) ((char*) p + 0x27c));
}
