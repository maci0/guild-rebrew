#include "Develop/DieGildeAddOn/game/spiel.h"
// FUNCTION: GOLD 0x4c8050
// FUNCTION: GOLDTL 0x4c8bf0

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) < (b) ? (b) : (a))

typedef struct {
	float a;
	float b;
	float c;
} tri12;
// SIZE 0xc

int __cdecl fcn_004c4dc0(char*, int);


int __cdecl fcn_004c8bf0(char* x, char* out)
{
	char* e;
	unsigned char* q;
	int k;
	unsigned int i;

	*(int*) (x + 0x10) = fcn_004c4dc0(x, *(int*) (x + 0x10));
	if (gm_ResolveEntityById(0, 0, (void**) (&e), *(int*) (x + 0x10)) == 0)
		return 1;
	q = (unsigned char*) x + 0x15;
	for (i = 0; i < (unsigned char) x[0x14]; i++) {
		k = *q;
		q++;
		((tri12*) (e + 0x90))[k].a += *(float*) q;
		q += 4;
		((tri12*) (e + 0x90))[k].a = MIN(MAX(((tri12*) (e + 0x90))[k].a, 0.0), 1000.0);
	}
	if (out != 0)
		*out = 1;
	return 0;
}
