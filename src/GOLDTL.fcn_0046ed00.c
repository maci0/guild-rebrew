
// scroll is read through a volatile lvalue so the later += stays a memory
// read-modify-write (add [mem],reg) as in the reference.

typedef struct Win046ed00 {
	char pad0[0x10];
	int height;
	char pad14[0x254 - 0x14];
	int limit;
	int base;
	int pad25c;
	int scroll;
	int total;
	char pad268[0x3cc - 0x268];
} Win046ed00;
// SIZE 0x3cc

#include "client_types.h"
extern Win_1015f40 g_1015f40[0x60];

void __cdecl fcn_0046ed00(int delta, int step, int k)
{
	int scroll;
	int base;
	int sum;
	int v;

	scroll = *(volatile int*)&((Win046ed00*)g_1015f40)[k].scroll;
	base = ((Win046ed00*)g_1015f40)[k].base;
	sum = base + scroll;
	if (sum > 0 && step < 0) {
		v = -sum;
		if (step > v) {
			v = step;
		}
		((Win046ed00*)g_1015f40)[k].scroll = v;
	} else if (sum + ((Win046ed00*)g_1015f40)[k].height < ((Win046ed00*)g_1015f40)[k].limit && step > 0) {
		v = ((Win046ed00*)g_1015f40)[k].limit - ((Win046ed00*)g_1015f40)[k].height - base - scroll;
		if (step < v) {
			v = step;
		}
		((Win046ed00*)g_1015f40)[k].scroll += v;
	}
	((Win046ed00*)g_1015f40)[k].total += delta;
}
