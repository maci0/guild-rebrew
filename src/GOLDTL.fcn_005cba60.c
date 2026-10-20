#include <string.h>

typedef struct {
	unsigned short* house;
	char pad4[0x28];
	int role;
	int value;
	int task;
} Item5cba60;
// SIZE 0x38

char* __cdecl fcn_005463a0(int, int, int);
char* __cdecl fcn_005462a0(void);
unsigned short* __cdecl fcn_00508e40(int);
int __cdecl fcn_005ca560(Item5cba60*);
int __cdecl fcn_005cf720(unsigned short, unsigned short, int, int);

/* ADDRESS: GOLDTL 0x005cba60 */
int __cdecl fcn_005cba60(unsigned short* who, unsigned int max, Item5cba60* out, int kind)
{
	unsigned short* ps[4];
	Item5cba60* o;
	char* t;
	unsigned short* q;
	int count;
	int i;

	count = 0;
	for (t = fcn_005463a0(1, 0, 0x6f); t != 0 && count < 4; t = fcn_005462a0()) {
		if (*(int*) (t + 0xac) == *(int*) (who + 2)) {
			q = fcn_00508e40(*(int*) (t + 0xb0));
			if (q != 0) {
				ps[count++] = q;
			}
		}
	}
	if (max == 0) {
		return count;
	}
	memset(out, 0, max * 0x38);
	for (i = 0, o = out; i < count && i < max; i++, o++) {
		o->house = ps[i];
		fcn_005ca560(o);
		o->value = fcn_005cf720(*who, *o->house, kind, 0);
	}
	return count;
}
