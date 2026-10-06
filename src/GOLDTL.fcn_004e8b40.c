#include <string.h>

// FUNCTION: GOLDTL 0x4e8b40
// FUNCTION: GOLD 0x004e6f80

#include "client_types.h"
typedef Rec18_68da68 Rec18;
// SIZE 0x18

extern Rec18_68da68 g_68da68[];

int __cdecl fcn_004e8b40(int idx, Rec18* out)
{
	if (idx >= 0x28) {
		*out = g_68da68[0];
		return 0;
	}
	*out = g_68da68[idx];
	return 1;
}

extern int g_9a9620[10];
extern char g_7f4ca0[];

// FUNCTION: GOLDTL 0x004e98d0
int* __cdecl fcn_004e98d0(void)
{
	Rec18 r;
	int p;
	unsigned char c;

	memset(g_9a9620, 0, sizeof(g_9a9620));
	for (p = (int) (g_7f4ca0 + 0x167); p < (int) (g_7f4ca0 + 0x167 + 0x65400); p += 0x21c) {
		c = *(unsigned char*) (p - 0x165);
		if (c >= 2 && c <= 7) {
			if (*(unsigned char*) p == 0) {
				g_9a9620[0]++;
			} else {
				fcn_004e8b40(*(unsigned char*) p, &r);
				g_9a9620[r.type]++;
			}
		}
	}
	return g_9a9620;
}

extern Rec18 g_9a9228[];

// FUNCTION: GOLDTL 0x004e9950
int __cdecl fcn_004e9950(int type, int max, int* out)
{
	Rec18 r;
	int p;
	int n;
	int id;

	if (max < 1) {
		return 0;
	}
	n = 0;
	for (p = (int) g_9a9228; p < (int) (g_9a9228 + 0x1c); p += sizeof(Rec18)) {
		if (n >= max) {
			break;
		}
		id = ((Rec18*) p)->id;
		fcn_004e8b40(id, &r);
		if (r.type == type) {
			out[n] = id;
			n++;
		}
	}
	return n;
}
