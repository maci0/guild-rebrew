unsigned short __cdecl gm_RandomMod(int n);
int __cdecl fcn_004f6040(int* ids, int* d, unsigned short id);
char* __cdecl gm_LookupEntityRecordById(int id);

/* ADDRESS: GOLDTL 0x004a93a0 */
int __cdecl ai_PreparePriv0x03(int unused1, char* actor, int unused2, int unused3, char* out)
{
	int d[32];
	int ids[32];
	int remaining;
	int i;
	int count;
	int thr;
	char* candidate;

	thr = gm_RandomMod(8) + 5;
	if (actor[0x166] == 0xd) {
		return 0;
	}
	count = fcn_004f6040(ids, d, *(unsigned short*) actor);
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
