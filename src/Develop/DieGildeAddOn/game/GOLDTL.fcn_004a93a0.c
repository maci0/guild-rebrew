unsigned short __cdecl gm_RandomMod(int n);
int __cdecl fcn_004f6040(int* ids, int* d, unsigned short id);
char* __cdecl gm_LookupEntityRecordById(int id);

/* ADDRESS: GOLDTL 0x004a93a0 */
int __cdecl fcn_004a93a0(int a1, char* e, int a3, int a4, char* out)
{
	int d[32];
	int ids[32];
	int remaining;
	int i;
	int count;
	int thr;
	char* candidate;

	thr = gm_RandomMod(8) + 5;
	if (e[0x166] == 0xd) {
		return 0;
	}
	count = fcn_004f6040(ids, d, *(unsigned short*) e);
	if (count <= 0) {
		return 0;
	}
	i = 0;
	remaining = count;
	do {
		if (d[i] >= thr) {
			candidate = gm_LookupEntityRecordById(ids[i]);
			if (candidate && candidate[2] != 0xf && candidate[8] && candidate[0x166] != 0xd && candidate[0x166] != 0x1b && candidate[0x166] != 0xf && candidate[0x166] != 0x15) {
				out[0] = 7;
				*(int*) (out + 4) = *(int*) (candidate + 4);
				return 1;
			}
		}
		remaining--;
		i = (i + 1) % count;
	} while (remaining);
	return 0;
}
