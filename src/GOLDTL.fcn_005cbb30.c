// FUNCTION: GOLDTL 0x5cbb30

#pragma pack(push, 2)
// SIZE 0xe
typedef struct {
	int day;
	unsigned short hour;
	int min;
	int sec;
} Time5cbb;
#pragma pack(pop)

// SIZE 0x38
typedef struct {
	unsigned short* house;
	char pad4[0x28];
	int role;
	int value;
	int task;
} Item5cbb;

#include "client_types.h"
extern pos14_7f4c00 g_7f4c00;

char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl fcn_005462a0(void);
unsigned short* __cdecl fcn_00508e40(int);
int __cdecl fcn_005ca560(Item5cbb* s);
int __cdecl fcn_005cf720(unsigned short, unsigned short, int, int);

int __cdecl fcn_005cbb30(unsigned short* who, unsigned int max, Item5cbb* out, int kind)
{
	int result;
	int mindays;
	unsigned short* ps[6];
	int role[6];
	char* t;
	Item5cbb* o;
	unsigned short* p;
	int found;
	int n;
	int i;
	int k;

	mindays = 200;
	result = 0;
	if (max == 0) {
		for (t = fcn_005463a0(1, 0, 0x2c); t != 0; t = fcn_005462a0()) {
			found = 0;
			if ((p = fcn_00508e40(*(int*) (t + 0xac))) == 0) {
				continue;
			}
			if (p == who) {
				found = 1;
			}
			if ((p = fcn_00508e40(*(int*) (t + 0xb0))) == 0) {
				continue;
			}
			if (p == who) {
				found = 1;
			}
			if ((p = fcn_00508e40(*(int*) (t + 0xb4))) == 0) {
				continue;
			}
			if (p == who) {
				found = 1;
			}
			if ((p = fcn_00508e40(*(int*) (t + 0xb8))) == 0) {
				continue;
			}
			if (p == who) {
				found = 1;
			}
			if ((p = fcn_00508e40(*(int*) (t + 0xbc))) == 0) {
				continue;
			}
			n = 5;
			if (p == who) {
				found = 1;
			}
			if ((p = fcn_00508e40(*(int*) (t + 0xc0))) != 0) {
				n = 6;
				if (p == who) {
					found = 1;
				}
			}
			if (found) {
				result += n;
			}
		}
		return result;
	}
	for (t = fcn_005463a0(1, 0, 0x2c); t != 0; t = fcn_005462a0()) {
		found = 0;
		if (*(int*) (t + 0xc5) - (*(Time5cbb*)&g_7f4c00).day > mindays) {
			continue;
		}
		if ((ps[0] = fcn_00508e40(*(int*) (t + 0xac))) == 0) {
			continue;
		}
		role[0] = 0;
		if (ps[0] == who) {
			found = 1;
		}
		if ((ps[1] = fcn_00508e40(*(int*) (t + 0xb0))) == 0) {
			continue;
		}
		role[1] = 1;
		if (ps[1] == who) {
			found = 1;
		}
		if ((ps[2] = fcn_00508e40(*(int*) (t + 0xb4))) == 0) {
			continue;
		}
		role[2] = 2;
		if (ps[2] == who) {
			found = 1;
		}
		if ((ps[3] = fcn_00508e40(*(int*) (t + 0xb8))) == 0) {
			continue;
		}
		role[3] = 3;
		if (ps[3] == who) {
			found = 1;
		}
		if ((ps[4] = fcn_00508e40(*(int*) (t + 0xbc))) == 0) {
			continue;
		}
		role[4] = 3;
		if (ps[4] == who) {
			found = 1;
		}
		if ((ps[5] = fcn_00508e40(*(int*) (t + 0xc0))) != 0) {
			role[5] = 4;
			if (ps[5] == who) {
				found = 1;
			}
		}
		if (!found) {
			continue;
		}
		mindays = *(int*) (t + 0xc5) - (*(Time5cbb*)&g_7f4c00).day;
		o = out;
		for (i = 0, k = 0; i < 6 && (unsigned int) i < max; i++) {
			if (ps[i] != 0) {
				o->house = ps[i];
				o->role = role[i];
				o->task = *(int*) (t + 4);
				fcn_005ca560(o);
				o->value = fcn_005cf720(*who, *o->house, kind, 0);
				k++;
				o++;
			}
		}
		result = k;
	}
	return result;
}
