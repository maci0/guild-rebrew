#include <string.h>

typedef struct Buf18 {
	char b0;
	int f4;
	int f8;
	int pad[3];
} Buf18;
// SIZE 0x18

int __cdecl fcn_004aa240(int, int, int, void*, void*);

/* ADDRESS: GOLDTL 0x0049d180 */
int __cdecl fcn_0049d180(int a1, int a2, int a3, void* a4, void* a5)
{
	Buf18 b1;
	Buf18 b2;

	if (a1 != 0) {
		return 0;
	}
	if (a3 != 0) {
		return 0;
	}
	b1.b0 = 0;
	b1.f4 = 0;
	b1.f8 = 0;
	if (fcn_004aa240(0, a2, 0, &b1, &b2) == 0) {
		return 0;
	}
	memcpy(a4, &b1, 0x18);
	memcpy(a5, &b2, 0x18);
	return 0x2d;
}
