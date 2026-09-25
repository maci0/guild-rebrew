// FUNCTION: GOLDTL 0x005b1980
// SIZE: 256

typedef struct {
	unsigned int id;
	unsigned char pct;
	char pad[3];
} Share;
// SIZE 0x8

typedef struct {
	char pad0[0xc];
	Share e[7];
} Owner;
// SIZE 0x44

unsigned char* __cdecl fcn_005b1aa0(int);

void __cdecl fcn_005b1980(int a, Owner* o)
{
	unsigned char* p;
	unsigned short* q;
	int n;
	int k;
	int found;
	unsigned int id;
	unsigned int total;
	int cnt;
	int rem;
	int step;
	int j;

	p = fcn_005b1aa0(a);
	if (p == 0) {
		return;
	}
	q = (unsigned short*) (p + 1);
	for (n = 0; n < 10; n++, q++) {
		if (*q != 0) {
			found = 0;
			id = *q;
			for (k = 0; k < 7; k++) {
				if (*q == o->e[k].id) {
					found = 1;
				}
			}
			if (!found) {
				for (k = 0; k < 7; k++) {
					if (o->e[k].id == 0) {
						o->e[k].id = id;
						o->e[k].pct = 0xe;
						break;
					}
				}
			}
		}
	}
	total = 0;
	cnt = 0;
	for (k = 0; k < 7; k++) {
		if (o->e[k].id != 0) {
			cnt++;
			total += o->e[k].pct;
		}
	}
	if (total == 100) {
		return;
	}
	if (total > 100) {
		rem = total - 100;
		step = -1;
	}
	else {
		rem = 100 - total;
		step = 1;
	}
	for (j = 0; rem != 0 && cnt != 0; j = (j + 1) % 7) {
		if (o->e[j].id != 0) {
			if (o->e[j].pct + step > -1 && o->e[j].pct + step < 101) {
				o->e[j].pct += step;
				rem--;
			}
		}
	}
}
