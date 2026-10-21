extern int g_7f4c00;
extern char g_773d75;

int __cdecl fcn_004507b00(unsigned char);
int __cdecl fcn_00503fe0(int, int, int);
void __cdecl fcn_004f4830(int, int*);
float __cdecl fcn_004fbd40(void);
int __cdecl fcn_0050e4a0(int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_0050b810(int, char);
int __cdecl fcn_004ec710(void);
int __cdecl gm_RandomMod(int);

/* ADDRESS: GOLDTL 0x00490e20 */
int __cdecl fcn_00490e20(char* a0, int a1, int* a2)
{
	int v5[9];
	int mode;
	int cnt;
	int r;
	int cur;
	int v;
	int p;
	float f;
	int d;

	mode = fcn_004507b00(*(unsigned char*) (a0 + 0x164));
	if (g_7f4c00 <= 9) {
		return 0;
	}
	cnt = fcn_00503fe0(1, 5, 0x17) != 0;
	if (fcn_00503fe0(1, 5, 0x18)) {
		cnt++;
	}
	if (fcn_00503fe0(1, 5, 0x19)) {
		cnt++;
	}
	if (fcn_00503fe0(1, 5, 0x1a)) {
		cnt++;
	}
	if (cnt == 0) {
		return 0;
	}
	fcn_004f4830(10, v5);
	f = fcn_004fbd40();
	d = v5[2] - v5[1];
	if (f <= *(float*) 0x664188) {
		v = (int) ((float) d * *(float*) 0x664160 + v5[1]);
	} else if (f >= *(double*) 0x664180) {
		v = (int) ((float) d * *(float*) 0x66417c + v5[1]);
	} else {
		v = (int) ((float) d * *(float*) 0x664178 + v5[1]);
	}
	r = v;
	if (mode == 1 || mode == 2 || mode == 3 || mode == 5) {
		r--;
	}
	p = fcn_00502cd0(*(int*) ((char*) fcn_0050e4a0(1) + 0x5d), 2, 6, 0, 0x115);
	cur = fcn_0050b810(*(int*) ((char*) p + 0x14), g_773d75);
	if (cur < fcn_004ec710() * 3) {
		r = r + 1 + (gm_RandomMod(3) & 0xffff);
	}
	v = v5[6];
	if (v - 3 <= r) {
		if (v + 3 >= r) {
			return 0;
		}
		cur = (gm_RandomMod(2) & 0xffff) + v + 1;
		if (v5[2] >= cur) {
			*a2 = cur;
			return 1;
		}
		*a2 = v5[2];
		return 1;
	}
	cur = (v - (gm_RandomMod(2) & 0xffff)) - 1;
	*a2 = cur;
	if (v5[1] > cur) {
		*a2 = v5[1];
		return 1;
	}
	*a2 = cur;
	return 1;
}
