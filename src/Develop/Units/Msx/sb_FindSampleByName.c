


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

extern int sb_WaveDriver;
extern int* sb_BankListHead;
extern char g_14cbc20[];

Sample* __cdecl sb_FindSampleByName(Bank* bank, const char* name)
{
	Sample* r;
	int i;
	Bank* b;
	int n;

	r = 0;
	i = 0;
	if (sb_WaveDriver == 0) {
		return &(*(Sample*)g_14cbc20);
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
		for (b = ((Bank*)sb_BankListHead); b != 0; b = b->next) {
			r = sb_FindSampleByName(b, name);
			if (r != 0) {
				break;
			}
		}
	}
	return r;
}
