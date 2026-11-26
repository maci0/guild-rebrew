


#define MAX(a, b) ((a) > (b) ? (a) : (b))

int __cdecl fcn_00508eb0(unsigned short, int);
#include "Develop/DieGildeAddOn/game/spiel.h"
void __cdecl gm_RandomizeIntArray(int, int*);

void __cdecl he_RollTripletEventScores(char* action, unsigned short* first_ent, unsigned short* second_ent)
{
	int arr[12];
	int half;
	int wealth_a;
	int wealth_b;
	int i;
	float total_wealth;

	half = fcn_00508eb0(*first_ent, 0) / 2;
	wealth_a = MAX(gm_WalkEntityChain(*first_ent), 32000);
	wealth_b = MAX(gm_WalkEntityChain(*second_ent), 32000);
	for (i = 0; i < 12; i++) {
		arr[i] = i + half;
	}
	gm_RandomizeIntArray(12, arr);
	i = 0;
	total_wealth = (float) (wealth_b + wealth_a);
	for (; i < 3; i++) {
		action[0xbc + i] = (char) arr[i];
		((int*) (action + 0xc0))[i] = (int) (((unsigned char) arr[i] + 1) * total_wealth * 0.0015625f);
	}
}
