unsigned short __cdecl gm_RandomMod(unsigned short n);
int __cdecl fcn_004f6040(int* ids, int* d, unsigned short id);
char* __cdecl gm_LookupEntityRecordById(int id);
int __cdecl fcn_0055c0a0(char* a, char* b);
float __cdecl fcn_0050f980(unsigned int a0, unsigned int a1, unsigned int a2);

/* ADDRESS: GOLDTL 0x004aa7c0 */
int __cdecl fcn_004aa7c0(char* entity, char* res, char* out)
{
	int d[32];
	int ids[32];
	int vb[2]; /* holds the double result of fcn_0050f980; an aligned double local forces an EBP frame */
	int remaining;
	int i;
	int count;
	int r;
	char* target;

	if (*(int*) (entity + 0x194) < 2) {
		return 0;
	}
	count = fcn_004f6040(ids, d, *(unsigned short*) entity);
	if (!count) {
		return 0;
	}
	i = gm_RandomMod(count);
	remaining = count;
	do {
		target = gm_LookupEntityRecordById(ids[i]);
		if (!target) {
			return 0;
		}
		if (!fcn_0055c0a0(entity, target)) {
			return 0;
		}
		*(double*) vb = fcn_0050f980(*(unsigned short*) entity, *(unsigned short*) target, 1);
		r = gm_RandomMod(0x3d) & 0xffff;
		if ((double) r + 20.0 > *(double*) vb) {
			r = gm_RandomMod(4) & 0xffff;
			if (d[i] < r + 2) {
				out[0] = 7;
				*(int*) (out + 4) = *(int*) (target + 4);
				*(int*) (out + 0x10) = *(unsigned short*) target;
				*(int*) (res + 8) = (gm_RandomMod(*(unsigned short*) &d[i]) & 0xffff) + 1;
				*(int*) (res + 0x10) = gm_RandomMod(3) & 0xffff;
				return 1;
			}
		}
		remaining--;
		i = (i + 1) % count;
	} while (remaining);
	return 0;
}
