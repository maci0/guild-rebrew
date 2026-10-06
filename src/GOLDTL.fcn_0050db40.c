// FUNCTION: GOLD 0x50a6c0
// FUNCTION: GOLDTL 0x0050db40

#include <stdlib.h>

// SIZE 0x8
typedef struct {
	short slot;
	unsigned char type;
	char pad3;
	int id;
} Entity;

extern float g_6628a8;
extern double g_6628f0;
extern float g_665bf0;
extern double g_664f18;

int __cdecl gm_AccumulateTyped2(Entity*);
int __cdecl fcn_0050dac0(short);
void __cdecl fcn_0051af00(char*, int, ...);
int __cdecl fcn_005c4ec0(int, Entity*, int, char*);
void __cdecl fcn_00545d40(int, int, char*, int, int, char*);

int __cdecl fcn_0050db40(Entity* e, int extra)
{
	char msg[0x800];
	float v;
	float d;
	int amount;
	int got;

	v = (float) (gm_AccumulateTyped2(e) + extra);
	if (v > g_6628a8) {
		return 0;
	}
	d = -v;
	d += fcn_0050dac0(e->slot);
	if (e->type != 6 && e->type != 7) {
		if (abs((int) v) / d > g_6628f0) {
			return 1;
		}
		return 0;
	}
	amount = (int) (g_665bf0 * d);
	if (!(abs((int) v) / d > g_664f18)) {
		return 0;
	}
	fcn_0051af00(msg, 0x42c3);
	got = fcn_005c4ec0(e->id, e, amount, msg);
	fcn_00545d40(e->id, e->id, msg, 1, 0x5ff, "_NACHRICHTEN_HS_69");
	return got <= amount / 2;
}
