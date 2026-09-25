#include <string.h>

int __cdecl fcn_0064eeec(char*);
int __cdecl fcn_004f4830(int, void*);
void __cdecl fcn_004f4860(unsigned short*, unsigned char, int);

struct range_4b0c90 {
	char kind;
	char strict;
	short pad2;
	int lo;
	int hi;
	int pad0c[3];
	int cur;
};
// SIZE 0x1c

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))

// FUNCTION: GOLDTL 0x4b0c90
// SIZE: 496
// FUNCTION: GOLD 0x004b0b50
// SIZE: 496

int __cdecl fcn_004b0c90(int a1, int a2, char* a3)
{
	int ids[2];
	int i;
	int n;
	int id;

	if (*a3 != '-')
		return 0;
	{
		int sign = -1;
		char signs[2][6] = { "MINUS", "PLUS" };
		char names[2][32] = { "RECHTSPRECHUNG_HAERTE", "AEMTEREINKOMMEN" };
		struct range_4b0c90* r;

		ids[0] = 0;
		ids[1] = 0xf;
		a3++;
		for (i = 0; i < 2; i++) {
			if (memcmp(a3, signs[i], strlen(signs[i])) == 0)
				break;
		}
		if (i >= 2)
			return 0;
		if (i == 1)
			sign = i;
		a3 += strlen(names[i]);
		if (*a3 != '_')
			return 0;
		a3++;
		for (i = 0; i < 2; i++) {
			if (memcmp(a3, names[i], strlen(names[i])) == 0)
				break;
		}
		if (i >= 2)
			return 0;
		a3 += strlen(names[i]);
		if (*a3 != '_')
			return 0;
		id = ids[i];
		r = (struct range_4b0c90*) names;
		if (fcn_004f4830(id, r) == 0)
			return 0;
		a3++;
		n = fcn_0064eeec(a3) * sign + r->cur;
		n = MAX(MIN(r->hi, n), r->lo);
	}
	fcn_004f4860(0, id, n);
	return 1;
}
