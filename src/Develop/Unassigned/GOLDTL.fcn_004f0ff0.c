extern float g_6628a0;
extern float g_6628bc;
extern float g_664330;
extern float g_664154;
extern unsigned char g_773d75;

int __cdecl fcn_0050b810(int, unsigned char);

/* ADDRESS: GOLDTL 0x004f0ff0 */
int __cdecl fcn_004f0ff0(char* obj, int a1, int a2, int a3, int* out1, int* out2)
{




	if (a1 < 4) {
		if (a1 > 0) {
			a1 = a1;
		} else {
			a1 = 0;
		}
	} else {
		a1 = 4;
	}
	if (a2 < 0x64) {
		if (a2 > 0) {
			a2 = a2;
		} else {
			a2 = 0;
		}
	} else {
		a2 = 0x64;
	}
	if (a3 < 3) {
		if (a3 > 1) {
			a3 = a3;
		} else {
			a3 = 1;
		}
	} else {
		a3 = 3;
	}
	*out1 = a1 + 2;
	*out2 = (int) (((float) a2 * 2.0f + 500.0f) * ((float) a1 * 0.25f + 1.0f)
		* a3 * 32.0f);
	if (*(int*) (obj + 0x194) < *out1) {
		return 0;
	}
	if (fcn_0050b810(*(int*) (obj + 0x178), g_773d75) < *out2) {
		return 0;
	}
	return 1;
}
