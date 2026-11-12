#include <string.h>












void __cdecl fcn_00455140(char* node, float* in, float* out);
float __cdecl fcn_00451380(float* a, float* b);

/* ADDRESS: GOLDTL 0x005bd970 */
int __cdecl fcn_005bd970(char* a0, char* a1)
{
	float v4[4];
	double v5;

	if (strstr(a0, "ob_BRUECKE_FLUSS") != 0) {
		fcn_00455140(a0, (float*) 0x662d40, v4);
		v5 = -fcn_00451380((float*) 0x662d40, v4);
		*(unsigned int*) (a1 + *(int*) (a1 + 0x400) * 4) = (unsigned int) a0;
		if (v5 >= 0.0 && v5 < 0.39269909262657166) {
			*(int*) (a1 + 0x200 + *(int*) (a1 + 0x400) * 4) = 0x1a;
		}
		if (v5 >= 0.39269909262657166 && v5 < 1.178097277879715) {
			*(int*) (a1 + 0x200 + *(int*) (a1 + 0x400) * 4) = 0x1b;
		}
		if (v5 >= 1.178097277879715 && v5 < 1.9634954631328583) {
			*(int*) (a1 + 0x200 + *(int*) (a1 + 0x400) * 4) = 0x1c;
		}
		if (v5 >= 1.9634954631328583 && v5 < 2.7488936483860016) {
			*(int*) (a1 + 0x200 + *(int*) (a1 + 0x400) * 4) = 0x1d;
		}
		if (v5 >= 2.7488936483860016 && v5 < 3.534291833639145) {
			*(int*) (a1 + 0x200 + *(int*) (a1 + 0x400) * 4) = 0x1a;
		}
		if (v5 >= 3.534291833639145 && v5 < 4.319690018892288) {
			*(int*) (a1 + 0x200 + *(int*) (a1 + 0x400) * 4) = 0x1b;
		}
		if (v5 >= 4.319690018892288 && v5 < 5.1050882041454315) {
			*(int*) (a1 + 0x200 + *(int*) (a1 + 0x400) * 4) = 0x1c;
		}
		if (v5 >= 4.319690018892288 && v5 < 5.890486389398575) {
			*(int*) (a1 + 0x200 + *(int*) (a1 + 0x400) * 4) = 0x1c;
		}
		if (v5 >= 5.890486389398575 && v5 <= 6.2831854820251465) {
			*(int*) (a1 + 0x200 + *(int*) (a1 + 0x400) * 4) = 0x1a;
		}
	} else if (strstr(a0, "dummy_GEBIRGE") != 0) {
		*(unsigned int*) (a1 + *(int*) (a1 + 0x400) * 4) = (unsigned int) a0;
		*(int*) (a1 + 0x200 + *(int*) (a1 + 0x400) * 4) = 0x1e;
	} else {
		if (strstr(a0, "gb_MAUER_GR") == 0) {
			return *(int*) (a1 + 0x400) < 0x80;
		}
		*(unsigned int*) (a1 + *(int*) (a1 + 0x400) * 4) = (unsigned int) a0;
		*(int*) (a1 + 0x200 + *(int*) (a1 + 0x400) * 4) = 0x1f;
	}
	*(int*) (a1 + 0x400) += 1;
	return *(int*) (a1 + 0x400) < 0x80;
}
