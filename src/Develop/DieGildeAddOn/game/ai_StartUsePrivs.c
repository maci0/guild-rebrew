#include <string.h>

typedef struct Buf18 {
	char b0;
	int f4;
	int f8;
	int pad[3];
} Buf18;
// SIZE 0x18

int __cdecl ai_SelectPrivTarget(int, int, int, void*, void*);

/* ADDRESS: GOLDTL 0x0049d180 */
/* ADDRESS: GOLDDE 0x0048bbc0 */
int __cdecl ai_StartUsePrivs(int a1, int a2, int a3, void* firstOut, void* secondOut)
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
	if (ai_SelectPrivTarget(0, a2, 0, &b1, &b2) == 0) {
		return 0;
	}
	memcpy(firstOut, &b1, 0x18);
	memcpy(secondOut, &b2, 0x18);
	return 0x2d;
}
