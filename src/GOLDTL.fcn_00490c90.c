extern int g_7f4c00;
extern char g_773d75;

int __cdecl fcn_004507b00(int);
void __cdecl fcn_004f4830(int, int*);
float __cdecl fcn_004fbd40(void);
int __cdecl fcn_0050e4a0(int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_0050b810(int, char);
int __cdecl fcn_004ec710(void);
int __cdecl fcn_0042e410(int);

/* ADDRESS: GOLDTL 0x00490c90 */
int __cdecl fcn_00490c90(char* a0, int a1, int* a2)
{
	int v5[9];
	int mode;
	int r;
	int p;
	int cur;
	int v;
	float f;
	float k;
	int d;

	mode = fcn_004507b00(*(unsigned char*) (a0 + 0x164));
	if (g_7f4c00 >= 4) {
		fcn_004f4830(9, v5);
		f = fcn_004fbd40();
		d = v5[2] - v5[1];
		if (f < *(float*) 0x664188) {
			k = (float) d * *(float*) 0x664160 + v5[1];
		} else if (f < *(double*) 0x664180) {
			k = (float) d * *(float*) 0x66417c + v5[1];
		} else {
			k = (float) d * *(float*) 0x664178 + v5[1];
		}
		r = (int) k;
		if (mode != 1 && mode != 2 && mode != 3 && mode != 5) {
			r--;
		}
		p = fcn_0050e4a0(1);
		p = fcn_00502cd0(*(int*) ((char*) p + 0x5d), 2, 6, 0, 0x115);
		cur = fcn_0050b810(*(int*) ((char*) p + 0x14), g_773d75);
		if (cur < 3 * (int) ((float) fcn_004ec710() * *(float*) 0x6628bc)) {
			r = r + 1 + (fcn_0042e410(3) & 0xffff);
		}
		if (v5[6] - 3 > r) {
			v = (v5[6] - (fcn_0042e410(3) & 0xffff)) - 1;
			*a2 = v;
			if (v5[1] > v) {
				*a2 = v5[1];
				return 1;
			}
			*a2 = v;
			return 1;
		}
		if (v5[6] + 3 < r) {
			v = (fcn_0042e410(3) & 0xffff) + v5[6] + 1;
			*a2 = v;
			if (v5[2] < v) {
				*a2 = v5[2];
				return 1;
			}
			*a2 = v;
			return 1;
		}
	}
	return 0;
}
