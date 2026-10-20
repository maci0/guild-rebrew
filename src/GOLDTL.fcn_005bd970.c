#include <string.h>

extern double g_662950;
extern double g_662958;
extern double g_666090;
extern double g_666098;
extern double g_6660a0;
extern double g_6660a8;
extern double g_6660b0;
extern double g_6660b8;
extern double g_6660c0;
extern double g_6660c8;

void __cdecl fcn_00455140(char* node, float* in, float* out);
float __cdecl fcn_00451380(float* a, float* b);

/* ADDRESS: GOLDTL 0x005bd970 */
int __cdecl fcn_005bd970(char* a0, char* a1)
{
	float v4[4];
	double v5;

	if (strstr(a0, (char*) 0x6ac41c) != 0) {
		fcn_00455140(a0, (float*) 0x662d40, v4);
		v5 = -fcn_00451380((float*) 0x662d40, v4);
		*(unsigned int*) (a1 + *(int*) (a1 + 0x400) * 4) = (unsigned int) a0;
		if (v5 >= g_662950 && v5 < g_6660c8) {
			*(int*) (a1 + 0x200 + *(int*) (a1 + 0x400) * 4) = 0x1a;
		}
		if (v5 >= g_6660c8 && v5 < g_6660c0) {
			*(int*) (a1 + 0x200 + *(int*) (a1 + 0x400) * 4) = 0x1b;
		}
		if (v5 >= g_6660c0 && v5 < g_6660b8) {
			*(int*) (a1 + 0x200 + *(int*) (a1 + 0x400) * 4) = 0x1c;
		}
		if (v5 >= g_6660b8 && v5 < g_6660b0) {
			*(int*) (a1 + 0x200 + *(int*) (a1 + 0x400) * 4) = 0x1d;
		}
		if (v5 >= g_6660b0 && v5 < g_6660a8) {
			*(int*) (a1 + 0x200 + *(int*) (a1 + 0x400) * 4) = 0x1a;
		}
		if (v5 >= g_6660a8 && v5 < g_6660a0) {
			*(int*) (a1 + 0x200 + *(int*) (a1 + 0x400) * 4) = 0x1b;
		}
		if (v5 >= g_6660a0 && v5 < g_666098) {
			*(int*) (a1 + 0x200 + *(int*) (a1 + 0x400) * 4) = 0x1c;
		}
		if (v5 >= g_6660a0 && v5 < g_666090) {
			*(int*) (a1 + 0x200 + *(int*) (a1 + 0x400) * 4) = 0x1c;
		}
		if (v5 >= g_666090 && v5 <= g_662958) {
			*(int*) (a1 + 0x200 + *(int*) (a1 + 0x400) * 4) = 0x1a;
		}
	} else if (strstr(a0, (char*) 0x6ac40c) != 0) {
		*(unsigned int*) (a1 + *(int*) (a1 + 0x400) * 4) = (unsigned int) a0;
		*(int*) (a1 + 0x200 + *(int*) (a1 + 0x400) * 4) = 0x1e;
	} else {
		if (strstr(a0, (char*) 0x6ac400) == 0) {
			return *(int*) (a1 + 0x400) < 0x80;
		}
		*(unsigned int*) (a1 + *(int*) (a1 + 0x400) * 4) = (unsigned int) a0;
		*(int*) (a1 + 0x200 + *(int*) (a1 + 0x400) * 4) = 0x1f;
	}
	*(int*) (a1 + 0x400) += 1;
	return *(int*) (a1 + 0x400) < 0x80;
}
