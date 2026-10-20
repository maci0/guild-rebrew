typedef struct G175_REC {
	int id;
	char pad[0x20];
	unsigned char v[5];
	char tail[0x1b];
} G175_REC;

/* ADDRESS: GOLDTL 0x004f14c0 */
int __cdecl fcn_004f14c0(G175_REC* a, int na, G175_REC* b, int nb)
{
	G175_REC* best_a;
	G175_REC* best_b;
	int sum_a;
	int sum_b;
	int sum;
	int i;
	int j;

	best_a = 0;
	best_b = 0;
	sum_a = 0;
	sum_b = 0;
	for (i = na; i > 0; i--, a++) {
		if (a->id == -1) {
			continue;
		}
		if (best_a == 0) {
			best_a = a;
			for (j = 0; j < 5; j++) {
				sum_a += a->v[j];
			}
		}
		else {
			sum = 0;
			for (j = 0; j < 5; j++) {
				sum += a->v[j];
			}
			if (sum > sum_a) {
				best_a = a;
				sum_a = sum;
			}
		}
	}
	for (i = nb; i > 0; i--, b++) {
		if (b->id == -1) {
			continue;
		}
		if (best_b == 0) {
			best_b = b;
			for (j = 0; j < 5; j++) {
				sum_b += b->v[j];
			}
		}
		else {
			sum = 0;
			for (j = 0; j < 5; j++) {
				sum += b->v[j];
			}
			if (sum > sum_b) {
				best_b = b;
				sum_b = sum;
			}
		}
	}
	if (best_a == 0) {
		if (best_b != 0) {
			return 1;
		}
		return -2;
	}
	if (best_b == 0) {
		return -1;
	}
	if (sum_b > sum_a) {
		return 1;
	}
	return (sum_b >= sum_a) - 1;
}
