int __cdecl gm_RandomMod(int);
int __cdecl fcn_00508220(int, int*);
int __cdecl fcn_004c4510(int*, int);
int __cdecl fcn_004c4570(int, int, int, void*);
int __cdecl fcn_004c5360(void);
float __cdecl fcn_004ff210(int, int);

/* ADDRESS: GOLDTL 0x00508540 */
int __cdecl fcn_00508540(int* rec, int unused, void* out)
{
	int avail[4];
	int sel[4];
	int r;
	int left;
	int mode;
	int value;
	int amount;

	avail[0] = 0;
	avail[1] = 0;
	avail[2] = 0;
	avail[3] = 0;
	sel[0] = 2;
	sel[1] = 3;
	sel[2] = 4;
	sel[3] = 5;
	value = rec[0xb];
	if ((value & 0xf0) == 0) {
		avail[0] = 1;
	}
	if ((value & 0xf00) == 0) {
		avail[1] = 1;
	}
	if ((value & 0x3000) == 0) {
		avail[2] = 1;
	}
	if ((value & 0x1c000) == 0) {
		avail[3] = 1;
	}
	r = gm_RandomMod(4) & 0xffff;
	for (left = 4; ; left--) {
		if (avail[r] == 1) {
			break;
		}
		r = (r + 1) % 4;
		if (left == 0) {
			return 0;
		}
	}
	if (r == -1) {
		return 0;
	}
	mode = sel[r];
	if (fcn_00508220(mode, avail) == 0) {
		return 0;
	}
	r = gm_RandomMod((int) ((double) (unsigned int) avail[2] * *(double*) 0x662908));
	if (r == 0) {
		return 0;
	}
	amount = (int) ((float) r * *(float*) &avail[1]);
	value = rec[0xb];
	if (mode == 2) {
		r <<= 4;
		r ^= value;
		r &= 0xf0;
	} else if (mode == 3) {
		r <<= 8;
		r ^= value;
		r &= 0xf00;
	} else if (mode == 4) {
		r <<= 0xc;
		r ^= value;
		r &= 0x3000;
	} else if (mode == 5) {
		r <<= 0xe;
		r ^= value;
		r &= 0x1c000;
	}
	value ^= r;
	fcn_004c4510(rec, rec[1]);
	fcn_004c4570(4, 1, 0x2c, out);
	fcn_004c5360();
	fcn_004ff210(*(short*) rec, -amount);
	return mode;
}
