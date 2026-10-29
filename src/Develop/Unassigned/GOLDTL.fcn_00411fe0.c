void __cdecl fcn_00411f90(void);
void __cdecl fcn_00411b80(void);

/* Reads the 0x14-byte UI event records of the active input object and applies
 * them to the cursor position and the three button latches. Cases 0/4 scale the
 * event value into the cursor delta, case 8 accumulates the wheel step, cases
 * 12/13/14 latch the three buttons. The cursor is clamped to the screen rect
 * and the whole state is published afterwards. */
/* ADDRESS: GOLDTL 0x00411fe0 */
void __cdecl fcn_00411fe0(void)
{
	int flag;
	int pt[2];
	unsigned char ev[0x14];
	int v;
	int t;

	flag = 1;
	*(short*) 0x14ce926 = 0;
	*(short*) 0x14ce928 = 0;
	*(short*) 0x14ce92a = 0;
	if (*(int*) 0x14ce8a0 == 0) {
		return;
	}
	for (;;) {
		*(int*) 0x14ce938 = 0;
		*(int*) 0x14ce92c = 0;
		*(int*) 0x14ce93c = 0;
		*(int*) 0x14ce94c = 0;
		*(int*) 0x14ce940 = 0;
		*(int*) 0x14ce95c = 0;
		*(int*) 0x14ce950 = 0;
		*(int*) 0x14ce960 = 0;
		*(int*) 0x14ce964 = 0;
		v = ((int (__stdcall*) (int, int, void*, int*, int)) *(void**) (*(int*) 0x14ce8a0 + 0x28))(*(int*) 0x14ce8a0, 0x14, ev, &flag, 0);
		if (v < 0 || flag == 0) {
			break;
		}
		switch (*(int*) ev) {
		case 0:
			v = (int) ((float) *(int*) 0x6772b8 * *(float*) 0x662a30 * (float) *(int*) (ev + 4));
			*(short*) 0x14ce920 = (short) (*(short*) 0x14ce920 + v);
			*(short*) 0x14ce926 = (short) v;
			break;
		case 4:
			v = (int) ((float) *(int*) 0x6772b8 * *(float*) 0x662a30 * (float) *(int*) (ev + 4));
			*(short*) 0x14ce922 = (short) (*(short*) 0x14ce922 + v);
			*(short*) 0x14ce928 = (short) v;
			break;
		case 8:
			v = *(int*) 0x6772b8 * *(int*) (ev + 4);
			v >>= 8;
			if (v > 0) {
				*(int*) 0x14ce964 = 1;
			} else if (v < 0) {
				*(int*) 0x14ce960 = 1;
			}
			*(short*) 0x14ce924 = (short) (*(short*) 0x14ce924 + v);
			*(short*) 0x14ce92a = (short) v;
			fcn_00411b80();
			break;
		case 12:
			if (*(int*) (ev + 4) & 0x80) {
				*(int*) 0x14ce930 = 1;
				*(int*) 0x14ce92c = 0;
				if (*(int*) 0x14ce8e8 == 0) {
					*(int*) 0x14ce938 = 1;
				}
				fcn_00411f90();
				fcn_00411b80();
			} else {
				*(int*) 0x14ce92c = 1;
				*(int*) 0x14ce930 = 0;
				fcn_00411f90();
				fcn_00411b80();
			}
			break;
		case 13:
			if (*(int*) (ev + 4) & 0x80) {
				*(int*) 0x14ce944 = 1;
				*(int*) 0x14ce940 = 0;
				*(int*) 0x14ce94c = 1;
				fcn_00411f90();
				fcn_00411b80();
			} else {
				*(int*) 0x14ce940 = 1;
				*(int*) 0x14ce944 = 0;
				fcn_00411f90();
				fcn_00411b80();
			}
			break;
		case 14:
			if (*(int*) (ev + 4) & 0x80) {
				*(int*) 0x14ce954 = 1;
				*(int*) 0x14ce950 = 0;
				*(int*) 0x14ce95c = 1;
				fcn_00411f90();
				fcn_00411b80();
			} else {
				*(int*) 0x14ce950 = 1;
				*(int*) 0x14ce954 = 0;
				fcn_00411f90();
				fcn_00411b80();
			}
			break;
		}
	}
	if ((int) *(short*) 0x14ce920 < *(int*) 0x6b5c80) {
		*(short*) 0x14ce920 = (short) *(int*) 0x6b5c80;
	}
	if ((int) *(short*) 0x14ce920 > *(int*) 0x6772bc) {
		*(short*) 0x14ce920 = (short) *(int*) 0x6772bc;
	}
	if ((int) *(short*) 0x14ce922 < *(int*) 0x6b5c84) {
		*(short*) 0x14ce922 = (short) *(int*) 0x6b5c84;
	}
	if ((int) *(short*) 0x14ce922 > *(int*) 0x6772c0) {
		*(short*) 0x14ce922 = (short) *(int*) 0x6772c0;
	}
	if (*(int*) 0x6b5c88 & 4) {
		((void (__stdcall*) (int*)) *(void**) 0x662250)(pt);
		((void (__stdcall*) (int, int*)) *(void**) 0x662308)(*(int*) 0x14ce89c, pt);
		if (*(int*) 0x6772c4 == 0) {
			*(short*) 0x14ce920 = (short) (*(short*) 0x14ce920 + pt[0] - *(int*) 0x14ce8c0);
			*(short*) 0x14ce922 = (short) (*(short*) 0x14ce922 + (short) pt[1] - *(short*) 0x14ce8c2);
			pt[0] = (int) (short) *(int*) 0x14ce8c0;
			pt[1] = (int) *(short*) 0x14ce8c2;
			((void (__stdcall*) (int, int*)) *(void**) 0x662304)(*(int*) 0x14ce89c, pt);
			((void (__stdcall*) (int, int)) *(void**) 0x662300)(pt[0], pt[1]);
			fcn_00411b80();
			return;
		}
		t = pt[0];
		if (*(int*) 0x6772bc <= t) {
			t = *(int*) 0x6772bc;
		}
		if (*(int*) 0x6b5c80 <= t) {
			*(short*) 0x14ce920 = (short) pt[0];
			if (*(int*) 0x6772bc <= pt[0]) {
				*(short*) 0x14ce920 = (short) *(int*) 0x6772bc;
			}
		} else {
			*(short*) 0x14ce920 = (short) *(int*) 0x6b5c80;
		}
		t = pt[1];
		if (*(int*) 0x6772c0 <= t) {
			t = *(int*) 0x6772c0;
		}
		if (*(int*) 0x6b5c84 <= t) {
			*(short*) 0x14ce922 = (short) pt[1];
			if (*(int*) 0x6772c0 <= pt[1]) {
				*(short*) 0x14ce922 = (short) *(int*) 0x6772c0;
			}
		} else {
			*(short*) 0x14ce922 = (short) *(int*) 0x6b5c84;
		}
	}
	fcn_00411b80();
}
