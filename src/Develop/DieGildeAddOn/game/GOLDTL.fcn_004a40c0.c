


#pragma pack(push, 1)
typedef struct Recipe {
	unsigned char id;
	unsigned short goods[10];
} Recipe;
// SIZE 0x15
#pragma pack(pop)

typedef struct Calc {
	int id;
	int count;
	int goods[10];
	int need[10];
	int price[10];
	float ratio[10];
	float avg;
	int best;
	int worst;
} Calc;
// SIZE 0xb4

#include "client_types.h"
extern Rec15_699058 g_699058[37];
extern unsigned char g_773d75;

float __cdecl fcn_0050bb50(int id, char k);
float __cdecl eval_ObjektPreis2Credits(int id, int k);

int __cdecl fcn_004a40c0(Calc* p)
{
	int i;
	int k;
	int n;
	float sum;

	for (i = 0; i < 0x25; i++) {
		if (((Recipe*)g_699058)[i].id == p->id) {
			break;
		}
	}
	if (i >= 0x25) {
		return 0;
	}
	n = 0;
	for (k = 0; k < 10; k++) {
		if (((Recipe*)g_699058)[i].goods[k] != 0) {
			p->goods[n] = ((Recipe*)g_699058)[i].goods[k];
			n++;
		}
	}
	p->count = n;
	if (n == 0) {
		return 0;
	}
	p->best = 0;
	p->worst = 0;
	sum = 0;
	for (k = 0; k < p->count; k++) {
		p->price[k] = (int) fcn_0050bb50(p->goods[k], (*(char*)&g_773d75));
		p->need[k] = (int) eval_ObjektPreis2Credits(p->goods[k], 100);
		p->ratio[k] = (float) p->price[k] / p->need[k];
		sum += p->ratio[k];
		if (p->ratio[k] > p->ratio[p->best]) {
			p->best = k;
		}
		if (p->ratio[k] < p->ratio[p->worst]) {
			p->worst = k;
		}
	}
	p->avg = sum / p->count;
	return 1;
}
