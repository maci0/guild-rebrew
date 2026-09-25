// FUNCTION: GOLD 0x004260c0
// SIZE: 176
// FUNCTION: GOLDTL 0x00422530
// SIZE: 176

#include <string.h>

// SIZE 0x40
typedef struct {
	int id;
	char name[0x3c];
} Sample;

typedef struct Bank Bank;

// SIZE 0x140
struct Bank {
	char pad0[0x134];
	int count;
	Sample* samples;
	Bank* next;
};

extern int g_6b7d7c;
extern Bank* g_6b7d78;
extern Sample g_14cbc20;

Sample* __cdecl fcn_00422530(Bank* bank, const char* name)
{
	Sample* r;
	int i;
	Bank* b;
	int n;

	r = 0;
	i = 0;
	if (g_6b7d7c == 0) {
		return &g_14cbc20;
	}
	if (bank != 0) {
		n = bank->count;
		for (; i < n; i++) {
			if (_strnicmp(bank->samples[i].name, name, 0x32) == 0) {
				r = &bank->samples[i];
				break;
			}
		}
	} else {
		for (b = g_6b7d78; b != 0; b = b->next) {
			r = fcn_00422530(b, name);
			if (r != 0) {
				break;
			}
		}
	}
	return r;
}
