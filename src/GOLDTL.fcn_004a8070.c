/* Pattern match of the 32-bit value against the static group tables.
 * The first table holds 6 groups of 4 slots at stride 0x10; the second view
 * holds 4 rows of 6 slots at stride 0x40. Results report group indices. */
/* ADDRESS: GOLDTL 0x004a8070 */
char __cdecl fcn_004a8070(int value, int* out1, int* out2, int* out3, int* out4)
{
	int best;
	int second;
	int max1;
	int max2;
	int counts1[6];
	int counts2[4];
	int groups1;
	int groups2;
	int best2;
	int next;
	int mode;
	int first;
	int i;
	int n;
	int* p;

	best = -1;
	next = 0;
	groups2 = 0;
	groups1 = 0;
	max1 = 0;
	max2 = 0;
	best2 = 0;
	second = -1;
	mode = 0;
	p = (int*) 0x1007ce8;
	for (first = 0; (int) p < 0x1007e68; first++) {
		n = 0;
		for (i = 0; i < 4; i++) {
			if (p[i * 4] == value) {
				n++;
			}
		}
		p += 0x10;
		counts1[first] = n;
		if (n >= 2) {
			groups2++;
			if (n <= max1) {
				if (best < 0) {
					best = first;
				}
			} else {
				best = next;
				max1 = n;
				next = first;
			}
		}
	}
	second = best;
	best = 0;
	p = (int*) 0x1007ce8;
	for (first = 0; (int) p < 0x1007d28; first++) {
		n = 0;
		for (i = 0; i < 6; i++) {
			if (p[i * 0x10] == value) {
				n++;
			}
		}
		p += 4;
		counts2[first] = n;
		if (n >= 2) {
			groups1++;
		}
		if (n > max2) {
			max2 = n;
			best2 = first;
		}
	}
	if (groups1 != 1 || max2 != 5) {
		mode = 0;
	} else {
		mode = 6;
		*out3 = best2;
	}
	if (groups2 == 0) {
		if (counts1[0] != 0 && counts1[5] != 0) {
			if (mode != 6) {
				return 0;
			}
			return 6;
		}
		return (mode == 6) * 4 + 4;
	}
	if (groups2 != 1) {
		if (groups2 != 2) {
			return 0;
		}
		if (max1 != 3) {
			if (max1 != 2) {
				return 0;
			}
			*out1 = next;
			*out2 = second;
			p = (int*) (second * 0x40 + 0x1007d18);
			{
				int* q;
				q = (int*) (next * 0x40 + 0x1007d18);
				for (i = 3; i >= 0; i--) {
					if (*q == value) {
						*out3 = i;
					}
					if (*p == value) {
						*out4 = i;
					}
					q -= 4;
					p -= 4;
				}
			}
			return 2;
		}
		*out1 = next;
		*out2 = second;
		return 5;
	}
	if (max1 == 4) {
		*out1 = next;
		return 7;
	}
	if (max1 != 3) {
		if (max1 != 2) {
			return 0;
		}
		*out1 = next;
		i = 3;
		p = (int*) (next * 0x40 + 0x1007d18);
		do {
			if (*p == value) {
				*out3 = i;
				return 1;
			}
			i--;
			p -= 4;
		} while (i >= 0);
		return 1;
	}
	*out1 = next;
	return 3;
}
