// FUNCTION: GOLD 0x0041c6f0
// SIZE: 100
// FUNCTION: GOLDTL 0x0041b1e0
// SIZE: 100

#include <stdio.h>

// SIZE 0x10
typedef struct {
	unsigned long d1;
	unsigned short d2;
	unsigned short d3;
	unsigned char d4[8];
} Guid;

char* __cdecl fcn_0041b1e0(Guid* g, char* out)
{
	char* r;

	r = 0;
	if (g != 0 && out != 0) {
		sprintf(out, "%08x-%04x-%04x-%02x%02x%02x%02x%02x%02x%02x%02x", g->d1, g->d2, g->d3, g->d4[0], g->d4[1], g->d4[2], g->d4[3], g->d4[4], g->d4[5], g->d4[6], g->d4[7]);
		r = out;
	}
	return r;
}
