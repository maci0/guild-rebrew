extern float g_6628a0;
extern float g_6628bc;
extern float g_664330;
extern float g_664154;
extern unsigned char g_773d75;

int __cdecl fcn_0050b810(int, unsigned char);

/* ADDRESS: GOLDTL 0x004f0ff0 */
int __cdecl fcn_004f0ff0(char* obj, int a1, int a2, int a3, int* out1, int* out2)
{
	int q1;
	int q2;
	int q3;

	if (a1 >= 4) {
		q1 = 4;
	} else if (a1 <= 0) {
		q1 = 0;
	} else {
		q1 = a1;
	}
	if (a2 >= 0x64) {
		q2 = 0x64;
	} else if (a2 <= 0) {
		q2 = 0;
	} else {
		q2 = a2;
	}
	if (a3 >= 3) {
		q3 = 3;
	} else if (a3 <= 1) {
		q3 = 1;
	} else {
		q3 = a3;
	}
	*out1 = q1 + 2;
	*out2 = (int) (((float) q2 * 2.0f + g_664330) * ((float) q1 * g_6628bc + g_6628a0)
		* q3 * g_664154);
	if (*(int*) (obj + 0x194) < *out1) {
		return 0;
	}
	if (fcn_0050b810(*(int*) (obj + 0x178), g_773d75) < *out2) {
		return 0;
	}
	return 1;
}
