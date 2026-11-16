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
	int j;
	int i;

	best_a = 0;
	sum_a = 0;
	for (i = 0; i < na; i++) {
		if (a[i].id == -1) {
			continue;
		}
		if (best_a == 0) {
			best_a = a + i;
			for (j = 0; j < 5; j++) {
				sum_a += a[i].v[j];
			}
		}
		else {
			sum = 0;
			for (j = 0; j < 5; j++) {
				sum += a[i].v[j];
			}
			if (sum > sum_a) {
				best_a = a + i;
				sum_a = sum;
			}
		}
	}
	best_b = 0;
	sum_b = 0;
	for (i = 0; i < nb; i++) {
		if (b[i].id == -1) {
			continue;
		}
		if (best_b == 0) {
			best_b = b + i;
			for (j = 0; j < 5; j++) {
				sum_b += b[i].v[j];
			}
		}
		else {
			sum = 0;
			for (j = 0; j < 5; j++) {
				sum += b[i].v[j];
			}
			if (sum > sum_b) {
				best_b = b + i;
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
