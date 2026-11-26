extern int gm_GameTime;
extern char g_773d75;

int __cdecl gm_MapEntityStatRange(int);
void __cdecl fcn_004f4830(int, int*);
float __cdecl fcn_004fbd40(void);
int __cdecl gm_FindPublicBuilding(int);
int __cdecl fcn_00502cd0(int, int, int, int, int);
int __cdecl fcn_0050b810(int, char);
int __cdecl amt_CalcTotalOfficeSalaries(void);
int __cdecl gm_RandomMod(int);

/* ADDRESS: GOLDTL 0x00490c90 */
int __cdecl fcn_00490c90(char* entity, int a1, int* outResult)
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

	mode = gm_MapEntityStatRange(*(unsigned char*) (entity + 0x164));
	if (gm_GameTime >= 4) {
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
		p = gm_FindPublicBuilding(1);
		p = fcn_00502cd0(*(int*) ((char*) p + 0x5d), 2, 6, 0, 0x115);
		cur = fcn_0050b810(*(int*) ((char*) p + 0x14), g_773d75);
		if (cur < 3 * (int) ((float) amt_CalcTotalOfficeSalaries() * 0.25f)) {
			r = r + 1 + (gm_RandomMod(3) & 0xffff);
		}
		if (v5[6] - 3 > r) {
			v = gm_RandomMod(3) & 0xffff; v = v5[6] - v;
			*outResult = v - 1;
			*outResult = v5[1] > v - 1 ? v5[1] : v - 1;
			return 1;
		}
		if (v5[6] + 3 < r) {
			v = (gm_RandomMod(3) & 0xffff) + v5[6] + 1;
			*outResult = v;
			*outResult = v5[2] < v ? v5[2] : v;
			return 1;
		}
	}
	return 0;
}
