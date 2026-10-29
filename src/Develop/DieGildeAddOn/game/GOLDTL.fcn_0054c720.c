


#define MAX(a, b) ((a) > (b) ? (a) : (b))

int __cdecl fcn_00508eb0(unsigned short, int);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl fcn_00508d80(int, int*);

void __cdecl fcn_0054c720(char* e, unsigned short* a, unsigned short* b)
{
	int arr[12];
	int half;
	int x;
	int y;
	int i;
	float s;

	half = fcn_00508eb0(*a, 0) / 2;
	x = MAX(gm_WalkEntityChain(*a), 32000);
	y = MAX(gm_WalkEntityChain(*b), 32000);
	for (i = 0; i < 12; i++) {
		arr[i] = i + half;
	}
	fcn_00508d80(12, arr);
	i = 0;
	s = (float) (y + x);
	for (; i < 3; i++) {
		e[0xbc + i] = (char) arr[i];
		((int*) (e + 0xc0))[i] = (int) (((unsigned char) arr[i] + 1) * s * 0.0015625f);
	}
}
