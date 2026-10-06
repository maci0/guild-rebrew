// FUNCTION: GOLD 0x4e70f0
// FUNCTION: GOLDTL 0x4e8cb0

#include "client_types.h"
typedef Rec18_68da68 Rec18;
// SIZE 0x18

extern Rec18_68da68 g_9a9220[42];
extern Rec18_68da68 g_68da68[];

int __cdecl fcn_004e8cb0(int all, int max, Rec18* out)
{
	int n;
	int i;

	n = 0;
	for (i = 30; i < 37; i++) {
		if (n >= max) {
			break;
		}
		if (g_68da68[g_9a9220[i].type].x4 == 7 && (all != 0 || g_9a9220[i].x4 != -1)) {
			*out = g_9a9220[i];
			n++;
			out++;
		}
	}
	return n;
}
