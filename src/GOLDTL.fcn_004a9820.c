// FUNCTION: GOLD 0x004a9700
// FUNCTION: GOLDTL 0x4a9820

#include <string.h>

typedef struct Rec18 {
	int a;
	volatile int id;
	char pad8[0x18 - 8];
} Rec18;
// SIZE 0x18

unsigned short __cdecl fcn_0042e410(int n);
int __cdecl fcn_004e8b80(int kind, int max, Rec18* out);
char* __cdecl fcn_00508e40(int id);
float __cdecl fcn_0050f980(int a, int b, int c);

int __cdecl fcn_004a9820(char* a1, char* e, char* a3, char* a4, char* out)
{
	volatile int id;
	float d;
	char* cands[6];
	Rec18 recs[6];
	int n;
	int i;
	int k;
	int tries;
	char* c;

	if (*(int*) (e + 0x1c8) & 0x100) {
		return 0x20;
	}
	if (*(int*) (e + 0x194) < 4) {
		return 0x20;
	}
	if (*(int*) a3 == 1) {
		id = *(int*) (e + 4);
	} else if (*(int*) a3 == 2 && *(char**) (a3 + 0x21c) != 0) {
		id = *(int*) (*(char**) (a3 + 0x21c) + 4);
	} else {
		return 0;
	}
	n = fcn_004e8b80(4, 6, recs);
	for (i = 0; i < n; i++) {
		cands[i] = fcn_00508e40(recs[i].id);
	}
	for (i = n; i < 6; i++) {
		cands[i] = 0;
	}
	k = fcn_0042e410(6);
	for (tries = 6; tries != 0;) {
		c = cands[k];
		if (c != 0 && id != *(int*) (c + 4)) {
			d = fcn_0050f980(*(unsigned short*) c, *(unsigned short*) e, 1);
			if (fcn_0042e410(0x10) + 16.0f > d) {
				c = cands[k];
				if (c == 0 || *(int*) (e + 0x5c) == *(int*) (c + 4)) {
					return 0;
				}
				out[0] = 7;
				*(int*) (out + 4) = *(int*) (c + 4);
				return 1;
			}
		}
		tries--;
		k = (k + 1) % 6;
	}
	return 0;
}
