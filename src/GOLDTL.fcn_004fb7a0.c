#include <string.h>

typedef struct Time14 {
	int day;
	unsigned short hour;
	int min;
	int sec;
} Time14;

unsigned short __cdecl gm_RandomMod(int);
float __cdecl fcn_0042e450(void);
int __cdecl fcn_005463a0(int, int, int);
void __cdecl fcn_00500bb0(Time14* t, int value, int delay, int arg);
void __cdecl fcn_004c5530(void* msg);
int __cdecl fcn_004c6a00(void* msg);

#pragma optimize("y", off)

/* ADDRESS: GOLDTL 0x004fb7a0 */
void __cdecl fcn_004fb7a0(void)
{
	int st[9];
	int sel[16];
	unsigned char ev[0xf8];
	Time14* at;
	int phase;
	int v6;
	int v7;
	int i;
	float f;

	if (*(int*) 0x99f5a0 != 1) {
		return;
	}
	memcpy(st, (void*) 0x99f5a0, sizeof(st));
	if (*(int*) 0x99f5bc <= 0) {
		f = (float) fcn_0042e450() * *(float*) (st + 4) + *(float*) (st + 3) + *(float*) (st + 5);
		*(float*) (st + 5) = f;
		if (f <= *(float*) (st + 6)) {
			goto label_4fbc2b;
		}
		memset(ev, 0, sizeof(ev));
		st[1] += 1;
		st[2] = *(int*) 0x7f4c00;
		if (st[8] >= 4) {
			st[8] = 0;
			st[7] = 3;
			goto label_state3;
		}
		if (st[8] == 0) {
			st[7] = 3;
			goto label_state3;
		}
		sel[15] = 2;
		sel[14] = 2;
		sel[8] = 1;
		sel[7] = 1;
		sel[1] = 0;
		sel[0] = 0;
		if (st[8] == 1) {
			sel[2] = 1;
			sel[3] = 1;
			sel[4] = 1;
			sel[5] = 1;
			sel[6] = 1;
			sel[9] = 2;
			sel[10] = 2;
			sel[11] = 2;
			sel[12] = 2;
			sel[13] = 2;
		} else if (st[8] == 2) {
			sel[2] = 0;
			sel[3] = 0;
			sel[4] = 0;
			sel[5] = 0;
			sel[6] = 0;
			sel[9] = 2;
			sel[10] = 2;
			sel[11] = 2;
			sel[12] = 2;
			sel[13] = 2;
		} else {
			sel[2] = 0;
			sel[3] = 0;
			sel[4] = 0;
			sel[5] = 0;
			sel[6] = 0;
			sel[9] = 1;
			sel[10] = 1;
			sel[11] = 1;
			sel[12] = 1;
			sel[13] = 1;
		}
		v7 = sel[gm_RandomMod(0x10) & 0xffff] + 1;
		st[7] = v7;
		if (v7 == 1) {
			at = (Time14*) (ev + 0x28);
			ev[4] = 'Y';
			*(int*) (ev + 8) = *(int*) (0x773da8 + 4);
			*(int*) (ev + 0xc) = -1;
			at->day = *(int*) 0x7f4c00;
			at->hour = *(unsigned short*) 0x7f4c04;
			at->min = *(int*) 0x7f4c08;
			at->sec = *(unsigned short*) 0x7f4c0c;
			ev[0x36] = 2;
			*(int*) (ev + 0x58) = -1;
			*(int*) (ev + 0x74) = 1000;
			v6 = (int) (gm_RandomMod(4) & 0xffff) * 0x1e;
			if (*(unsigned short*) 0x7f4c04 >= 0x17) {
				v6 = (v6 & 0xffff) + 7;
			}
			fcn_00500bb0(at, v6, 4, 2);
			goto label_4fbc1d;
		}
		if (v7 == 2) {
			at = (Time14*) (ev + 0x28);
			ev[4] = 'N';
			*(int*) (ev + 8) = *(int*) (0x773da8 + 4);
			*(int*) (ev + 0xc) = -1;
			at->day = *(int*) 0x7f4c00;
			at->hour = *(unsigned short*) 0x7f4c04;
			at->min = *(int*) 0x7f4c08;
			at->sec = *(unsigned short*) 0x7f4c0c;
			ev[0x36] = 1;
			*(int*) (ev + 0x58) = -1;
			*(int*) (ev + 0x74) = 1000;
			v6 = (int) (gm_RandomMod(4) & 0xffff) * 0x1e;
			if (*(unsigned short*) 0x7f4c04 >= 0x17) {
				fcn_00500bb0(at, (v6 & 0xffff) + 7, 4, 2);
			} else {
				fcn_00500bb0(at, v6 & 0xffff, 4, 2);
			}
			goto label_4fbc1d;
		}
		if (v7 != 3) {
			st[7] = v7;
			goto label_4fbc2b;
		}
label_state3:
		at = (Time14*) (ev + 0x28);
		ev[4] = 'P';
		*(int*) (ev + 8) = *(int*) (0x773da8 + 4);
		*(int*) (ev + 0xc) = -1;
		at->day = *(int*) 0x7f4c00;
		at->hour = *(unsigned short*) 0x7f4c04;
		at->min = *(int*) 0x7f4c08;
		at->sec = *(unsigned short*) 0x7f4c0c;
		ev[0x36] = 2;
		*(int*) (ev + 0x58) = -1;
		*(int*) (ev + 0x74) = 1000;
		v6 = (int) (gm_RandomMod(4) & 0xffff) * 0x1e;
		if (*(unsigned short*) 0x7f4c04 >= 0x17) {
			v6 = (v6 & 0xffff) + 7;
		}
		fcn_00500bb0(at, v6, 4, 2);
		goto label_4fbc1d;
	}
	phase = *(int*) 0x99f5bc;
	if (phase == 1) {
		if (fcn_005463a0(1, 0, 0x59)) {
			return;
		}
	} else if (phase == 2) {
		if (fcn_005463a0(1, 0, 0x4e)) {
			return;
		}
	} else if (phase == 3) {
		if (fcn_005463a0(1, 0, 0x50)) {
			return;
		}
	}
	st[8] = 0;
	*(float*) (st + 5) = 0.0f;
	goto label_4fbc2b;
label_4fbc1d:
	fcn_004c5530(ev);
	st[8] = st[7];
label_4fbc2b:
	st[9] = 0x73657420;
	fcn_004c6a00(st);
}
