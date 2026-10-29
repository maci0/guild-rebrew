unsigned short __cdecl gm_RandomMod(unsigned short n);
int __cdecl fcn_004f6040(int* ids, int* d, unsigned short id);
char* __cdecl fcn_00508e40(int id);
int __cdecl fcn_0055c0a0(char* a, char* b);
double __cdecl fcn_0050f980(int a, int b, int c);

/* ADDRESS: GOLDTL 0x004aa7c0 */
int __cdecl fcn_004aa7c0(char* e, char* res, char* out)
{
	int d[32];
	int ids[32];
	int vb[2]; /* holds the double result of fcn_0050f980; an aligned double local forces an EBP frame */
	int k;
	int i;
	int n;
	int r;
	char* p;

	if (*(int*) (e + 0x194) < 2) {
		return 0;
	}
	n = fcn_004f6040(ids, d, *(unsigned short*) e);
	if (!n) {
		return 0;
	}
	i = gm_RandomMod(n);
	k = n;
	do {
		p = fcn_00508e40(ids[i]);
		if (!p) {
			return 0;
		}
		if (!fcn_0055c0a0(e, p)) {
			return 0;
		}
		*(double*) vb = fcn_0050f980(*(unsigned short*) e, *(unsigned short*) p, 1);
		r = gm_RandomMod(0x3d) & 0xffff;
		if ((double) r + 20.0 > *(double*) vb) {
			r = gm_RandomMod(4) & 0xffff;
			if (d[i] < r + 2) {
				out[0] = 7;
				*(int*) (out + 4) = *(int*) (p + 4);
				*(int*) (out + 0x10) = *(unsigned short*) p;
				*(int*) (res + 8) = (gm_RandomMod(*(unsigned short*) &d[i]) & 0xffff) + 1;
				*(int*) (res + 0x10) = gm_RandomMod(3) & 0xffff;
				return 1;
			}
		}
		k--;
		i = (i + 1) % n;
	} while (k);
	return 0;
}
