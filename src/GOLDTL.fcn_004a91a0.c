unsigned short __cdecl fcn_0042e410(int n);
int __cdecl fcn_004f6040(int* ids, int* d, unsigned short id);
char* __cdecl fcn_00508e40(int id);

// FUNCTION: GOLD 0x004a9080
// SIZE: 208
// FUNCTION: GOLDTL 0x4a91a0
// SIZE: 208
int __cdecl fcn_004a91a0(int a1, char* e, int a3, int a4, char* out)
{
	int d[32];
	int ids[32];
	int k;
	int i;
	int n;
	int thr;
	char* p;

	thr = fcn_0042e410(4) + 2;
	if (e[0x166] == 0xd) {
		return 0;
	}
	n = fcn_004f6040(ids, d, *(unsigned short*) e);
	if (!n) {
		return 0;
	}
	i = 0;
	k = n;
	do {
		if (d[i] >= thr) {
			p = fcn_00508e40(ids[i]);
			if (p && p[2] != 0xf && p[8] && p[0x166] != 0xd && p[0x166] != 0x1b && p[0x166] != 0xf && p[0x166] != 0x15) {
				out[0] = 7;
				*(int*) (out + 4) = *(int*) (p + 4);
				return 1;
			}
		}
		k--;
		i = (i + 1) % n;
	} while (k);
	return 0;
}
