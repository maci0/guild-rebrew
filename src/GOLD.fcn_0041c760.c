// FUNCTION: GOLD 0x41c760
// SIZE: 195

#include <stdio.h>

// SIZE 0x10
typedef struct {
	unsigned long d1;
	unsigned short d2;
	unsigned short d3;
	unsigned char d4[8];
} Guid;

char __cdecl fcn_0041c760(const char* s, Guid* g)
{
	int d1;
	int d2;
	int d3;
	int b[8];
	char r;

	r = 0;
	if (s != 0 && *s != 0 && g != 0) {
		sscanf(s, "%08x-%04x-%04x-%02x%02x%02x%02x%02x%02x%02x%02x", &d1, &d2, &d3, &b[0], &b[1], &b[2], &b[3], &b[4], &b[5], &b[6], &b[7]);
		g->d1 = d1;
		g->d2 = (unsigned short) d2;
		g->d3 = (unsigned short) d3;
		g->d4[0] = (unsigned char) b[0];
		g->d4[1] = (unsigned char) b[1];
		g->d4[2] = (unsigned char) b[2];
		g->d4[3] = (unsigned char) b[3];
		g->d4[4] = (unsigned char) b[4];
		g->d4[5] = (unsigned char) b[5];
		g->d4[6] = (unsigned char) b[6];
		g->d4[7] = (unsigned char) b[7];
		r = 1;
	}
	return r;
}
