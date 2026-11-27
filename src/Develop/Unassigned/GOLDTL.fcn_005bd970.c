#include <string.h>












void __cdecl fcn_00455140(char* node, float* in, float* out);
float __cdecl d3_SignedPlanarAngle(float* a, float* b);

/* ADDRESS: GOLDTL 0x005bd970 */
int __cdecl fcn_005bd970(char* node, char* entries)
{
	float v4[4];
	double angle;

	if (strstr(node, "ob_BRUECKE_FLUSS") != 0) {
		fcn_00455140(node, (float*) 0x662d40, v4);
		angle = -d3_SignedPlanarAngle((float*) 0x662d40, v4);
		*(unsigned int*) (entries + *(int*) (entries + 0x400) * 4) = (unsigned int) node;
		if (angle >= 0.0 && angle < 0.39269909262657166) {
			*(int*) (entries + 0x200 + *(int*) (entries + 0x400) * 4) = 0x1a;
		}
		if (angle >= 0.39269909262657166 && angle < 1.178097277879715) {
			*(int*) (entries + 0x200 + *(int*) (entries + 0x400) * 4) = 0x1b;
		}
		if (angle >= 1.178097277879715 && angle < 1.9634954631328583) {
			*(int*) (entries + 0x200 + *(int*) (entries + 0x400) * 4) = 0x1c;
		}
		if (angle >= 1.9634954631328583 && angle < 2.7488936483860016) {
			*(int*) (entries + 0x200 + *(int*) (entries + 0x400) * 4) = 0x1d;
		}
		if (angle >= 2.7488936483860016 && angle < 3.534291833639145) {
			*(int*) (entries + 0x200 + *(int*) (entries + 0x400) * 4) = 0x1a;
		}
		if (angle >= 3.534291833639145 && angle < 4.319690018892288) {
			*(int*) (entries + 0x200 + *(int*) (entries + 0x400) * 4) = 0x1b;
		}
		if (angle >= 4.319690018892288 && angle < 5.1050882041454315) {
			*(int*) (entries + 0x200 + *(int*) (entries + 0x400) * 4) = 0x1c;
		}
		if (angle >= 4.319690018892288 && angle < 5.890486389398575) {
			*(int*) (entries + 0x200 + *(int*) (entries + 0x400) * 4) = 0x1c;
		}
		if (angle >= 5.890486389398575 && angle <= 6.2831854820251465) {
			*(int*) (entries + 0x200 + *(int*) (entries + 0x400) * 4) = 0x1a;
		}
		*(int*) (entries + 0x400) += 1;
	} else if (strstr(node, "dummy_GEBIRGE") != 0) {
		*(unsigned int*) (entries + *(int*) (entries + 0x400) * 4) = (unsigned int) node;
		*(int*) (entries + 0x200 + *(int*) (entries + 0x400) * 4) = 0x1e;
		*(int*) (entries + 0x400) += 1;
	} else if (strstr(node, "gb_MAUER_GR") != 0) {
		*(unsigned int*) (entries + *(int*) (entries + 0x400) * 4) = (unsigned int) node;
		*(int*) (entries + 0x200 + *(int*) (entries + 0x400) * 4) = 0x1f;
		*(int*) (entries + 0x400) += 1;
	}
	return *(int*) (entries + 0x400) < 0x80;
}
