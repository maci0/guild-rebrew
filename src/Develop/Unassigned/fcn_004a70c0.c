typedef struct Blk16 {
	int v[4];
} Blk16;

/* ADDRESS: GOLDTL 0x004a70c0 */
int __cdecl fcn_004a70c0(int a1, int a2, Blk16* out)
{
	int idx;

	if (a1 <= 2 && a2 <= 4) {
		idx = *(int*) (*(int*) 0x1007cd4 + (a1 * 13 + a2) * 4 + 0xc);
		if (idx != -1) {
			*out = ((Blk16*) 0x1007ce0)[idx];
			return 1;
		}
	}
	return 0;
}
