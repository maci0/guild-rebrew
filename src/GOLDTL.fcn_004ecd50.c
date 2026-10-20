extern float g_6628a0;
extern float g_6628a8;
extern float g_6628cc;

float __cdecl fcn_004ec8a0(char*, int);
int* __cdecl fcn_004ec950(char*, unsigned int);
int __cdecl fcn_004eccd0(char*, char*);

/* ADDRESS: GOLDTL 0x004ecd50 */
float __cdecl fcn_004ecd50(char* a0, unsigned int* a1, int* a2)
{
	float x;
	int* obj;
	int v1;
	int v4;
	int v5;
	int v6;

	x = fcn_004ec8a0(a0, 2);
	obj = fcn_004ec950(a0, *a1);
	if (obj == 0) {
		return g_6628a8;
	}
	if (*((float*) obj + 1) >= g_6628a0) {
		return g_6628a8;
	}
	v1 = *a2;
	if (v1 <= 0) {
		return g_6628a8;
	}
	v4 = fcn_004eccd0(a0, (char*) a1);
	v5 = (int) ((float) v4 * (g_6628a0 - x * g_6628cc) * (g_6628a0 - *((float*) obj + 1)));
	if (v5 <= 0) {
		return g_6628a8;
	}
	v6 = v5;
	if (v1 < v5) {
		v6 = v1;
	}
	*a2 = v6;
	return ((float) v6 / (float) v5) * (g_6628a0 - *((float*) obj + 1));
}
