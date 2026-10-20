int __cdecl fcn_0050e4a0(int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_0050b810(int, int);
void __cdecl fcn_004fc460(char*);
int __cdecl gm_RandomMod(int);
int __cdecl fcn_00495400(int, int, int, void*, void*);
int __cdecl fcn_0050d170(int);
int __cdecl fcn_004a4bb0(int, char*, int, void*, void*, int);

/* ADDRESS: GOLDTL 0x0049d300 */
int __cdecl fcn_0049d300(int a0, unsigned short* a1, int a2,
	unsigned int* a3, unsigned int* a4)
{
	int ptrs[6];
	int vals[6];
	unsigned char* e;
	unsigned char* best;
	int r;
	int i;
	int n;
	int kind;
	int mask;
	unsigned short flags;
	int val;

	best = 0;
	ptrs[0] = 0;
	ptrs[1] = 0;
	vals[0] = 0;
	vals[1] = 0;
	if (a0 != 0 || a2 != 0 || *(unsigned char*) &a1[0xb3 * 2] != 0x0f) {
		return 0;
	}
	r = fcn_0050e4a0(1);
	if (r == 0) {
		return 0;
	}
	fcn_00502cd0(*(int*) (r + 0x5d), 2, 6, 0, 0x115);
	a0 = fcn_0050b810(*(int*) (r + 0x14), *(unsigned char*) 0x773d75);
	fcn_004fc460((char*) ptrs);
	e = (unsigned char*) 0x90e094;
	a2 = 0x100;
	do {
		kind = *e;
		if (kind != 0 && *(unsigned char*) (kind * 0x24d + 0x868050) == 1) {
			flags = *(unsigned short*) (e + 0x5a * 2);
			if ((flags & 0x45) == 0) {
				if (*(char*) (e + 0x5c) <= 0x4f
					&& (best == 0 || *(char*) (e + 0x5c) < *(char*) (best + 0x5c))) {
					best = e;
				}
				if (kind == 3) {
					/* counted below */
				}
				else if (kind == 2) {
					vals[1] += 1;
					if ((flags & 0x45) == 0) {
						ptrs[1] = (int) e;
					}
				}
				else {
					vals[0] += 1;
					if ((flags & 0x45) == 0) {
						ptrs[0] = (int) e;
					}
				}
			}
		}
		e += 0xa9;
		a2 -= 1;
	} while (a2 != 0);
	/* Partial: the sparse-table arm (registry scan results, radius tests and the
	   copy-out of ptrs/vals into a3/a4) is not reconstructed yet. */
	(void) best;
	(void) r;
	(void) i;
	return 0;
}
