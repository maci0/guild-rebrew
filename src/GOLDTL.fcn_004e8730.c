// FUNCTION: GOLD 0x004e6b70
// FUNCTION: GOLDTL 0x4e8730

#include "client_types.h"
typedef Rec18_68da68 Rec18;
// SIZE 0x18

extern Rec18_68da68 g_9a9220[42];

void __cdecl fcn_004e8730(int v)
{
	int i;

	for (i = 41; i != 0; i--) {
		if (g_9a9220[i].type == 0x27) {
			g_9a9220[i].x4 = v;
			return;
		}
	}
}
