unsigned short __cdecl gm_RandomMod(int n);
int __cdecl fcn_004f6040(int* ids, int* d, unsigned short id);
char* __cdecl gm_LookupEntityRecordById(int id);

/* ADDRESS: GOLDTL 0x004a91a0 */
int __cdecl fcn_004a91a0(int a1, char* e, int a3, int a4, char* out)
{
	int d[32];
	int ids[32];
	int remaining;
	int i;
	int count;
	int threshold;
	char* p;

	threshold = gm_RandomMod(4) + 2;
	if (e[0x166] == 0xd) {
		return 0;
	}
	count = fcn_004f6040(ids, d, *(unsigned short*) e);
	if (!count) {
		return 0;
	}
	i = 0;
	remaining = count;
	do {
		if (d[i] >= threshold) {
			p = gm_LookupEntityRecordById(ids[i]);
			if (p && p[2] != 0xf && p[8] && p[0x166] != 0xd && p[0x166] != 0x1b && p[0x166] != 0xf && p[0x166] != 0x15) {
				out[0] = 7;
				*(int*) (out + 4) = *(int*) (p + 4);
				return 1;
			}
		}
		remaining--;
		i = (i + 1) % count;
	} while (remaining);
	return 0;
}
