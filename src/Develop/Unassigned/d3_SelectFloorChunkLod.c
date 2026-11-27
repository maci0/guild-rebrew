/* SIZE 0x1 */
typedef struct State {
	unsigned char lo : 2;
	unsigned char st : 3;
	unsigned char hi : 3;
} State;

#if defined(REBREW_GOLD)
/* The b + (a + s) grouping keeps s on the FPU stack across both compares. */

/* ADDRESS: GOLD 0x0043fee0 */
char __cdecl d3_SelectFloorChunkLod(char* a, char* b, int unused, int n)
{
	float t;
	float s;
	char r;
	char prev;

	if (((State*) (a + 0x1c70))->st != 0) {
		return ((State*) (a + 0x1c70))->st;
	}
	if (*(int*) (a + 0x24) == 0) {
		return 0;
	}
	t = *(float*) (b + 0x4c) / *(float*) (a + 0xa0);
	s = (40.0f - n) * 0.4f;
	if (t > *(float*) (b + 0x48) + (*(float*) (a + 0x1c68) + s)) {
		r = 4;
	} else if (t > *(float*) (b + 0x48) + (*(float*) (a + 0x1c64) + s)) {
		r = 2;
	} else {
		r = 1;
	}
	prev = b[0x5f];
	if (prev != 0 && prev != -1 && r != prev) {
		b[0x61] = r;
		if (++*(int*) (b + 0x58) <= 8) {
			return prev;
		}
	}
	*(int*) (b + 0x58) = 0;
	return r;
}
#else
/* ADDRESS: GOLDTL 0x0043bc30 */
char __cdecl d3_SelectFloorChunkLod(char* floor, char* cell, int unused, int n)
{
	float t;
	float s;
	char r;
	char prev;

	if (((State*) (floor + 0x8036))->st != 0) {
		return ((State*) (floor + 0x8036))->st;
	}
	if (*(int*) (floor + 0x24) == 0) {
		return 0;
	}
	t = *(float*) (cell + 0x1dc) / *(float*) (floor + 0x60);
	s = (40.0f - n) * 0.4f;
	if (t > *(float*) (floor + 0x8028) + *(float*) (cell + 0x1d8) + s) {
		r = 4;
	} else if (t > *(float*) (floor + 0x8024) + *(float*) (cell + 0x1d8) + s) {
		r = 2;
	} else {
		r = 1;
	}
	prev = cell[0x1ef];
	if (prev != 0 && prev != -1 && r != prev) {
		cell[0x1f0] = r;
		if (++*(int*) (cell + 0x1e8) <= 8) {
			return prev;
		}
	}
	*(int*) (cell + 0x1e8) = 0;
	return r;
}
#endif
