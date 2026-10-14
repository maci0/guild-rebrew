// SIZE 0x58
typedef struct Deal {
	int price;
	int tax;
	int active;
	unsigned char* seller;
	int x10;
	int seller_id;
	char pad18[0x10];
	int x28;
	int x2c;
	unsigned char* buyer;
	int x34;
	int buyer_id;
	char pad3c[0x10];
	int x4c;
	int x50;
	int x54;
} Deal;

extern unsigned char g_773d75;
extern unsigned char g_772628[];

double __cdecl log10(double x);

int __cdecl fcn_00492590(int kind);
#include "Develop/DieGildeAddOn/game/spiel.h"
int __cdecl fcn_0050b710(int a, unsigned char k);
int __cdecl fcn_0050b750(int a, unsigned char k);
float __cdecl gm_RandomFloat01(void);

/* ADDRESS: GOLD 0x004931f0 */
/* ADDRESS: GOLDTL 0x004927c0 */
int __cdecl fcn_004927c0(unsigned char* e, Deal* o, int kind)
{
	char* d;
	int k;
	int pr;
	double x;

	d = (char*) gm_GetEntityTableEntry((char*) (e));
	if (e == 0 || e[2] != 6 || o == 0) {
		return 0;
	}
	if (kind != 1 && kind != 2 && kind != 4) {
		return 0;
	}
	o->price = 0;
	k = fcn_00492590(kind);
	o->x54 = 0;
	pr = fcn_0050b710(gm_WalkEntityChain(*(unsigned short*) e), g_773d75);
	x = pr;
	if (10000.0 > x) {
		x = 10000.0;
	}
	x = x / (log10(x) + 1.0) * 0.1f;
	o->price = fcn_0050b750((int) (x * (kind * 0.25f)), g_773d75);
	o->tax = (int) (o->price * 0.1f);
	o->x28 = 0;
	o->x2c = 0;
	o->x4c = 0;
	o->x50 = 0;
	if (gm_RandomFloat01() > *(float*) (d + 0x58)) {
		o->seller = e;
		o->seller_id = 0xffff;
		o->buyer = g_772628;
		o->buyer_id = k;
		*(float*) (d + 0x58) = gm_RandomFloat01() * 0.11f + *(float*) (d + 0x58) + 0.2f;
	} else {
		o->buyer = e;
		o->buyer_id = 0xffff;
		o->seller = g_772628;
		o->seller_id = k;
		*(float*) (d + 0x58) = *(float*) (d + 0x58) - 0.2f - gm_RandomFloat01() * 0.11f;
	}
	o->active = 1;
	return 1;
}
