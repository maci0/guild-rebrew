


#include "client_types.h"
typedef Rec18_68da68 Rec18;
// SIZE 0x18

extern Rec18_68da68 g_9a9220[42];

int __cdecl fcn_004e8a80(int type, Rec18* out)
{
	int i;

	for (i = 0; i < 42; i++) {
		if (g_9a9220[i].type == type) {
			break;
		}
	}
	if (i >= 42) {
		return 0;
	}
	*out = g_9a9220[i];
	return 1;
}
