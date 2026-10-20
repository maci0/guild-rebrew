int __cdecl gm_RandomMod(unsigned short n);
int __cdecl fcn_005cf720(unsigned short a, unsigned short b, void* c, int d);
float __cdecl fcn_0050f980(int a, int b, int c);
int __cdecl fcn_004e99c0(int k);

/* ADDRESS: GOLDTL 0x004a5c40 */
unsigned int __cdecl fcn_004a5c40(unsigned short* a0, unsigned int a1, unsigned int a2, float lo, float hi, int range, unsigned short* out)
{
	int arr[0x14];
	unsigned short slots[0x10];
	int base;
	int flag;
	int have;
	unsigned int count;
	unsigned int cand;
	unsigned int tries;
	unsigned int v9;
	unsigned int step;
	int i;

	arr[1] = a2;
	arr[5] = 2;
	flag = 0;
	have = 0;
	count = 0;
	base = 0;
	if (*(int*) 0x77261c != 0) {
		count = 0;
		if (fcn_005cf720(*a0, *(unsigned short*) *(int*) 0x77261c, arr, 0) != 0) {
			have = 1;
			*out = *(unsigned short*) *(int*) 0x77261c;
		}
	}
	if ((*(double*) 0x662950 < lo || hi < *(double*) 0x662c38) && lo < hi) {
		flag = 1;
	}
	base = fcn_004e99c0(*(char*) ((char*) a0 + 0x166));
	if (have < a2) {
		do {
			arr[1] = a2;
			if (have != 0) {
				slots[have] = out[have - 1];
			} else {
				slots[0] = *a0;
			}
			tries = 0x300;
			step = 0;
			v9 = (unsigned int) gm_RandomMod(0x300);
			cand = v9;
			do {
				float d;
				int diff;

				if (tries == 0) {
					if (step == 0) {
						return have;
					}
					break;
				}
				if (fcn_005cf720(*a0, (unsigned short) cand, arr, 0) != 0) {
					if (!flag || ((d = fcn_0050f980(cand, *a0, 1)) >= lo && d <= hi)) {
						diff = base - fcn_004e99c0(*(char*) (cand * 0x21c + 0x7f4e06));
						if (diff < 0) {
							diff = -diff;
						}
						if (diff <= range) {
							step = 1;
							out[have] = (unsigned short) cand;
						}
					}
				}
				tries--;
				cand = (cand + count) % 0x300;
			} while (step == 0);
			have++;
		} while (have < a1);
	}
	return have;
}
